#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int _offset)
{
  offset = _offset;
}

void Motor::setPin(int _in1, int _in2, int _in3) 
{
  in1 = _in1;
  in2 = _in2;
  in3 = _in3;
}

void Motor::setPower(int _power) 
{
  if (_power > 0) {
    if (offset > _power) {
      analogWrite(in1, offset);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
    } else {
      analogWrite(in1, _power);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
    }
  } else if (_power < 0) {
    if (offset > abs(_power)) {
      analogWrite(in1, offset);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
    } else {
      analogWrite(in1, -_power);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
    }
  } else {
    analogWrite(in1, 0);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
  }
}

