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

#define MODE_STOP  0
#define MODE_CW    1
#define MODE_CCW   2
#define MODE_BRAKE 3

const int in1 = 2;
const int in2 = 4; 

const int out1 = 3;
const int out2 = 5;

int pwm = 0;

void setup() {
  Serial.begin(9600);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
}

void loop() {
  int in1_switch = digitalRead(in1);
  int in2_switch = digitalRead(in2);

  int mode = 0;
  
  if ((in1_switch == LOW) && (in2_switch == LOW)) {
    mode = MODE_STOP;
  } else if ((in1_switch == HIGH) && (in2_switch == LOW)) {
    mode = MODE_CW;
  } else if ((in1_switch == LOW) && (in2_switch == HIGH)) {
    mode = MODE_CCW;
  } else if ((in1_switch == HIGH) && (in2_switch == HIGH)){
    mode = MODE_BRAKE;
  } else {
    ;
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
      analogWrite(out1, 0);
      analogWrite(out2, 0);
      Serial.println(pwm);
      break;
    case CW_ACCEL:
      pwm++;
      if (mode == MODE_STOP || mode == MODE_BRAKE || mode == MODE_CCW) {
        gMotorStatus = CW_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        gMotorStatus = CW_MAX;
      }
      analogWrite(out1, pwm);
      analogWrite(out2, 0);
      Serial.println(pwm);
      break;
    case CW_MAX:
      if (mode == MODE_STOP || mode == MODE_BRAKE || mode == MODE_CCW) {
        gMotorStatus = CW_DECEL;
      } else {
        ;
      }
      analogWrite(out1, pwm);
      analogWrite(out2, 0);
      Serial.println(pwm);
      break;
    case CW_DECEL:
      pwm--;
      if (mode == MODE_CW) {
        gMotorStatus = CW_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        gMotorStatus = INIT;
      }
      analogWrite(out1, pwm);
      analogWrite(out2, 0);
      Serial.println(pwm);
      break;
    case CCW_ACCEL:
      pwm++;
      if (mode == MODE_STOP || mode == MODE_BRAKE || mode == MODE_CW) {
        gMotorStatus = CCW_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        gMotorStatus = CCW_MAX;
      }
      analogWrite(out1, 0);
      analogWrite(out2, pwm);
      Serial.println(-pwm);
      break;
    case CCW_MAX:
      if (mode == MODE_STOP || mode == MODE_BRAKE || mode == MODE_CW) {
        gMotorStatus = CCW_DECEL;
      } else {
        ;
      }
      analogWrite(out1, 0);
      analogWrite(out2, pwm);
      Serial.println(-pwm);
      break;
    case CCW_DECEL:
      pwm--;
      if (mode == MODE_CCW) {
        gMotorStatus = CCW_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        gMotorStatus = INIT;
      }
      analogWrite(out1, 0);
      analogWrite(out2, pwm);
      Serial.println(-pwm);
      break;
    case NONE:
      break;
    default:
      break;
  }
  delay(5);
}
