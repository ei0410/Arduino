#ifndef omni_h
#define omni_h

class omni {
  private:
    int _pin1, _pin2, _pin3, _pin4, _pin5, _pin6, _pin7, _pin8;
  public:
    omni(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8);
    void digital_direction(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8);
    void analog_direction(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8);
};

#endif
