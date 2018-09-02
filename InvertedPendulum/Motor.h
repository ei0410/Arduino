#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    int in1;//pwm
    int in2;//cw
    int in3;//ccw
    int offset;
    
  public:
    Motor(int _offset);
    void setPin(int _pin1, int _pin2, int _pin3);
    void setPower(int _power);
};

#endif
