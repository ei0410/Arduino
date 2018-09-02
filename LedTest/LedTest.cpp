#include "Arduino.h"
#include "LedTest.h"

LedTest::LedTest(int pin) {
  m_ledPin = pin;
  pinMode(m_ledPin, OUTPUT);
}

void LedTest::on(void) {
  digitalWrite(m_ledPin, HIGH);
}

void LedTest::off(void) {
  digitalWrite(m_ledPin, LOW);
}
