#include <PS2X_lib.h>

PS2X ps2x;

int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
  Serial.begin(57600);
  
  error = ps2x.config_gamepad(13,11,10,12, true, true);
 
  if (error == 0){
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  } else if (error == 1) {
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  } else if (error == 2) {
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  } else if (error == 3) {
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  }
  
  type = ps2x.readType();
  
  switch(type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
}

void loop(){
  if (error == 1) {
    return; 
  }
  
  if (type == 2){
    ps2x.read_gamepad();
  
    if (ps2x.ButtonPressed(GREEN_FRET)) {
      Serial.println("Green Fret Pressed");
    }
    if (ps2x.ButtonPressed(RED_FRET)) {
      Serial.println("Red Fret Pressed");
    }
    if (ps2x.ButtonPressed(YELLOW_FRET)) {
      Serial.println("Yellow Fret Pressed");
    }
    if (ps2x.ButtonPressed(BLUE_FRET)) {
      Serial.println("Blue Fret Pressed");
    }
    if (ps2x.ButtonPressed(ORANGE_FRET)) {
      Serial.println("Orange Fret Pressed");
    }
    if (ps2x.ButtonPressed(STAR_POWER)) {
      Serial.println("Star Power Command");
    }
    if (ps2x.Button(UP_STRUM)) {
      Serial.println("Up Strum");
    }
    if (ps2x.Button(DOWN_STRUM)) {
      Serial.println("DOWN Strum");
    }
    if (ps2x.Button(PSB_START)) {
       Serial.println("Start is being held");
    }
    if (ps2x.Button(PSB_SELECT)) {
       Serial.println("Select is being held");
    }
    if (ps2x.Button(ORANGE_FRET)) {
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
  } else {
    ps2x.read_gamepad(false, vibrate);
    
    if (ps2x.Button(PSB_START)) {
      Serial.println("Start is being held");
    }
    if (ps2x.Button(PSB_SELECT)) {
      Serial.println("Select is being held");
    }   
    if (ps2x.Button(PSB_PAD_UP)) {
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

    vibrate = ps2x.Analog(PSAB_BLUE);   
    
    if (ps2x.NewButtonState()) {
      if (ps2x.Button(PSB_L3)) {
        Serial.println("L3 pressed");
      }
      if (ps2x.Button(PSB_R3)) {
        Serial.println("R3 pressed");
      }
      if (ps2x.Button(PSB_L2)) {
        Serial.println("L2 pressed");
      }
      if (ps2x.Button(PSB_R2)) {
        Serial.println("R2 pressed");
      }
      if (ps2x.Button(PSB_GREEN)) {
        Serial.println("Triangle pressed");
      }
    }   
         
    if (ps2x.ButtonPressed(PSB_RED)) {
      Serial.println("Circle just pressed");
    }    
    if (ps2x.ButtonReleased(PSB_PINK)) {
      Serial.println("Square just released");
    }     
    if (ps2x.NewButtonState(PSB_BLUE)) {
      Serial.println("Cross just changed");    
    }
    
    if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) {
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC);
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }
  }
  delay(50);  
}
