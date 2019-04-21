#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "ESP32AP-WiFi";
const char pass[] = "esp32apwifi";

const char html[] = "<!DOCTYPE html> <html lang='ja'> <head> <meta charset='UTF-8'> <style> input { margin: 8px; width: 80px; } div { font-size: 16px; color: red; text-align: center; width: 400px; } .wrapper { padding: 0.5em 1em; margin: 2em 0; font-weight: bold; color: #6091d3; background: #FFF; border: solid 3px #6091d3; border-radius: 10px; text-align: center; } </style> <title> WiFi_Car Controller </title> </head> <body> <div class='wrapper'> <p> WiFi Controller </p> </div> <form method='get'> <div class='wrapper'> <input type='submit' name='fo' value='forward' /><br> <input type='submit' name='le' value='left' /> <input type='submit' name='st' value='stop' /> <input type='submit' name='ri' value='right' /><br> <input type='submit' name='ba' value='back' /> </div> </form> </body> </html>";

const IPAddress ip(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, pass);
  delay(100);
  WiFi.softAPConfig(ip, ip, subnet);
  
  IPAddress myIP = WiFi.softAPIP();
  server.begin();

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Server start!");
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    String currentLine = "";
    Serial.println("new client!");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println(html);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      
        if (currentLine.indexOf("forward") > -1) {
          
        }
        if (currentLine.indexOf("left") > -1) {
          
        }
        if (currentLine.indexOf("stop") > -1) {
          
        }
        if (currentLine.indexOf("right") > -1) {
          
        }
        if (currentLine.indexOf("back") > -1) {
          
        }
      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}
