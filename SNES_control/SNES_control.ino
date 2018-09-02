#include <SNESpad.h>

SNESpad pad = SNESpad(2, 3, 4);

void setup() {
  for (int i = 5; i <= 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  int input = pad.buttons();
  if (input == 16) {
    Up();
  } else if (input == 32) {
    Down();
  } else if (input == 64) {
    Left();
  } else if (input == 128) {
    Right();
  } else {
    Stop();
  }
}

void Up() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void Down() {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

void Left() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void Right() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void Stop() {
  for (int i = 5; i <= 8; i++) {
    digitalWrite(i, LOW);
  }
}

