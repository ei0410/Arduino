#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void top() {
  server.send(200, "text/html", "<center>ようこそ・・・<b>「IoTの世界」</b>へ・・・</center>");
}

void setup() {
  WiFi.softAP("ゆっくりしていってね！");
  server.on("/", top);
  server.begin();
}

void loop() {
  server.handleClient();
}

