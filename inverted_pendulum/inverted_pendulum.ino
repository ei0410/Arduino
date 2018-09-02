#include <TimerOne.h>

#define DEBUG

float callbackCycle = 4000;

float kp = 2.5;
float ki = 0.00000002;
float kd = 3.0;

//2.5 3
//ku = 1.5, tu = 0.0000004
//p = 1.5, i = 0, d = 0
//p = 0.675 i = 0.000000332, d = 0
//p = 0.9, i = 0.0000002, d = 0.00000001

float target = 515;
float error[2];
float integral;
float pid = 0;

const float pwm_min = 50;

void callback() {
  float p, i, d;
  float sensor = analogRead(1);

  error[0] = error[1];
  error[1] = sensor - target;
  integral += ((error[1] + error[0]) / 2.0) * callbackCycle;

  p = kp * error[1];
  i = ki * integral;
  d = kd * (error[1] - error[0]) / callbackCycle;
  pid = p + i + d;

  if (pid > 255) {
    pid = 255;
  } else if (pid < -255) {
    pid = -255;
  } else {
    ;
  }

  Motor(pid);
  
  #ifdef DEBUG
  Serial.println(analogRead(1));
  #endif
}

void setup() {
  #ifdef  DEBUG
  Serial.begin(9600);
  #endif
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);

  Timer1.initialize(callbackCycle);
  Timer1.attachInterrupt(callback);
}

void loop() {
  //Motor(pid);
}

void Motor(int pwm) {
  if (pwm < pwm_min && 0 < pwm) {
    pwm = pwm_min;
  } else if (pwm > -pwm_min && 0 > pwm) {
    pwm = -pwm_min;
  }
  if (pwm >= 0) {
    analogWrite(3,  pwm);
    analogWrite(5,  0);
    analogWrite(6,  pwm);
    analogWrite(11, 0);
  } else {
    analogWrite(3,  0);
    analogWrite(5,  -pwm);
    analogWrite(6,  0);
    analogWrite(11, -pwm);
  }
}

