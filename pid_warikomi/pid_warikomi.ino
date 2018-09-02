#include <TimerOne.h>

const float power = 110;
const float kp = 1;
const float ki = 0;
const float kd = 0;
//power 110, kp 0.8, ki 0, kd 3

float dt = 4000; //us
float now_error;
float old_error;
float pid;
float p;
float i;
float d;
float integral = 0;

const int sensorpin = 12;     //pins
const int motorR[2] = {5, 6};
const int motorL[2] = {3, 11};

void callback() {
  int sensor[3]; //400, 680, 400

  for (int i = 0; i < 3; i++) {
    sensor[i] = analogRead(i);
//    Serial.print(sensor[i]);
//    Serial.print(F("\t:"));
    if (sensor[i] > 680) {
      sensor[i] = 680;
    }
  }

  old_error = now_error;
  now_error = sensor[0] * (-0.8)+ sensor[1] * 0 + sensor[2] * 0.8;
  integral += (now_error + old_error) * dt / 2.0 ;
  
  p = kp * now_error;
  i = ki * integral;
  d = kd * (now_error - old_error) / dt;
  pid = p + i + d;
  
  if (pid > 255) {
    pid = 255;
  } else if (pid < -255) {
    pid = -255;
  } else {
    ;
  }
  
  int rightpwm = power * ((pid + 255.0) / 510);
  int leftpwm  = power * ((255.0 - pid) / 510);
  
//  Serial.print(old_error);
//  Serial.print("\t");
//  Serial.print(now_error);
//  Serial.print("\t");
//  Serial.print(pid);
//  Serial.print("\t");
//  Serial.print(leftpwm);
//  Serial.print("\t");
//  Serial.print(rightpwm);
//  Serial.print("\t");
//  Serial.println("");

  analogWrite(motorL[0],leftpwm);
  analogWrite(motorL[1],0);
  analogWrite(motorR[0],0);
  analogWrite(motorR[1],rightpwm);
}

void setup() {
//  Serial.begin(9600);
  while(millis() < 2000) {
    ;
  }
  pinMode(motorL[0], OUTPUT);
  pinMode(motorL[1], OUTPUT);
  pinMode(motorR[0], OUTPUT);
  pinMode(motorR[1], OUTPUT);
  
  pinMode(sensorpin, OUTPUT);
  digitalWrite(sensorpin, HIGH);
  
  Timer1.initialize(dt);
  Timer1.attachInterrupt(callback);
}

void loop() {

}
