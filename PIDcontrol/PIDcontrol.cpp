#include "Arduino.h"
#include "PIDcontrol.h"

PIDcontrol::PIDcontrol(float kp, float ki, float kd, float dt) {
  _kp = kp;
  _ki = ki;
  _kd = kd;
  _dt = dt;
}

float PIDcontrol::control(float sensor, float target) {
  error[0] = error[1];
  error[1] = target - sensor;
  integral += (error[1] + error[0]) * _dt / 2.0;

  p = _kp * error[1];
  i = _ki * integral;
  d = _kd * (error[1] - error[0]) / _dt;
  pid = p + i + d;

  return pid;
}

