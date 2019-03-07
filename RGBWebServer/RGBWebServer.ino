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
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <map>
#include <ESPAsyncHTTPClient.h>

// This file contains the ssid and password!
#include "secret_key.h"

int red_led = 0;
int green_led = 2;
int blue_led = 3;

ESP8266WebServer server(80);
AsyncHTTPClient httpClient;

int prevVal = 0;

void handleRoot()
{
  String red = server.arg(0);   // read RGB arguments
  String green = server.arg(1); // read RGB arguments
  String blue = server.arg(2);  // read RGB arguments

  analogWrite(red_led, 1023 - red.toInt());
  analogWrite(green_led, 1023 - green.toInt());
  analogWrite(blue_led, 1023 - blue.toInt());

  server.send(200, "text/plain", "r " + red + " g:" + green + " b: " + blue);
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

void handlePing()
{
  server.send(200, "text/plain", "pong");
}

void setup(void)
{
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  //WiFi.localIP();

  server.on("/", handleRoot);
  server.on("/ping", handlePing);
  server.onNotFound(handleNotFound);
  delay(1000);

  server.begin();
  delay(500);
}

void loop(void)
{
  server.handleClient();
}