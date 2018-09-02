#include <TimerOne.h>

typedef enum {
  INIT,
  CW_ACCEL,
  CW_MAX,
  CW_DECEL,
  CCW_ACCEL,
  CCW_MAX,
  CCW_DECEL,
  NONE
} MotorStatus;

MotorStatus gMotorStatus = INIT;

#define MODE_STOP 0
#define MODE_CW 1
#define MODE_CCW 2

const int in1  = 2;
const int in2  = 4;
const int out1 = 3;
const int out2 = 5;

float pwm = 0;

float count_on;
float count_off;
int count_max;

int gTon  = 1000; //accel_time_ms
int gToff = 1000; //decel_time_ms
int gMax  = 1000; //max_time_ms 

int callbackCycle = 10000; //us

void callback() {
  int currStatus1 = digitalRead(in1);
  int currStatus2 = digitalRead(in2);
  static int prevStatus1 = LOW;
  static int prevStatus2 = LOW;

  int mode = 0;

  if ((prevStatus1 == LOW) && (currStatus1 == HIGH)) {
    mode = MODE_CW;
  } else if ((prevStatus2 == LOW) && (currStatus2 == HIGH)) {
    mode = MODE_CCW;
  } else {
    mode = MODE_STOP;
  }
  
  switch (gMotorStatus) {
    case INIT:
      if (mode == MODE_CW) {
        gMotorStatus = CW_ACCEL;
      } else if (mode == MODE_CCW) {
        gMotorStatus = CCW_ACCEL;
      } else {
        ;
      }
      break;
    case CW_ACCEL:
      cw_execAccel();
      break;
    case CW_MAX:
      cw_execMax();
      break;
    case CW_DECEL:
      cw_execDecel();
      break;
      case CCW_ACCEL:
      ccw_execAccel();
      break;
    case CCW_MAX:
      ccw_execMax();
      break;
    case CCW_DECEL:
      ccw_execDecel();
      break;
    case NONE:
      break;
    default:
      break;
  }
  prevStatus1 = currStatus1;
  prevStatus2 = currStatus2;
}

void cw_execAccel() {
  static int i = 0;

  pwm = 255 / count_on * i;
  
  analogWrite(out1, int(pwm));
  analogWrite(out2, 0);
  Serial.println(pwm);
  
  if (count_on > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = CW_MAX;
  }
}

void cw_execMax() {
  static int i = 0;

  pwm = 255;
  
  analogWrite(out1, int(pwm));
  analogWrite(out2, 0);
  Serial.println(pwm);

  if (count_max > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = CW_DECEL;
  }
}

void cw_execDecel() {
  static int i = 0;

  pwm = 255 - 255 / count_off * i;
  
  analogWrite(out1, int(pwm));
  analogWrite(out2, 0);
  Serial.println(pwm);

  if (count_off > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = INIT;
  }
}

void ccw_execAccel() {
  static int i = 0;

  pwm = 255 / count_on * i;
  
  analogWrite(out1, 0);
  analogWrite(out2, int(pwm));
  Serial.println(pwm);
  
  if (count_on > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = CCW_MAX;
  }
}

void ccw_execMax() {
  static int i = 0;

  pwm = 255;
  
  analogWrite(out1, 0);
  analogWrite(out2, int(pwm));
  Serial.println(pwm);
  
  if (count_max > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = CCW_DECEL;
  }
}

void ccw_execDecel() {
  static int i = 0;

  pwm = 255 - 255 / count_off * i;
  
  analogWrite(out1, 0);
  analogWrite(out2, int(pwm));
  Serial.println(pwm);
  
  if (count_off > i) {
    i++;
  } else {
    i = 0;
    gMotorStatus = INIT;
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(in1, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(in2, INPUT);
  pinMode(out2, OUTPUT);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  
  count_on  = gTon  / 10; //ms
  count_off = gToff / 10; //ms
  count_max = gMax  / 10; //ms

  Timer1.initialize(callbackCycle);
  Timer1.attachInterrupt(callback);
}

void loop() {
  
}
