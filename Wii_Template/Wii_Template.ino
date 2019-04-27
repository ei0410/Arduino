#include <Wii.h>
#include <usbhub.h>
#include <SPI.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

USB Usb;
BTD Btd(&Usb); 
WII Wii(&Btd, PAIR);

bool printAngle = false; // if you want to use sensors, you set true.

int direction(int x, int y, int pattern){
  x -= 130; 
  y -= 130;
  
  double rad = atan2((double)y,(double)x);
  double deg = rad * 180.0 /(atan(1.0) * 4.0);
  
  if (abs(x) > 16 || abs(y) > 16) {
    double div = 360.0/pattern;
    deg += 180.0;
    for(int i = 0; i < pattern; i++) {
      if(deg >= (i*div)-div/2.0 && deg < (i*div)+div/2.0) {
        pattern = i+1;
      }
    }
    if (deg >= 360.0-div/2.0 && deg < 360.0) {
      pattern = 1;
    }
  } else {
    pattern = 0;
  }
  
  return pattern;
}

void setup() {
  Serial.begin(115200);
  
  #if !defined(__MIPSEL__)
  while (!Serial);
  #endif
  
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nWiimote Bluetooth Library Started"));
}

void loop() {
  Usb.Task();
  if (Wii.wiimoteConnected) {
    if (Wii.getButtonClick(HOME)) {
      Serial.print(F("\r\nHOME"));
      Wii.disconnect();
    }
    else {
      if (Wii.getButtonPress(LEFT)) {
        Serial.print(F("\r\nLeft"));
      }
      if (Wii.getButtonPress(RIGHT)) {
        Serial.print(F("\r\nRight"));
      }
      if (Wii.getButtonPress(DOWN)) {
        Serial.print(F("\r\nDown"));
      }
      if (Wii.getButtonPress(UP)) {
        Serial.print(F("\r\nUp"));
      }

      if (Wii.getButtonPress(PLUS)) {
        Serial.print(F("\r\nPlus"));
      }
      if (Wii.getButtonPress(MINUS)) {
        Serial.print(F("\r\nMinus"));
      }
      
      if (Wii.getButtonPress(ONE)) {
        Serial.print(F("\r\nOne"));
      }
      if (Wii.getButtonPress(TWO)) {
        Serial.print(F("\r\nTwo"));
      }

      if (Wii.getButtonPress(A)) {
        Serial.print(F("\r\nA"));
      }
      if (Wii.getButtonPress(B)) {
        Serial.print(F("\r\nB"));
      }

      if (Wii.nunchuckConnected) {
        if (Wii.getButtonPress(Z)) {
          Serial.print(F("\r\nZ"));
        }
        if (Wii.getButtonPress(C)) {
          Serial.print(F("\r\nC"));
        }

        switch(direction(Wii.getAnalogHat(HatX), Wii.getAnalogHat(HatY), 8)) {
          case 0:
            //Serial.print(F("\r\n0"));
            break;
          case 1:
            Serial.print(F("\r\n1"));
            break;
          case 2:
            Serial.print(F("\r\n2"));
            break;
          case 3:
            Serial.print(F("\r\n3"));
            break;
          case 4:
            Serial.print(F("\r\n4"));
            break;
          case 5:
            Serial.print(F("\r\n5"));
            break;
          case 6:
            Serial.print(F("\r\n6"));
            break;
          case 7:
            Serial.print(F("\r\n7"));
            break;
          case 8:
            Serial.print(F("\r\n8"));
            break;
          default:
            Serial.print(F("\r\nerror"));
            break;
        }

        /*
        if (Wii.getAnalogHat(HatX) > 137 ||  Wii.getAnalogHat(HatX) < 117 || Wii.getAnalogHat(HatY) > 137 || Wii.getAnalogHat(HatY) < 117) {
          Serial.print(F("\r\nHatX: "));
          Serial.print(Wii.getAnalogHat(HatX));
          Serial.print(F("\tHatY: "));
          Serial.print(Wii.getAnalogHat(HatY));
        }
        */
      }

      if (printAngle) {
        Serial.print(F("\r\nPitch: "));
        Serial.print(Wii.getPitch());
        Serial.print(F("\tRoll: "));
        Serial.print(Wii.getRoll());
        if (Wii.motionPlusConnected) {
          Serial.print(F("\tYaw: "));
          Serial.print(Wii.getYaw());
        }
        
        if (Wii.nunchuckConnected) {
          Serial.print(F("\tNunchuck Pitch: "));
          Serial.print(Wii.getNunchuckPitch());
          Serial.print(F("\tNunchuck Roll: "));
          Serial.print(Wii.getNunchuckRoll());
        }
      }
    }
  }
}
