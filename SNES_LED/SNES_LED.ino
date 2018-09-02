#include <SNESpad.h>
#include <TimerOne.h>

#define DEBUG

SNESpad pad = SNESpad(2, 3, 4);

const int ledpin = 13;

int callbackCycle = 1000;
int dt = 1000;

void callback() {
  int input = pad.buttons();
  if (input == 1) {           //B
    dt = 50;
  } else if (input == 2) {    //Y
    dt = 100;
  } else if (input == 4) {    //Select
    dt = 150;
  } else if (input == 8) {    //Start
    dt = 200;
  } else if (input == 16) {   //Up 
    dt = 250;
  } else if (input == 32) {   //Down
    dt = 300;
  } else if (input == 64) {   //Left
    dt = 350;
  } else if (input == 128) {  //Right
    dt = 400;
  } else if (input == 256) {  //A
    dt = 450;
  } else if (input == 512) {  //X
    dt = 500;
  } else if (input == 1024) { //L
    dt = 550;
  } else if (input == 2048) { //R
    dt = 600;
  }
  #ifdef DEBUG
  Serial.println(input);
  #endif
}

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif 
  
  pinMode(ledpin, OUTPUT);

  Timer1.initialize(callbackCycle);
  Timer1.attachInterrupt(callback);
}

void loop() {
  digitalWrite(ledpin, HIGH);
  delay(dt);
  digitalWrite(ledpin, LOW);
  delay(dt);
}
