#include <MsTimer2.h>
#include "PIDcontrol.h"

const float kp = 1.0;
const float ki = 0.0;
const float kd = 0.0;
const float dt = 0.004;

PIDcontrol PID_control = PIDcontrol(kp, ki, kd, dt);

float pid = 0;
float sensorval = 0;
float targetval = 512;

void flash() {
  sensorval = analogRead(A0);
  pid = PID_control.control(sensorval, targetval);
  Serial.println(pid);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  MsTimer2::set(dt, flash);
  MsTimer2::start();
}
