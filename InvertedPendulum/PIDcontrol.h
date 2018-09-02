#ifndef PIDCONTROL_H
#define PIDCONTROL_H

class PIDcontrol {
  private:
    float kp, ki, kd, sensor, target;
    float p , i , d;
    float diff[2];
    float integral;
  public:
    PIDcontrol();
    void setGain(float _kp, float _ki, float _kd);
    void setParam(float _sensor, float _target);
    void getValue();
};

#endif
