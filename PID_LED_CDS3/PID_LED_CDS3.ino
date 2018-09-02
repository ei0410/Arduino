#include<PID_v1.h>

#define inputpin A0
#define outputpin 3

double Setpoint, Input, Output;
double kp = 0.36;//0.36
double ki = 0;
double kd = 0.1;
//int delta_t = 4;

double Min = 0;
double Max = 255;

PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

void setup() {
  //myPID.SetSampleTime(delta_t);

  Input = analogRead(inputpin);
  Setpoint = 300;
  myPID.SetMode(AUTOMATIC);
  pinMode(outputpin, OUTPUT);
  pinMode(inputpin, INPUT);
  Serial.begin(9600);

}

void loop() {
  double volt = analogRead(inputpin);

  Serial.print(volt);
  Serial.print(',');
  Serial.println(Setpoint);
  Serial.print(F("\r\n"));

  myPID.Compute();
  myPID.SetOutputLimits(Min, Max);
  analogWrite(outputpin, Output);
}
