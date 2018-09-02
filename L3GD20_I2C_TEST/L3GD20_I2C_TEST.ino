#include <Wire.h>

const byte L3GD20_ADDR = 0x6a;
const byte L3GD20_WHOAMI = 0x0f;
const byte L3GD20_CTRL_REG1 = 0x20;
const byte L3GD20_OUT_X_L = 0x28;
const byte L3GD20_OUT_X_H = 0x29;
const byte L3GD20_OUT_Y_L = 0x2A;
const byte L3GD20_OUT_Y_H = 0x2B;
const byte L3GD20_OUT_Z_L = 0x2C;
const byte L3GD20_OUT_Z_H = 0x2D;

byte L3GD20_read(byte reg) {
  Wire.beginTransmission(L3GD20_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(L3GD20_ADDR, 1);
  return Wire.read();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println(L3GD20_read(L3GD20_WHOAMI), HEX);
  Wire.beginTransmission(L3GD20_ADDR);
  Wire.write(L3GD20_CTRL_REG1);
  Wire.write(0x0f);
  Wire.endTransmission();
}

void loop() {
  int x, y, z;
  int h, l;

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
