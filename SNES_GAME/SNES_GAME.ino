#define DEBUG

typedef enum {
  INIT,   //0
  CURSOR, //1
  FLOW_X, //2
  FLOW_Y, //3
  RANDOM, //4
  HELIX,  //5
  NONE
} Status;

Status gStatus = INIT;

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
int px = 1;
int py = 1;

int delay_time = 15;

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
  } else if (old_input == 0 && input == 1024) {
    delay_time = delay_time + 5;
    if (delay_time > 300) {
      delay_time = 300;
    } else {
      ;
    }
  } else if (old_input == 0 && input == 2048) {
    delay_time = delay_time - 5;
    if (delay_time < 10) {
      delay_time = 10;
    } else {
      ;
    }
  } else if (old_input == 0 && input == 512) {
    gStatus = FLOW_X;
  } else if (old_input == 0 && input == 2) {
    gStatus = FLOW_Y;
  } else if (old_input == 0 && input == 256) {
    gStatus = RANDOM;
  } else if (old_input == 0 && input == 1) {
    gStatus = HELIX;
  } else {
    ;
  }
  old_input = input;
}

void reset() {
  for (int i = 0; i < number_of_anode_pins; i++) {
    digitalWrite(anode_pins[i], LOW);
  }
  for (int i = 0; i < number_of_cathode_pins; i++) {
    digitalWrite(cathode_pins[i], HIGH);
  }
}

void flow_x() {
  for (int i = 0; i < number_of_cathode_pins; i++) {
    for (int j = 0; j < number_of_anode_pins; j++) {
      digitalWrite(cathode_pins[j], LOW);
      digitalWrite(anode_pins[i], HIGH);
      delay(delay_time);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
  }
}

void flow_y() {
  for (int i = 0; i < number_of_cathode_pins; i++) {
    for (int j = 0; j < number_of_anode_pins; j++) {
      digitalWrite(cathode_pins[i], LOW);
      digitalWrite(anode_pins[j], HIGH);
      delay(delay_time);
      digitalWrite(cathode_pins[i], HIGH);
      digitalWrite(anode_pins[j], LOW);
    }
  }
}

void random_point() {
  for (int i = 0; i < 100; i++) {
    int anode_pin = anode_pins[random(number_of_anode_pins)];
    int cathode_pin = cathode_pins[random(number_of_cathode_pins)];
    digitalWrite(cathode_pin, LOW);
    digitalWrite(anode_pin, HIGH);
    delay(delay_time);
    digitalWrite(cathode_pin, HIGH);
    digitalWrite(anode_pin, LOW);
  }
}

void helix() {

  int i = 0;
  int j = 0;
  int a = 0;
  
  for (a = 0; a < 4; a++) {
    for (i ; i < number_of_anode_pins - a; i++) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delay_time);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i - 1;
    j = j + 1;
    for (j ; j < number_of_cathode_pins - a; j++) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delay_time);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i - 1;
    j = j - 1;
    for (i ; i > 0 - 1 + a; i--) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delay_time);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i + 1;
    j = j - 1;
    for (j ; j > 0 + a; j--) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delay_time);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i + 1;
    j = j + 1;
  }
}

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  for (int i = 0; i < number_of_anode_pins; i++) {
    pinMode(anode_pins[i], OUTPUT);
  }

  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);
  }

  Timer1.initialize(callbackCycle);
  Timer1.attachInterrupt(callback);
}

void loop() {
  switch(gStatus) {
    case INIT:
      reset();
      gStatus = CURSOR;
      break;
    case CURSOR:
      digitalWrite(cathode_pins[x], LOW);
      digitalWrite(anode_pins[y], HIGH);
      digitalWrite(cathode_pins[px], HIGH);
      digitalWrite(anode_pins[py], LOW);
      break;
    case FLOW_X:
      reset();
      flow_x();
      gStatus = CURSOR;
      break;
    case FLOW_Y:
      reset();
      flow_y();
      gStatus = CURSOR;
      break;
    case RANDOM:
      reset();
      random_point();
      gStatus = CURSOR;
      break;
    case HELIX:
      reset();
      helix();
      gStatus = CURSOR;
      break;
    default:
      break;
  }
  #ifdef DEBUG
  Serial.print(input);
  Serial.print("\t");
  Serial.print(delay_time);
  Serial.print("\t");
  Serial.println(gStatus);
  #endif
}
