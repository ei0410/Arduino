#include <SNESpad.h>
#include <Servo.h>

#define NONE      0
#define B_SW      1
#define Y_SW      2
#define SELECT_SW 4
#define START_SW  8
#define UP_SW     16
#define DOWN_SW   32
#define LEFT_SW   64
#define RIGHT_SW  128
#define A_SW      256
#define X_SW      512
#define L_SW      1024
#define R_SW      2048

//latch/clock/data
//orange/yellow/red
SNESpad nintendo = SNESpad(8, 9, 10);
int old_state;

#define SERVO_MIN     45
#define SERVO_DEFAULT 90
#define SERVO_MAX     135
#define SERVO_STEP    5

Servo servo;
const int servo_pin = 6;
int servo_pos = SERVO_DEFAULT;

#define PWM_MAX 255
#define PWM_DEFAULT 150
#define PWM_MIN 50
#define PWM_STEP 10

int r_pwm = PWM_DEFAULT;
int l_pwm = PWM_DEFAULT;

void setup() {
  for (int i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  digitalWrite(7, HIGH);
  // 7pin is Vcc for SNESpad
  
  servo.attach(servo_pin);
  servo.write(SERVO_DEFAULT);
}

void loop() {
  int state = nintendo.buttons();

//  if ((state == X_SW) && (old_state == NONE)) {
//    l_pwm += PWM_STEP;
//    r_pwm += PWM_STEP;
//    if (l_pwm > PWM_MAX) {
//      l_pwm = PWM_MAX;
//    }
//    if (r_pwm > PWM_MAX) {
//      r_pwm = PWM_MAX;
//    }
//  } else if ((state == B_SW) && (old_state == NONE)) {
//    l_pwm -= PWM_STEP;
//    r_pwm -= PWM_STEP;
//    if (l_pwm < PWM_MIN) {
//      l_pwm = PWM_MIN;
//    }
//    if (r_pwm < PWM_MIN) {
//      r_pwm = PWM_MIN;
//    }
//  }
  
  if (state == UP_SW) {
    Up(l_pwm, r_pwm);
  } else if (state == DOWN_SW) {
    Down(l_pwm, r_pwm);
  } else {
    Stop();
  }
  
  if ((state == L_SW) && (old_state == NONE)) {
//    servo_pos -= SERVO_STEP;
//    if (servo_pos < SERVO_MIN) {
//      servo_pos = SERVO_MIN;
//    }
    servo_pos = SERVO_MIN;
  } else if ((state == R_SW) && (old_state == NONE)) {
//    servo_pos += SERVO_STEP;
//    if (servo_pos > SERVO_MAX) {
//      servo_pos = SERVO_MAX;
//    }
    servo_pos = SERVO_MAX;
  } else if (state == SELECT_SW) {
    servo_pos = SERVO_DEFAULT;
  }
  
  servo.write(servo_pos);

  old_state = state;
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
