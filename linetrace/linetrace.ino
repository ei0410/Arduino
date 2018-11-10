#include <SNESpad.h>
#include <Servo.h>

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

Servo servo;
const int servo_pin = 6;
int servo_pos = 90;

void setup() {
  for (int i = 2; i < 7; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  
  servo.attach(servo_pin);
  servo.write(servo_pos);
  
  Serial.begin(9600);
}

void loop() {
  int state = nintendo.buttons();

  switch(state) {
    case UP_SW:
      Up(255, 255);
      break;
    case DOWN_SW:
      Down(255, 255);
      break;
    case L_SW:
      servo_pos = 45;
      break;
    case R_SW:
      servo_pos = 135;
      break;
    default:
      servo_pos = 90;
      Stop();
      break;
  }
  servo.write(servo_pos);
  
  Serial.println(state);
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
