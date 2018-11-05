#include <PS3BT.h>
#include <usbhub.h>
#include <Servo.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

Servo servo;

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
  for (int i = 2; i < 7; i++) {
    pinMode(i, OUTPUT);
  }

  servo.attach(6);
  servo.write(90);
  
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

  int servo_pos = 90;

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
      Serial.print(F("\r\nStop"));
      Stop();
      break;
    case 1:
    case 2:
    case 12:
      Serial.print(F("\r\nUp"));
      Up();
      servo_pos = 90;
      break;
    case 3:
    case 4:
    case 5:
      Serial.print(F("\r\nLeft"));
      Left();
      servo_pos = 45;
      break;
    case 6:
    case 7:
    case 8:
      Serial.print(F("\r\nDown"));
      Down();
      servo_pos = 90;
      break;
    case 9:
    case 10:
    case 11:
      Serial.print(F("\r\nRight"));
      Right();
      servo_pos = 135;
      break;
    default:
      Stop();
      break;
    }

    servo.write(servo_pos);

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
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void Up() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

void Right() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

void Down() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}

void Left() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}
