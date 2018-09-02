#include "PIDcontrol.h"

PIDcontrol::PIDcontrol() 
{
  ;
}

void PIDcontrol::setGain(float _kp, float _ki, float _kd)
{
  kp = _kp;
  ki = _ki;
  kd = _kd;
}

void PIDcontrol::setParam(float _sensor, float _target) 
{
  sensor = _sensor;
  target = _target;
}

void PIDcontrol::getValue() 
{
  diff[0] = diff[1];
  diff[1] = sensor - target;
  integral += (diff[1] + diff[0]) / 2.0;

  p = kp * diff[1];
  i = ki * integral;
  d = kd * (diff[1] - diff[0]);

  return p + i + d;
}

