#include <SFCpad.h>

SFCpad pad(5, 7, 6);
/*
  SFCpad pad(data,clock,latch)
  data : digitalI/O Pin Number to SFCpad data Out   
  clock: digitalI/O Pin Number to SFCpad clock In
  latch: digitalI/O Pin Number to SFCpad latch In
*/

/*
 SFCpad cable
 Red Line    : data
 Yellow Line : clock
 Orange Line : latch
 
 White Line  : Vcc(+5)
 Brown Line  : GND
*/

void setup(){
  Serial.begin(9600);
}

void loop(){
  unsigned int rawData;
  rawData = pad.readRaw();
/*
  readRow Funciton Returns pad status.
  each bit means Pressed Button 
*/  
  Serial.print("----RLXArlduTEYB:");
  Serial.println(0xF000+rawData,BIN);
/*
  R: R Button
  L: L Button
  X: X Button
  A: A Button
  r: right
  l: light
  d: down 
  u: up
  T: START Button
  E: SELECT Button
  Y: Y Button
  B: B Button  
*/
  delay(100);
}

