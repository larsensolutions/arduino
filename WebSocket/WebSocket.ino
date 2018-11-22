/**
 * WebSocket.ino
 * by Erik Andreas Larsen
 * 
 * Example taken from https://github.com/Links2004/arduinoWebSockets/blob/master/examples/esp8266/WebSocketClient/WebSocketClient.ino
 * 
 * Depends on these libraries: 
 * https://github.com/Links2004/arduinoWebSockets
 * https://github.com/bblanchon/ArduinoJson
 * 
 * This sketch was used to test that the ESP could connect to my python websocket server
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

#include <WebSocketsClient.h>

// This file contains the ssid and password!
#include "secret_key.h"

ESP8266WebServer server(80);
WebSocketsClient webSocket;

int slaveSelectPin = 16;
int led = 0; // All LED off

// Using this to confirm what buttons were pushed
void printBinary(byte inByte)
{
    if (Serial)
    {
        Serial.print(inByte);
        Serial.print(" - ");
        for (int b = 7; b >= 0; b--)
        {
            Serial.print(bitRead(inByte, b));
        }
        Serial.println("");
    }
}

void handleRoot()
{
    server.send(200, "text/plain", "hello from esp8266!");
}

struct RegisterLED {
  int slot;
  int position;
  int value;
};

struct RegisterLED convert(int id, int value){
    RegisterLED data;
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
            
            Serial.println(sensorType);
            Serial.println(value);
            Serial.println(id);

            RegisterLED data = convert(id, value);

            bitWrite(led, data.position, data.value);

            digitalWrite(slaveSelectPin, LOW);
            SPI.transfer(led);
            digitalWrite(slaveSelectPin, HIGH);
        }
        Serial.printf("[WSc] get text: %s\n", payload);
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

    delay(1000);

    server.begin();
    Serial.println("HTTP server started");

    delay(500);

    webSocket.begin("192.168.0.30", 5000, "/api/v1/echo");

    // event handler
    webSocket.onEvent(webSocketEvent);

    // use HTTP Basic Authorization this is optional remove if not needed
    //webSocket.setAuthorization("user", "Password");

    // try ever 5000 again if connection has failed
    webSocket.setReconnectInterval(5000);

    pinMode(slaveSelectPin, OUTPUT);
    // Initiate SPI (Serial Peripheral Interface)
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(0);
    digitalWrite(slaveSelectPin, HIGH);
}

void loop(void)
{
    server.handleClient();
    webSocket.loop();
    delay(100);
}
