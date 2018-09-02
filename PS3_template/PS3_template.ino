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
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS3.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
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
        Serial.print(F("\r\nUp"));
      }
      if (PS3.getButtonPress(RIGHT)) {
        Serial.print(F("\r\nRight"));
      }
      if (PS3.getButtonPress(DOWN)) {
        Serial.print(F("\r\nDown"));
      }
      if (PS3.getButtonPress(LEFT)) {
        Serial.print(F("\r\nLeft"));
      }

      if (PS3.getButtonPress(L1)) {
        Serial.print(F("\r\nL1"));
      }
      if (PS3.getButtonPress(R1)) {
        Serial.print(F("\r\nR1"));
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
