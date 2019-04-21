#include <WiFi.h>

const char ssid[] = "106F3FDDC2D2";
const char pass[] = "u4w3ihur3ei7m";

const char html[] = "<!DOCTYPE html> <html lang='ja'> <head> <meta charset='UTF-8'> <style> input { margin: 8px; width: 80px; } div { font-size: 16px; color: red; text-align: center; width: 400px; } .wrapper { padding: 0.5em 1em; margin: 2em 0; font-weight: bold; color: #6091d3; background: #FFF; border: solid 3px #6091d3; border-radius: 10px; text-align: center; } </style> <title> WiFi_Car Controller </title> </head> <body> <div class='wrapper'> <p> WiFi Controller </p> </div> <form method='get'> <div class='wrapper'> <input type='submit' name='fo' value='forward' /><br> <input type='submit' name='le' value='left' /> <input type='submit' name='st' value='stop' /> <input type='submit' name='ri' value='right' /><br> <input type='submit' name='ba' value='back' /> </div> </form> </body> </html>";

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
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(html);
            client.println();
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
    Serial.println("Client Disconnected.");
  }
}
