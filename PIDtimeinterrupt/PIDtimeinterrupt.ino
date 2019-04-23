#include <TimerOne.h>

#define delta 4000

#define target 2.5
#define Kp 50
#define Ki 0
#define Kd 0

volatile float duty = 0;
volatile float dt, preTime;
volatile float error;
volatile float P, I, D, preP;

void PID() {
  P = target - error;
  I += P * delta;
  D = (P - preP) / delta;
  preP = P;

  duty += Kp * P + Ki * I + Kd * D;
}

void serialMonitor() {
//  Serial.print(dt); Serial.print(",");
//  Serial.print(duty, 3); Serial.print(",");
//  Serial.print(P, 3); Serial.print(",");
//  Serial.print(I, 3); Serial.print(",");
//  Serial.print(D, 3); Serial.print(",");
  Serial.print(target); Serial.print(",");
  Serial.println(error);
}

void callback() {
  analogWrite(3, constrain(duty, 0, 255));
  for (int i = 0; i < 1000; i++) {
    error += analogRead(0);
  }
  error = 5.0 * (error / 1000) / 1023;

  PID();

  serialMonitor();
}

void setup() {
  Serial.begin(9600);

  Timer1.initialize(delta);
  Timer1.attachInterrupt(callback);
}

void loop() {
  
}
