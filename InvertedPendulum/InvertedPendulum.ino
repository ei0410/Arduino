#include <SPI.h>
#include "KalmanFilter.h"
#include "Motor.h"
#include "PIDcontrol.h"

const int L3GD20_CS = SS;

const byte L3GD20_ADDR = 0x6a;
const byte L3GD20_WHOAMI = 0x0f;
const byte L3GD20_CTRL_REG1 = 0x20;

const byte L3GD20_OUT_Y_L = 0x2A;
const byte L3GD20_OUT_Y_H = 0x2B;

const byte L3GD20_RW = 0x80;
const byte L3GD20_MS = 0x40;

const int Lpin1 = 3;
const int Lpin2 = 2;
const int Lpin3 = 4;
const int Rpin1 = 5;
const int Rpin2 = 6;
const int Rpin3 = 7;

int offset = 25;

Motor Lmotor(offset);
Motor Rmotor(offset);

const float kp = 1;
const float ki = 0;
const float kd = 1;

float target = 0;

static float diff[2];
static float integral;

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

  Serial.begin(115200);
  while(!Serial) {
    ;
  }

  Serial.println(L3GD20_read(L3GD20_WHOAMI), HEX);
  digitalWrite(L3GD20_CS, LOW);
  SPI.transfer(L3GD20_CTRL_REG1);
  SPI.transfer(B00001111);
  digitalWrite(L3GD20_CS, HIGH);

  Lmotor.setPin(Lpin1, Lpin2, Lpin3);
  Rmotor.setPin(Rpin1, Rpin2, Rpin3);
}

void loop() {
  short h, l;
  float y;

  float p, i, d;
  float pid;

  l = L3GD20_read(L3GD20_OUT_Y_L);
  h = L3GD20_read(L3GD20_OUT_Y_H);
  y = (h << 8) | l;
  y *= 0.00875;

  diff[0] = diff[1];
  diff[1] = target - y;
  integral += (diff[1] + diff[0]) / 2.0;

  p = kp * diff[1];
  i = ki * integral;
  d = kd * (diff[1] - diff[0]);

  pid = p + i + d;

  Lmotor.setPower(pid);
  Rmotor.setPower(pid);

  Serial.print(p);
  Serial.println("");
}
