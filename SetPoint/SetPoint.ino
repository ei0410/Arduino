#include "SetPoint.h"

int threshold = 511;
int hysteresis = 102;
int sensorPin = 0;
int ledPin = 13;

SetPoint setPoint;

void setup() {
  pinMode(ledPin, OUTPUT);

  setPoint.init(threshold, hysteresis);

  setPoint.attach(RISING_EDGE, onBrightenUp);
  setPoint.attach(FALLING_EDGE, onDarkenUp);
}

void loop() {
  int value = analogRead(sensorPin);
  setPoint.update(value);

  delay(100);
}

void onBrightenUp() {
  digitalWrite(ledPin, LOW);
}

void onDarkenUp() {
  digitalWrite(ledPin, HIGH);
}

