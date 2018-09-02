#include "ServoLoop.h"

ServoLoop::ServoLoop(int32_t proportionalGain, int32_t derivativeGain)
{
  m_proportionalGain = proportionalGain;
  m_derivativeGain = derivativeGain;
  m_prevError = 0x80000000L;
}

void ServoLoop::setServoLoop(int32_t rcs_min_pos, int32_t rcs_center_pos, int32_t rcs_max_pos) 
{
  m_pos = rcs_center_pos;
  m_min_pos = rcs_min_pos;
  m_max_pos = rcs_max_pos;
}

int32_t ServoLoop::getServoLoop() 
{
  return m_pos;
}

void ServoLoop::updateServoLoop(int32_t data)
{
  return m_pos + data;
}

void ServoLoop::update(int32_t error)
{
  long int velocity;
  char buf[32];
  if (m_prevError!=0x80000000)
  { 
    velocity = (error*m_proportionalGain + (error - m_prevError)*m_derivativeGain)>>10;
 
    m_pos += velocity;
    if (m_pos < m_min_pos) {
      m_pos = m_min_pos;
    } else if (m_pos > m_max_pos) {
      m_pos = m_max_pos;
    } else {
      ;
    }
    //constrain(m_pos, m_min_pos, m_max_pos);
  }
  m_prevError = error;
}
