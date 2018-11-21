#include <Servo.h>
#include <TimerOne.h> // TimerOne use 11, 12, 13pins

#define SERVO_MIN     45
#define SERVO_DEFAULT 90
#define SERVO_MAX     135

Servo servo;
const int servo_pin = 6;
int pos = SERVO_DEFAULT;

int dt = 40000;
#define SENSOR_NUMBERS 8

int r_pwm = 255;
int l_pwm = 255;
#define PWM_MAX 255
#define PWM_MIN 50

void callback() {
  int sensor[SENSOR_NUMBERS];

  for (int i = 0; i < SENSOR_NUMBERS; i++) {
    sensor[i] = analogRead(i);
    Serial.print(sensor[i]);
    Serial.print(F("\t:"));
  }
  Serial.println("");
}

void setup() {
  for (int i = 2; i < 7; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  servo.attach(servo_pin);
  servo.write(SERVO_DEFAULT);
  
  Serial.begin(9600);
  Timer1.initialize(dt);
  Timer1.attachInterrupt(callback);
}

void loop() {  
//  for (pos = 45; pos <= 135; pos += 1) {
//    servo.write(pos);
//    delay(10);
//  }
//  for (pos = 135; pos >= 45; pos -= 1) {
//    servo.write(pos);
//    delay(10);
//  }
  servo.write(pos);
}

void Stop() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void Up(int l, int r) {
  analogWrite(2, l);
  analogWrite(3, 0);
  analogWrite(4, 0);
  analogWrite(5, r);
}

void Down(int l, int r) {
  analogWrite(2, 0);
  analogWrite(3, l);
  analogWrite(4, r);
  analogWrite(5, 0);
}
