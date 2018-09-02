#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.requestFrom(8, 3);

  while(Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println("");
  delay(500);
}
