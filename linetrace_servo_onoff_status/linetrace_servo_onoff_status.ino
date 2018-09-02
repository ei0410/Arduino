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

Servo myservo;
const int servopin = 8;
int pos = 75;
//from 30 to 120

int threshold[8] = {600, 600, 600, 600, 600, 600, 600, 600};
const int motorR = 11;
const int motorL = 12;

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

  if (sensor[0] < threshold[0]){
    trace += 1;
  }
  if (sensor[1] < threshold[1]){
    trace += 2;
  }
  if (sensor[2] < threshold[2]){
    trace += 4;
  }
  if (sensor[3] < threshold[3]){
    trace += 8;
  }
  if (sensor[4] < threshold[4]) {
    trace += 16;
  }
  if (sensor[5] < threshold[5]) {
    trace += 32;
  }
  if (sensor[6] < threshold[6]){
    trace += 64;
  }
  if (sensor[7] < threshold[7]) {
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
      linetrace();
      break;
    case TURN_R:
      Motor(80, 0);
      myservo.write(30);
      if (trace == 14) {  //00001100
        gStatus = TRACE;
      } else {
        ;
      }
      break;
    case TURN_L:
      Motor(0, 80);
      myservo.write(120);
      if (trace == 48) { //00110000
        gStatus = TRACE;
      } else {
        ;
      }
      break;
    case CROSS_LINE:
      cross_count = cross_count + 1;
      delay(1000);
      if (cross_count > 4) {
        gStatus = STOP;
      } else {
        gStatus = TRACE;
      }
      break;
    case STOP:
      Motor(0, 0);
      myservo.write(75);
      break;
  }

  #ifdef DEBUG
  Serial.print(cross_count);
  Serial.print("\t");
  Serial.print(trace);
  Serial.print("\t");
  Serial.print(pos);
  Serial.print("\t");
  Serial.println(gStatus);
  #endif

  trace = 0;
  //delay(60);
}

void Motor(int motor_r, int motor_l) {
  analogWrite(motorR, motor_r);
  analogWrite(motorL, motor_l);
}

void linetrace () {
  switch (trace) {
    case 1:  //00000001
      Motor(40, 0);
      pos = 45;
      break;
    case 3:  //00000011
      Motor(50, 20);
      pos = 50;
      break;
    case 7:  //00000111
      Motor(60, 30);
      pos = 55;
      break;
    case 6:  //00000110
      Motor(70, 60);
      pos = 60;
      break;
    case 14: //00001110
      Motor(80, 70);
      pos = 65;
      break;
    case 12: //00001100
      Motor(80, 70);
      pos = 70;
      break;
    case 28: //00011100
      Motor(80, 80);
      pos = 70;
      break;
    case 24: //00011000
      Motor(90, 90);
      pos = 75;
      break;
    case 56: //00111000
      Motor(80, 80);
      pos = 80;
      break;
    case 48: //00110000
      Motor(70, 80);
      pos = 80;
      break;
    case 112://01110000
      Motor(70, 80);
      pos = 85;
      break;
    case 96: //01100000
      Motor(60, 70);
      pos = 90;
      break;
    case 224://11100000
      Motor(30, 60);
      pos = 95;
      break;
    case 192://11000000
      Motor(20, 50);
      pos = 100;
      break;
    case 128://10000000
      Motor(0, 40);
      pos = 105;
      break;
//    case 15: //00001111
    case 31: //00011111
    case 63: //00111111
      delay(300);
      if (trace == 31 || trace == 63) {
        gStatus = TURN_R;
      } else {
        gStatus = TRACE;
      }
      break;
//    case 240://11110000
    case 248://11111000
    case 252://11111100
      delay(300);
      if(trace == 248 || trace == 252) {
        gStatus = TURN_L;
      } else {
        gStatus = TRACE;
      }
      break;
    case 255://11111111
      gStatus = CROSS_LINE;
      break;
    default:
      break;
    }
  myservo.write(pos);
}
