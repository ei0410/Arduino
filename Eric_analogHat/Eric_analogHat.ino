#include "analogHat.h"
#include "omni.h"

#include <PS3BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);
bool printTemperature, printAngle;

const int split = 12;
analogHat analogL = analogHat(split);
analogHat analogR = analogHat(split);

const int pin1 = 22;
const int pin2 = 23;
const int pin3 = 24;
const int pin4 = 25;
const int pin5 = 26;
const int pin6 = 27;
const int pin7 = 28;
const int pin8 = 29;

omni omni4 = omni(pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8);

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial);
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeft_pattern: "));
      Serial.print(analogL.get_pattern(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)));
      Serial.print(F("\tLeft_radius: "));
      Serial.print(analogL.get_radius(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)));
      Serial.print(F("\tRight_pattern: "));
      Serial.print(analogR.get_pattern(PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(RightHatY)));
      Serial.print(F("\tRight_radius: "));
      Serial.print(analogR.get_radius(PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(RightHatY)));
    }
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      Serial.print(F("\tR2: "));
      Serial.print(PS3.getAnalogButton(R2));
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonPress(TRIANGLE)) {
        Serial.print(F("\r\nTraingle"));
      }
      if (PS3.getButtonPress(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
      }
      if (PS3.getButtonPress(CROSS)) {
        Serial.print(F("\r\nCross"));
      }
      if (PS3.getButtonPress(SQUARE)) {
        Serial.print(F("\r\nSquare"));
      }

      if (PS3.getButtonPress(UP)) {
        omni4.digital_direction(0, 1, 1, 0, 0, 1, 1, 0);
        Serial.print(F("\r\nUp"));
      } else if (PS3.getButtonPress(RIGHT)) {
        omni4.digital_direction(1, 0, 1, 0, 1, 0, 1, 0);
        Serial.print(F("\r\nRight"));
      } else if (PS3.getButtonPress(DOWN)) {
        omni4.digital_direction(1, 0, 0, 1, 1, 0, 0, 1);
        Serial.print(F("\r\nDown"));
      } else if (PS3.getButtonPress(LEFT)) {
        omni4.digital_direction(0, 1, 0, 1, 0, 1, 0, 1);
        Serial.print(F("\r\nLeft"));
      } else if (PS3.getButtonPress(L1)) {
        omni4.digital_direction(0, 1, 1, 0, 1, 0, 0, 1);
        Serial.print(F("\r\nL1"));
      } else if (PS3.getButtonPress(R1)) {
        omni4.digital_direction(1, 0, 0, 1, 0, 1, 1, 0);
        Serial.print(F("\r\nR1"));
      } else {
        omni4.digital_direction(0, 0, 0, 0, 0, 0, 0, 0);
      }
      
      if (PS3.getButtonClick(L3)) {
        Serial.print(F("\r\nL3"));
      }
      if (PS3.getButtonClick(R3)) {
        Serial.print(F("\r\nR3"));
      }
      
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    }
  }
}
