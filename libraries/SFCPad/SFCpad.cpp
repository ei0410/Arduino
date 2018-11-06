#include "SFCpad.h"

#include <inttypes.h>
#include "Arduino.h"

SFCpad::SFCpad(uint8_t data, uint8_t clock, uint8_t latch)
{
  init(data, clock, latch);
}

void SFCpad::init(uint8_t data, uint8_t clock, uint8_t latch)
{
  _data_pin = data;
  _clock_pin = clock;
  _latch_pin = latch;

  pinMode(_data_pin, INPUT);
  pinMode(_clock_pin, OUTPUT);
  pinMode(_latch_pin, OUTPUT);

  digitalWrite(_clock_pin, LOW);
  digitalWrite(_latch_pin, HIGH);
}

uint16_t SFCpad::readRaw() {
  byte i;
  uint16_t b;
  uint16_t d;
  
  b = 1;
  d = 0;
  
  digitalWrite(_latch_pin,LOW);
  delayMicroseconds(250);
  for (i = 0;i < 16;i++){
    if(digitalRead(_data_pin)==LOW){
      d = d | b;
    }
    b = b<<1;
  digitalWrite(_clock_pin,HIGH);
  delayMicroseconds(500);
  digitalWrite(_clock_pin,LOW);
  } 
  digitalWrite(_latch_pin,HIGH);

  return(d);
}

