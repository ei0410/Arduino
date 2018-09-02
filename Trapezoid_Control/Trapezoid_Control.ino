typedef enum {
  INIT,
  CW_ACCEL,
  CW_MAX,
  CW_DECEL,
  NONE
} MotorStatus;

MotorStatus gMotorStatus = INIT;

const int in1 = 3;
const int in2 = 4; 

const int out1 = 10;
const int out2 = 11;

int pwm = 0;

void setup() {
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  digitalWrite(out2, LOW);
}

void loop() {
  int in1_switch = digitalRead(in1);

  switch (gMotorStatus) {
    case INIT:
      if (in1_switch == HIGH) {
        gMotorStatus = CW_ACCEL;
      }
      break;
    case CW_ACCEL:
      pwm++;
      if (in1_switch == LOW) {
        gMotorStatus = CW_DECEL;
      }
      if (pwm >= 255) {
        gMotorStatus = CW_MAX;
      }
      break;
    case CW_MAX:
      if (in1_switch == LOW) {
        gMotorStatus = CW_DECEL;
      }
      break;
    case CW_DECEL:
      pwm--;
      if (in1_switch == HIGH) {
        gMotorStatus = CW_ACCEL;
      }
      if (pwm <= 0) {
        gMotorStatus = INIT;
      }
      break;
    case NONE:
      break;
    default:
      break;
  }
  analogWrite(out1 ,pwm);
  //delay(10);
}
