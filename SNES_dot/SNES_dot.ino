#include <SNESpad.h>
#include <TimerOne.h>

SNESpad pad = SNESpad(6, 7, 8);

const int anode_pins[] = {32, 33, 34, 35, 36, 37, 38, 39};
const int cathode_pins[] = {40, 41, 42, 43, 44, 45, 46, 47};
const int number_of_anode_pins = sizeof(anode_pins) / sizeof(anode_pins[0]);
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);

int callbackCycle = 1000;

int input = 0;
int old_input = 0;
int x = 0;
int y = 0;
int px = 0;
int py = 0;

void callback() {
  input = pad.buttons();
  if (old_input == 0 && input == 16) {
    py = y;
    y = y - 1;
    if (y < 0) {
      y = 0;
      py = 1;
    }
  } else if (old_input == 0 && input == 32) {
    py = y;
    y = y + 1;
    if (y > 7) {
      y = 7;
      py = 6;
    }
  } else if (old_input == 0 && input == 64) {
    px = x;
    x = x - 1;
    if (x < 0) {
      x = 0;
      px = 1;
    }
  } else if (old_input == 0 && input == 128) {
    px = x;
    x = x + 1;
    if (x > 7) {
      x = 7;
      px = 6;
    }
  } else {
    ;
  }
  old_input = input;
}

void setup() {
  for (int i = 0; i < number_of_anode_pins; i++) {
    pinMode(anode_pins[i], OUTPUT);
    digitalWrite(anode_pins[i], LOW);
  }

  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);
    digitalWrite(cathode_pins[i], HIGH);
  }

  Timer1.initialize(callbackCycle);
  Timer1.attachInterrupt(callback);
}

void loop() {
  digitalWrite(cathode_pins[x], LOW);
  digitalWrite(anode_pins[y], HIGH);
  digitalWrite(cathode_pins[px], HIGH);
  digitalWrite(anode_pins[py], LOW);
}
