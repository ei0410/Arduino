#include <FlexiTimer2.h>

const int ledpin = 13;

void flash() {
  static boolean output = HIGH;
  
  digitalWrite(ledpin, output);
  output = !output;
}

void setup() {
  pinMode(ledpin, OUTPUT);

  FlexiTimer2::set(1000, 1.0/1000, flash);
  FlexiTimer2::start();
}

void loop() {
  
}

