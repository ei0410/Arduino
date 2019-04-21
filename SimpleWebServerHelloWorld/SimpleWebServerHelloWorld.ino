#include <WiFi.h>

const char ssid[] = "106F3FDDC2D2";
const char pass[] = "u4w3ihur3ei7m";

const char html[] = "<html>Hello ESP32 World</html>";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  delay(10);

  Serial.print("connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("WiFi connected.");
  Serial.println("IP address ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    String currentLine = "";
    Serial.println("new client!");
    while (client.connected()) {
      if (client.available()) {  
        if (currentLine.length() == 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println(html);
          break;
        } else {
          currentLine = "";
        }
      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}
