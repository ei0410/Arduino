#include <Wire.h>
int pullup = 1;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(on_off);
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  delay(100);
}

void on_off() {
  pullup = digitalRead(12);
  if (pullup == 0) {
    Wire.write("ON ");
  } else {
    Wire.write("OFF");
  }
}

