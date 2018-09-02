typedef enum {
  INIT,
  TRACE,
  TURN_R,
  TURN_L,
  CROSS_LINE,
  STOP,
  NONE
} Status;

Status gStatus = INIT;

#include <Servo.h>

//#define DEBUG

int power = 135;
const float kp = 0.036;
const float kp_pos = 1.05;

float error;
float p;

Servo myservo;
const int servopin = 8;
int pos = 75;

int threshold = 760;
const int motorR = 11;
const int motorL = 12;
int leftpwm = 0;
int rightpwm = 0;

const int sensor_number = 8;
int sensor[sensor_number];
int trace = 0;
int cross_count = 0;

void setup() {
  myservo.attach(servopin);
  myservo.write(pos);
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

void loop() {
  for (int i = 0; i < sensor_number; i++) {
    sensor[i] = analogRead(i);
    #ifdef DEBUG
    Serial.print(sensor[i]);
    Serial.print("\t");
    #endif
  }

  if (sensor[0] < threshold){
    trace += 1;
  }
  if (sensor[1] < threshold){
    trace += 2;
  }
  if (sensor[2] < threshold){
    trace += 4;
  }
  if (sensor[3] < threshold){
    trace += 8;
  }
  if (sensor[4] < threshold) {
    trace += 16;
  }
  if (sensor[5] < threshold) {
    trace += 32;
  }
  if (sensor[6] < threshold){
    trace += 64;
  }
  if (sensor[7] < threshold) {
    trace += 128;
  }

  switch(gStatus) {
    case INIT:
      while(millis() < 2000) {
        ;
      }
      gStatus = TRACE;
      break;
    case TRACE:
      if (trace == 31) {
        delay(600);
        if (trace == 31) {
          gStatus = TURN_R;
        } else {
          gStatus = CROSS_LINE;
        }
      } else if (trace == 248) {
        delay(600);
        if (trace == 248) {
          gStatus = TURN_L;
        } else {
          gStatus = CROSS_LINE;
        } 
      } else if (trace == 255) {
        gStatus = CROSS_LINE;
      } else {
        gStatus = TRACE;
      }
      p_control();
      break;
    case TURN_R:
      pos = 45;
      rightpwm = 80;
      leftpwm  = 0;
      
      if (trace == 12) {
        gStatus = TRACE;
      } else {
        gStatus = TURN_R;
      }
      break;
    case TURN_L:
      pos = 105;
      rightpwm = 0;
      leftpwm  = 80;
      
      if (trace == 48) {
        gStatus = TRACE;
      } else {
        gStatus = TURN_L;
      }
      break;
    case CROSS_LINE:
      cross_count = cross_count + 1;
      delay(1000);
      if (cross_count > 1) {
        gStatus = STOP;
      } else {
        gStatus = TRACE;
      }
      break;
    case STOP:
      pos = 75;
      rightpwm = 0;
      leftpwm = 0;
      break;
    default:
      break;
  }

  myservo.write(pos);
  Motor(rightpwm, leftpwm);
  
  #ifdef DEBUG
  Serial.print(cross_count);
  Serial.print("\t");
  Serial.println(trace);
  #endif

  trace = 0;
}

void Motor(int motor_r, int motor_l) {
  analogWrite(motorR, motor_r);
  analogWrite(motorL, motor_l);
}

void p_control () {
  error = sensor[0] * (-4)+ sensor[1] * (-3) + sensor[2] * (-2) + sensor[3] * (-1) + sensor[4] * 1 + sensor[5] * 2 + sensor[6] * 3 + sensor[7] * 4;

  p = kp * error;

  if (p > 255) {
    p = 255;
  } else if (p < -255) {
    p = -255;
  } else {
    ;
  }

  rightpwm = power * ((p + 255.0) / 510);
  leftpwm  = power * ((255.0 - p) / 510);
  //pos = map(p, -255, 255, 120, 30);
  pos = (p + 255) * (30 - 120) / 510 + 120;
  pos = kp_pos * pos;
}
