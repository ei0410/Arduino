#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.requestFrom(8, 1);
  while(Wire.available()) {
    int c = Wire.read();
    Serial.print(c);
  }
  Serial.println(" cm");
  delay(500);
}
