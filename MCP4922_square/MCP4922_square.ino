#include "pins_arduino.h"
#include <SPI.h>

#define LDAC 9

float i = 0.0;
int out = 0;

void setup() {
  pinMode(LDAC, OUTPUT);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setDataMode(SPI_MODE0);

  //Serial.begin(115200);
}

void loop() {
  if (i >= 2.0*PI) {
    i = 0.0;
  } else {
    i += 0.01;
  }

  if (i < PI) {
    out = 0;
  } else {
    out = 4095;
  }
  
  //Serial.println(out);
  
  digitalWrite(LDAC,HIGH) ;
  digitalWrite(SS,LOW) ;
  SPI.transfer((out >> 8)|0x30) ;
  SPI.transfer(out & 0xff) ;
  digitalWrite(SS,HIGH) ;
  digitalWrite(LDAC,LOW) ;
}
