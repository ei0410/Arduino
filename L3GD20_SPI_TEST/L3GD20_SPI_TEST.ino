#include <SPI.h>

const int L3GD20_CS = SS;

const byte L3GD20_ADDR = 0x6a;
const byte L3GD20_WHOAMI = 0x0f;
const byte L3GD20_CTRL_REG1 = 0x20;

const byte L3GD20_OUT_X_L = 0x28;
const byte L3GD20_OUT_X_H = 0x29;
const byte L3GD20_OUT_Y_L = 0x2A;
const byte L3GD20_OUT_Y_H = 0x2B;
const byte L3GD20_OUT_Z_L = 0x2C;
const byte L3GD20_OUT_Z_H = 0x2D;

const byte L3GD20_RW = 0x80;
const byte L3GD20_MS = 0x40;

byte L3GD20_read(byte reg) {
  byte ret = 0;

  digitalWrite(L3GD20_CS, LOW);
  SPI.transfer(reg | L3GD20_RW);
  ret = SPI.transfer(0);
  digitalWrite(L3GD20_CS, HIGH);

  return ret;
}

void setup() {
  digitalWrite(SS, HIGH);
  pinMode(SS, OUTPUT);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  Serial.begin(9600);
  while(!Serial) {
    ;
  }

  Serial.println(L3GD20_read(L3GD20_WHOAMI), HEX);
  digitalWrite(L3GD20_CS, LOW);
  SPI.transfer(L3GD20_CTRL_REG1);
  SPI.transfer(B00001111);
  digitalWrite(L3GD20_CS, HIGH);
}

void loop() {
  short h, l;
  float x, y, z;

  l = L3GD20_read(L3GD20_OUT_X_L);
  h = L3GD20_read(L3GD20_OUT_X_H);
  x = (h << 8) | l;
  l = L3GD20_read(L3GD20_OUT_Y_L);
  h = L3GD20_read(L3GD20_OUT_Y_H);
  y = (h << 8) | l;
  l = L3GD20_read(L3GD20_OUT_Z_L);
  h = L3GD20_read(L3GD20_OUT_Z_H);
  z = (h << 8) | l;

  
  Serial.print(x*0.00875);
  Serial.print("\t");
  Serial.print(y*0.00875);
  Serial.print("\t");
  Serial.print(z*0.00875);
  Serial.println("");
}
