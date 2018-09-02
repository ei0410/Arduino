#include "Arduino.h"
#include "omni.h"

omni::omni(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8) {
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
  _pin5 = pin5;
  _pin6 = pin6;
  _pin7 = pin7;
  _pin8 = pin8;
}

void omni::digital_direction(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8) {
  digitalWrite(_pin1, x1);
  digitalWrite(_pin2, x2);
  digitalWrite(_pin3, x3);
  digitalWrite(_pin4, x4);
  digitalWrite(_pin5, x5);
  digitalWrite(_pin6, x6);
  digitalWrite(_pin7, x7);
  digitalWrite(_pin8, x8);
}

void omni::analog_direction(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8) {
  analogWrite(_pin1, x1);
  analogWrite(_pin2, x2);
  analogWrite(_pin3, x3);
  analogWrite(_pin4, x4);
  analogWrite(_pin5, x5);
  analogWrite(_pin6, x6);
  analogWrite(_pin7, x7);
  analogWrite(_pin8, x8);
}

