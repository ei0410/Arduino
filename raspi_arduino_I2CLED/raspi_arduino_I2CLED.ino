#include <Wire.h>

int SLAVE_ADDRESS = 0x04;
int ledPin = 13;
int analogPin = A0;

boolean ledOn = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  
  Wire.begin(SLAVE_ADDRESS);

  Wire.onReceive(ReceiveMassage);

  Wire.onRequest(RequestMassage);
}

void loop() {
  
}

void ReceiveMassage(int n) {
  char cmd = Wire.read();
  if (cmd == '1') {
    toggleLED();
  }
}

void RequestMassage() {
  int reading = analogRead(analogPin);
  Wire.write(reading >> 2); // wanna size of 1byte into size of value
}

void toggleLED() {
  ledOn = !ledOn;
  digitalWrite(ledPin, ledOn);
}

