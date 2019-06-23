/**
 * RaspdusWifi.ino
 * by Erik Andreas Larsen
 * 
 * https://github.com/larsensolutions/arduino
 * https://twitter.com/grizzlifrog
 * 
 **/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <map>
#include <ESPAsyncHTTPClient.h>

// This file contains the ssid and password!
#include "secret_key.h"
#include "74HC595.h"

ESP8266WebServer server(80);
WebSocketsClient webSocket;
Controller74HC595 btnController(5, 4, 2); // On Fritzing component, PIN 4 & 5 are switched around! Very important to know! Should be 4,5,2 for fritzing, 5,4,2 for the prototype
Controller74HC595 ledController(16, 2);
AsyncHTTPClient httpClient;

int prevVal = 0;

struct RegisterData convert(int id, int value)
{
  RegisterData data;
  data.value = value > 0 ? 1 : 0;
  data.slot = floor(id / 8);
  data.position = id % 8;
  return data;
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
  StaticJsonBuffer<300> JSONBuffer;
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[WSc] Disconnected!\n");
    break;
  case WStype_CONNECTED:
  {
    Serial.printf("[WSc] Connected to url: %s\n", payload);
    break;
  }
  case WStype_TEXT:
  {
    JsonObject &parsed = JSONBuffer.parseObject(payload);
    if (!parsed.success())
    {
      Serial.println("Parsing failed");
    }
    else
    {
      const char *sensorType = parsed["type"];
      if (strcmp(sensorType, "sensor") == 0)
      {
        break;
      }
      int value = parsed["value"];
      int id = ((int)parsed["id"]) - 1;

      RegisterData data = convert(id, value);
      ledController.writeRegisterData(data);
    }
    break;
  }
  case WStype_BIN:
    Serial.printf("[WSc] get binary length: %u\n", length);
    hexdump(payload, length);

    // send data to server
    // webSocket.sendBIN(payload, length);
    break;
  case WStype_ERROR:
    break;
  }
}

void handleRoot()
{
  server.send(200, "text/plain", "Raspdus box is live!");
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void initLEDstates()
{
  Serial.println("Initialise LED states");
  HTTPClient http;                                      // Declare object of class HTTPClient
  http.begin("http://192.168.10.30:5000/api/v1/states"); // Specify request destination
  int httpCode = http.GET();                            // Send the request
  String payload = http.getString();
  
  const size_t bufferSize = http.getSize(); //JSON_ARRAY_SIZE(16) + 16*JSON_OBJECT_SIZE(4) + 870;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonArray& root = jsonBuffer.parseArray(payload);
  if (root.success())
  {
    for (JsonObject& device : root)
    {
      int id = device["id"];
      int value = device["state"];
      RegisterData data = convert(id-=1, value); // Adjust for 0 index
      ledController.writeRegisterData(data);
    }
  }else{
    Serial.println("Could not parse LED states");
  }
  http.end();
}

void setup(void)
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(500);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  startOTA();                  // Start the OTA service

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  delay(1000);

  server.on("/inline", []() {
    server.send(200, "text/plain", String(prevVal));
  });

  server.onNotFound(handleNotFound);

  delay(1000);

  server.begin();
  Serial.println("HTTP server started");

  delay(500);

  btnController.begin(255);
  ledController.begin(0);

  delay(500);

  webSocket.begin("192.168.10.30", 5000, "/api/v1/echo");
  // event handler
  webSocket.onEvent(webSocketEvent);
  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

  delay(100);
  initLEDstates();
  delay(100);
}

// Callbacks from async http requests
// Consider refactoring
void readSucceeded()
{
  // Not really interested in the response
}

void readFailed(String msg)
{
  DEBUG(msg);
}

void loop(void)
{
  server.handleClient();
  if (btnController.needToHandleButtonPress())
  {
    // Async http requests, so we can continue listening for button clicks
    // Light API indexes start at 1, so taking care of that with the ++
    httpClient.initialize("http://192.168.10.30:5000/api/v1/toggle/" + String(btnController.activeButtonIndex += 1));
    httpClient.makeRequest(readSucceeded, readFailed);
  };
  delay(20);
  webSocket.loop();
  ArduinoOTA.handle();
}

const char *OTAName = "ESP8266-Kitchen";           // A name and a password for the OTA service
const char *OTAPassword = "esp8266";

void startOTA() { // Start the OTA service
  ArduinoOTA.setHostname(OTAName);
  ArduinoOTA.setPassword(OTAPassword);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\r\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready\r\n");
}