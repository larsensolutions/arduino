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

// This file contains the ssid and password!
#include "secret_key.h"

ESP8266WebServer server(80);

int prevVal = 0;

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", String(prevVal));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void sendRequest(int val){
    Serial.println("Sending POST");
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
    if (val < 30){
      JSONencoder["status"] = "off";
    }
    else {
      JSONencoder["value"] = val;
    }
  
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://192.168.0.30:5000/api/v1/devices/5");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.PATCH(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
}
const int totalSamples = 20;
double samples = totalSamples;

double total = 0;
double currentVal = 0;
double siblingVal = 0;
int average = 0;

void loop(void) {  
  
  server.handleClient();
  currentVal = analogRead(A0);
  currentVal = map(currentVal, 0, 1023, 0, 255);
  
  if(siblingVal==currentVal){
    return;
  }
  siblingVal = currentVal;
  samples--;
  Serial.println(currentVal);
  delay(20);
  
 
  total += currentVal;

  if(samples == 0){
    samples = totalSamples;
    average = total/samples;
    total = 0;
  }

  if (abs(prevVal-average) > 15){
      sendRequest(average);
      prevVal = average;
    }
}
