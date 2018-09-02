#include <Servo.h>

int yaw  = 90;
int roll = 150;

const int yaw_min = 0;
const int yaw_max = 180;
const int roll_min = 50;
const int roll_max = 160;

Servo servo_yaw;
Servo servo_roll;

void setup() {
  servo_yaw.attach(8);
  servo_roll.attach(9);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(2) == LOW) {
    yaw++;
    delay(10);
  }
  if(digitalRead(3) == LOW) {
    yaw--;
    delay(10);
  }
  if(digitalRead(5) == LOW) {
    roll++;
    delay(10);
  }
  if(digitalRead(6) == LOW) {
    roll--;
    delay(10);
  }

  if (yaw < yaw_min) {
    yaw = yaw_min;
  } else if (yaw > yaw_max) {
    yaw = yaw_max;
  } else {
    ;
  }

  if (roll < roll_min) {
    roll = roll_min;
  } else if (roll > roll_max) {
    roll = roll_max;
  } else {
    ;
  }

  servo_yaw.write(yaw);
  servo_roll.write(roll);
}
