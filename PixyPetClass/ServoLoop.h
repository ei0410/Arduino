#ifndef SERVOLOOP_H
#define SERVOLOOP_H
#include "Arduino.h"

class ServoLoop
{
  private:
    int32_t m_pos;
    int32_t m_min_pos;
    int32_t m_max_pos;
    int32_t m_prevError;
    int32_t m_proportionalGain;
    int32_t m_derivativeGain;
  public:
    ServoLoop(int32_t proportionalGain, int32_t derivativeGain);
    void setServoLoop(int32_t rcs_min_pos, int32_t rcs_center_pos, int32_t rcs_max_pos);
    int32_t getServoLoop();
    void updateServoLoop(int32_t data);
    void update(int32_t error);
};

#endif
