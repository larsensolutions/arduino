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
#include <SPI.h>
#include <ArduinoJson.h>
#include <map>

// This file contains the ssid and password!
#include "secret_key.h"
#include "74HC595.h"

ESP8266WebServer server(80);
Controller74HC595 controller(5, 4, 2);

int prevVal = 0;

std::map<int, int> light = {{1, 1}, {2, 2}, {4, 3}, {8, 4}};

void handleRoot()
{
  server.send(200, "text/plain", "hello from esp8266!");
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

  server.on("/inline", []() {
    server.send(200, "text/plain", String(prevVal));
  });

  server.onNotFound(handleNotFound);

  delay(1000);

  server.begin();
  Serial.println("HTTP server started");
  controller.begin();
}

void patch(String url, JsonObject &JSONencoder)
{
  char JSONmessageBuffer[300];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  HTTPClient http; // Declare object of class HTTPClient

  http.begin(url); // Specify request destination
  http.addHeader("Content-Type", "application/json");      // Specify content-type header

  int httpCode = http.PATCH(JSONmessageBuffer); // Send the request
  String payload = http.getString();            // Get the response payload

  Serial.println(httpCode); // Print HTTP return code
}

void dim(int light, int val)
{
  StaticJsonBuffer<300> JSONbuffer; //Declaring static JSON buffer
  JsonObject &JSONencoder = JSONbuffer.createObject();
  if (val < 30)
  {
    JSONencoder["status"] = "off";
  }
  else
  {
    JSONencoder["value"] = val;
  }
   patch("http://192.168.0.30:5000/api/v1/devices/"+String(light), JSONencoder);
}

void toggle(int light)
{
  StaticJsonBuffer<300> JSONbuffer; //Declaring static JSON buffer
  JsonObject &JSONencoder = JSONbuffer.createObject();
  JSONencoder["status"] = "toggle";
  patch("http://192.168.0.30:5000/api/v1/devices/"+String(light), JSONencoder);
}

void loop(void)
{
  server.handleClient();
  if (controller.needToHandleButtonPress())
  {
    delay(500);
    // Light API indexes start at 1, so taking care of that with the ++
    toggle(controller.activeButtonIndex+=1);
  };
  delay(100);
}
