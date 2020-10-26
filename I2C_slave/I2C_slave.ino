#include <Wire.h>
const int dist_pin = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(psd);
}

void loop() {
  delay(100);
}

void psd() {
  int temp, distance;
  temp = analogRead(dist_pin);
  if (temp < 4) {
    temp = 4;
  }
  distance = 6787 / (temp - 3);

  Wire.write(distance);
}
