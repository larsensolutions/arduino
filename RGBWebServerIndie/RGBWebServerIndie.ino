/* 
* RGB web server with ESP8266-07
*
* Wiring Circuit 
* 0=Red (GPIO0)
* 2=Green (GPIO2)
* 3=Blue (GPIO3) Rx
*/



#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

int red_led = 0;
int green_led = 2;
int blue_led = 3;

const char *ssid = "Rainfall Mood LED";
// const char *password = "87654321";

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1); //IP address of your ESP
DNSServer dnsServer;
ESP8266WebServer webServer(80);

//Webpage html Code
String webpage = ""
                 "<!DOCTYPE html><html><head><title>Rainfall Mood LED</title><meta name='mobile-web-app-capable' content='yes' />"
                 "<meta name='viewport' content='width=device-width' /></head><body style='margin: 0px; padding: 0px;'>"
                 "<canvas id='colorspace'></canvas>"
                 "</body>"
                 "<script type='text/javascript'>"
                 "(function () {"
                 " var canvas = document.getElementById('colorspace');"
                 " var ctx = canvas.getContext('2d');"
                 " function drawCanvas() {"
                 " var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);"
                 " for(var i=0; i <= 360; i+=10) {"
                 " colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');"
                 " }"
                 " ctx.fillStyle = colours;"
                 " ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);"
                 " var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);"
                 " luminance.addColorStop(0, '#ffffff');"
                 " luminance.addColorStop(0.05, '#ffffff');"
                 " luminance.addColorStop(0.5, 'rgba(0,0,0,0)');"
                 " luminance.addColorStop(0.95, '#000000');"
                 " luminance.addColorStop(1, '#000000');"
                 " ctx.fillStyle = luminance;"
                 " ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);"
                 " }"
                 " var eventLocked = false;"
                 " function handleEvent(clientX, clientY) {"
                 " if(eventLocked) {"
                 " return;"
                 " }"
                 " function colourCorrect(v) {"
                 " return Math.round(1023-(v*v)/64);"
                 " }"
                 " var data = ctx.getImageData(clientX, clientY, 1, 1).data;"
                 " var params = ["
                 " 'r=' + colourCorrect(data[0]),"
                 " 'g=' + colourCorrect(data[1]),"
                 " 'b=' + colourCorrect(data[2])"
                 " ].join('&');"
                 " var req = new XMLHttpRequest();"
                 " req.open('POST', '?' + params, true);"
                 " req.send();"
                 " eventLocked = true;"
                 " req.onreadystatechange = function() {"
                 " if(req.readyState == 4) {"
                 " eventLocked = false;"
                 " }"
                 " }"
                 " }"
                 " canvas.addEventListener('click', function(event) {"
                 " handleEvent(event.clientX, event.clientY, true);"
                 " }, false);"
                 " canvas.addEventListener('touchmove', function(event){"
                 " handleEvent(event.touches[0].clientX, event.touches[0].clientY);"
                 "}, false);"
                 " function resizeCanvas() {"
                 " canvas.width = window.innerWidth;"
                 " canvas.height = window.innerHeight;"
                 " drawCanvas();"
                 " }"
                 " window.addEventListener('resize', resizeCanvas, false);"
                 " resizeCanvas();"
                 " drawCanvas();"
                 " document.ontouchmove = function(e) {e.preventDefault()};"
                 " })();"
                 "</script></html>";
void handleRoot()
{
    String red = webServer.arg(0);   // read RGB arguments
    String green = webServer.arg(1); // read RGB arguments
    String blue = webServer.arg(2);  // read RGB arguments

    // Common anode
    analogWrite(red_led, red.toInt());
    analogWrite(green_led, green.toInt());
    analogWrite(blue_led, blue.toInt());

    //Common cathode
    //analogWrite(0, 1023 - red.toInt());
    //analogWrite(2, 1023 - green.toInt());
    //analogWrite(3, 1023 - blue.toInt());

    webServer.send(200, "text/html", webpage);
}
void setup()
{
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);
    pinMode(blue_led, OUTPUT);

    analogWrite(red_led, 1023);
    analogWrite(green_led, 1023);
    analogWrite(blue_led, 1023);

    delay(1000);

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid);
    dnsServer.start(DNS_PORT, "rgb", apIP);
    webServer.on("/", handleRoot);
    webServer.begin();
}

void loop()
{
    dnsServer.processNextRequest();
    webServer.handleClient();
}