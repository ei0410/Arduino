#include "LedTest.h"

LedTest led = LedTest(13);

void setup() {
  
}

void loop() {
  led.on();
  delay(100);
  led.off();
  delay(100);
}
