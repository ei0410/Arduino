#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void top() {
  server.send(200, "text/html", "<p>Hello IoT World!</p>");
}

void setup() {
  WiFi.softAP("IoT");
  server.on("/", top);
  server.begin();
}

void loop() {
  server.handleClient();
}
