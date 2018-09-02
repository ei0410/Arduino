#include <PS2X_lib.h>

//don't push an "ANALOG" button!!!
//if you push an "ANALOG" button, you can't use analogHats.

PS2X ps2x;

int error = 0; 
byte vibrate = 0;

const int clock_pin = 13;
const int command_pin = 11;
const int attention_pin = 10;
const int data_pin = 12;

void setup(){
  Serial.begin(115200);
  ps2x.config_gamepad(clock_pin, command_pin, attention_pin, data_pin, true, true);
}

void loop(){
  ps2x.read_gamepad(false, vibrate);

  if (ps2x.Analog(PSS_LX) > 150 || ps2x.Analog(PSS_LX) < 90 || ps2x.Analog(PSS_LY) > 150 || ps2x.Analog(PSS_LY) < 90 || ps2x.Analog(PSS_RX) > 150 || ps2x.Analog(PSS_RX) < 90 || ps2x.Analog(PSS_RY) > 150 || ps2x.Analog(PSS_RY) < 90) {
    Serial.print("\r\nLeftHatX: ");
    Serial.print(ps2x.Analog(PSS_LX));
    Serial.print("\tLeftHatY: ");
    Serial.print(ps2x.Analog(PSS_LY));
    Serial.print("\tRightHatX: ");
    Serial.print(ps2x.Analog(PSS_RX));
    Serial.print("\tRightHatY: ");
    Serial.print(ps2x.Analog(PSS_RY));
  }

  if (ps2x.Button(PSB_GREEN)) {
    Serial.println("Triangle");
  }    
  if (ps2x.Button(PSB_RED)) {
    Serial.println("Circle");
  }
  if (ps2x.Button(PSB_BLUE)) {
    Serial.println("Cross");    
  }
  if (ps2x.Button(PSB_PINK)) {
    Serial.println("Square");
  }
  
  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("Up");
  }
  if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("Right");
  }
  if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("DOWN");
  }  
  if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("LEFT");
  }
  
  if (ps2x.Button(PSB_L1)) {
    Serial.println("L1");
  }
  if (ps2x.Button(PSB_L2)) {
    Serial.println("L2");
  }
  if (ps2x.Button(PSB_L3)) {
    Serial.println("L3");
  }
  if (ps2x.Button(PSB_R1)) {
    Serial.println("R1");
  }
  if (ps2x.Button(PSB_R2)) {
    Serial.println("R2");
  }
  if (ps2x.Button(PSB_R3)) {
    Serial.println("R3");
  }

  if (ps2x.Button(PSB_SELECT)) {
    Serial.println("Select");
  }
  if (ps2x.Button(PSB_START)) {
    Serial.println("Start");
  }
}
