#ifndef PIDcontrol_h
#define PIDcontrol_h

static float error[2];
static float integral;

class PIDcontrol {
  private:
    float _kp, _ki, _kd, _dt;
    float p, i, d, pid;
    //float error[2];
    //float integral;
  public:
    PIDcontrol(float kp, float ki, float kd, float dt);
    float control(float sensor, float target);
};

#endif
