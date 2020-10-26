#include "pins_arduino.h"
#include <SPI.h>

#define LDAC 9

int i = 0;

void setup() {
  pinMode(LDAC, OUTPUT);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setDataMode(SPI_MODE0);
}

void loop() {
  if (i >= 4096) {
    i = 0;
  } else {
    i++;
  }
  
  digitalWrite(LDAC,HIGH) ;
  digitalWrite(SS,LOW) ;
  SPI.transfer((i >> 8)|0x30) ;
  SPI.transfer(i & 0xff) ;
  digitalWrite(SS,HIGH) ;
  digitalWrite(LDAC,LOW) ;
}
