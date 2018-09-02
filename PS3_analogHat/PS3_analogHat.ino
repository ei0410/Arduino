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

int direction(int x,int y){
  double deg,rad;
  int pattern = 0;
  x -= 128; //中心(0,0)の座標平面に変換
  y = abs(y - 256) - 128;
  rad = atan2((double)y,(double)x);
  deg = rad * 180.0 /(atan(1.0) * 4.0); //ラジアンを度に変換
  if(abs(x) > 16 || abs(y)> 16){ // x,yが16以下の時は0を返す
    //pattern = 12;
    deg += 180.0;// 0<=deg<=360として方向を判別
    for(int i = 0;i < 12;i++){
      if(deg >= 0.0 + (i * 30.0) && deg < 30.0 + (i * 30.0))
        pattern = i + 1;
    }
    Serial.print(deg);
  }
  return pattern;
}

void setup() {
  for (int i = 3; i <= 6; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  for (int i = 22; i <= 29; i++) {
    pinMode(i, OUTPUT);
  }
  
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
    
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }
    
    switch(direction(PS3.getAnalogHat(LeftHatX),PS3.getAnalogHat(LeftHatY))){
    case 0:
      Stop();
      break;
    case 1:
    case 12:
      Serial.print(F("\r\nLeft"));
      Left();
      break;
    case 2:
      Serial.print(F("\r\nDown+Left"));
      Down_Left();
      break;
    case 3:
    case 4:
      Serial.print(F("\r\nDown"));
      Down();
      break;
    case 5:
      Serial.print(F("\r\nDown+Right"));
      Down_Right();
      break;
    case 6:
    case 7:
      Serial.print(F("\r\nRight"));
      Right();
      break;
    case 8:
      Serial.print(F("\r\nUp+Right"));
      Up_Right();
      break;
    case 9:
    case 10:
      Serial.print(F("\r\nUp"));
      Up();
      break;
    case 11:
      Serial.print(F("\r\nUp+Left"));
      Up_Left();
      break;
    default:
      Stop();
      break;
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

      if (PS3.getButtonPress(L1))
        Serial.print(F("\r\nL1"));
      if (PS3.getButtonPress(R1))
        Serial.print(F("\r\nR1"));

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

void Stop() {
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
}

void Up() {
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);
}

void Up_Right() {
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
}

void Right() {
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  digitalWrite(28, LOW);
  digitalWrite(29, HIGH);
}

void Down_Right() {
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, HIGH);
}

void Down() {
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, HIGH);
}

void Down_Left() {
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
}

void Left() {
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);
}

void Up_Left() {
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);
}
