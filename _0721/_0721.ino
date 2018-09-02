#include <TimerOne.h>

typedef enum {
  INIT,
  ACCEL,
  MAX,
  DECEL,
  NONE
} MotorStatus;

MotorStatus gMotorStatus = INIT;

const int in  = 2;
const int out = 3;
float pwm    = 0;

float count_on;
float count_off;
int count_max;

int gTon  = 1000; //accel_time_ms
int gToff = 1000; //decel_time_ms
int gMax  = 3000; //max_time_ms 

int callbackCycle = 10000; //us

void callback() {
  int currStatus = digitalRead(in);
  static int prevStatus = LOW;

  switch (gMotorStatus) {
    case INIT:
      if (prevStatus == LOW && currStatus == HIGH) {
        gMotorStatus = ACCEL;
      } else {
        ;
      }
      break;
    case ACCEL:
      execAccel();
      break;
    case MAX:
      execMax();
      break;
    case DECEL:
      execDecel();
      break;
    case NONE:
      break;
    default:
      break;
  }
  prevStatus = currStatus;
}

void execAccel() {
  static int i = 0;

  pwm = 255 / count_on * i;
  Serial.println(pwm);
  analogWrite(out, int(pwm));
  
  if (count_on > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = MAX;
  }
}

void execMax() {
  static int i = 0;

  pwm = 255;
  Serial.println(pwm);
  analogWrite(out, int(pwm));

  if (count_max > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = DECEL;
  }
}

void execDecel() {
  static int i = 0;

  pwm = 255 - 255 / count_off * i;
  Serial.println(pwm);
  analogWrite(out, int(pwm));

  if (count_off > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = INIT;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(in, INPUT);
  pinMode(out, OUTPUT);

  count_on  = gTon  / 10; //ms
  count_off = gToff / 10; //ms
  count_max = gMax  / 10; //ms

  Timer1.initialize(callbackCycle);
  Timer1.attachInterrupt(callback);
}

void loop() {
  
}
