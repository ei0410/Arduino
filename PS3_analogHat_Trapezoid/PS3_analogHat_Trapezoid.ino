#include <TimerOne.h>
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

typedef enum {
  INIT,
  UP_ACCEL,
  UP_MAX,
  UP_DECEL,
  LEFT_ACCEL,
  LEFT_MAX,
  LEFT_DECEL,
  DOWN_ACCEL,
  DOWN_MAX,
  DOWN_DECEL,
  RIGHT_ACCEL,
  RIGHT_MAX,
  RIGHT_DECEL,
  UP_LEFT_ACCEL,
  UP_LEFT_MAX,
  UP_LEFT_DECEL,
  DOWN_LEFT_ACCEL,
  DOWN_LEFT_MAX,
  DOWN_LEFT_DECEL,
  UP_RIGHT_ACCEL,
  UP_RIGHT_MAX,
  UP_RIGHT_DECEL,
  DOWN_RIGHT_ACCEL,
  DOWN_RIGHT_MAX,
  DOWN_RIGHT_DECEL,
  NONE
} MotorStatus;

MotorStatus gMotorStatus = INIT;

#define MODE_STOP       0
#define MODE_UP         1
#define MODE_LEFT       2
#define MODE_DOWN       3
#define MODE_RIGHT      4
#define MODE_UP_LEFT    5
#define MODE_DOWN_LEFT  6
#define MODE_UP_RIGHT   7
#define MODE_DOWN_RIGHT 8

float pwm = 0;
float dpwm_accel = 1;
float dpwm_decel = 3;
int callbackCycle = 10000; //us

void callback() {
  
  int mode = 0;

  switch(direction(PS3.getAnalogHat(LeftHatX),PS3.getAnalogHat(LeftHatY))){
    case 0:
      mode = MODE_STOP;
      break;
    case 1:
    case 12:
      Serial.print(F("\r\nLeft"));
      mode = MODE_LEFT;
      break;
    case 2:
      Serial.print(F("\r\nDown+Left"));
      mode = MODE_DOWN_LEFT;
      break;
    case 3:
    case 4:
      Serial.print(F("\r\nDown"));
      mode = MODE_DOWN;
      break;
    case 5:
      Serial.print(F("\r\nDown+Right"));
      mode = MODE_DOWN_RIGHT;
      break;
    case 6:
    case 7:
      Serial.print(F("\r\nRight"));
      mode = MODE_RIGHT;
      break;
    case 8:
      Serial.print(F("\r\nUp+Right"));
      mode = MODE_UP_RIGHT;
      break;
    case 9:
    case 10:
      Serial.print(F("\r\nUp"));
      mode = MODE_UP;
      break;
    case 11:
      Serial.print(F("\r\nUp+Left"));
      mode = MODE_UP_LEFT;
      break;
    default:
      Stop();
      break;
    }
  
  switch (gMotorStatus) {
    case INIT:
      if (mode == MODE_UP) {
        gMotorStatus = UP_ACCEL;
      } else if (mode == MODE_LEFT) {
        gMotorStatus = LEFT_ACCEL;
      } else if (mode == MODE_DOWN) {
        gMotorStatus = DOWN_ACCEL;
      } else if (mode == MODE_RIGHT) {
        gMotorStatus = RIGHT_ACCEL;
      } else if (mode == MODE_UP_LEFT) {
        gMotorStatus = UP_LEFT_ACCEL;
      } else if (mode == MODE_DOWN_LEFT) {
        gMotorStatus = DOWN_LEFT_ACCEL;
      } else if (mode == MODE_UP_RIGHT) {
        gMotorStatus = UP_RIGHT_ACCEL;
      } else if (mode == MODE_DOWN_RIGHT) {
        gMotorStatus = DOWN_RIGHT_ACCEL;
      } else {
        ;
      }
      Stop();
      break;
    case UP_ACCEL:
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = UP_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = UP_MAX;
      }
      Up();
      break;
    case UP_MAX:
      if (mode == MODE_STOP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = UP_DECEL;
      } else {
        ;
      }
      Up();
      break;
    case UP_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_UP) {
        gMotorStatus = UP_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Up();
      break;
    case LEFT_ACCEL://
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = LEFT_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = LEFT_MAX;
      }
      Left();
      break;
    case LEFT_MAX:
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = LEFT_DECEL;
      } else {
        ;
      }
      Left();
      break;
    case LEFT_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_LEFT) {
        gMotorStatus = LEFT_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Left();
      break;
    case DOWN_ACCEL://
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = DOWN_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = DOWN_MAX;
      }
      Down();
      break;
    case DOWN_MAX:
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = DOWN_DECEL;
      } else {
        ;
      }
      Down();
      break;
    case DOWN_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_DOWN) {
        gMotorStatus = DOWN_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Down();
      break;
    case RIGHT_ACCEL://
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = RIGHT_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = RIGHT_MAX;
      }
      Right();
      break;
    case RIGHT_MAX:
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = RIGHT_DECEL;
      } else {
        ;
      }
      Right();
      break;
    case RIGHT_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_RIGHT) {
        gMotorStatus = RIGHT_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Right();
      break;
    case UP_LEFT_ACCEL:
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = UP_LEFT_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = UP_LEFT_MAX;
      }
      Up_Left();
      break;
    case UP_LEFT_MAX:
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = UP_LEFT_DECEL;
      } else {
        ;
      }
      Up();
      break;
    case UP_LEFT_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_UP_LEFT) {
        gMotorStatus = UP_LEFT_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Up_Left();
      break;
    case DOWN_LEFT_ACCEL://
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = DOWN_LEFT_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = DOWN_LEFT_MAX;
      }
      Down_Left();
      break;
    case DOWN_LEFT_MAX:
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_UP_RIGHT || mode == MODE_UP_LEFT || mode == MODE_UP_RIGHT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = DOWN_LEFT_DECEL;
      } else {
        ;
      }
      Down_Left();
      break;
    case DOWN_LEFT_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_DOWN_LEFT) {
        gMotorStatus = DOWN_LEFT_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Down_Left();
      break;
    case UP_RIGHT_ACCEL://
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = UP_RIGHT_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = UP_RIGHT_MAX;
      }
      Up_Right();
      break;
    case UP_RIGHT_MAX:
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_DOWN_RIGHT) {
        gMotorStatus = UP_RIGHT_DECEL;
      } else {
        ;
      }
      Up_Right();
      break;
    case UP_RIGHT_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_UP_RIGHT) {
        gMotorStatus = UP_RIGHT_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Up_Right();
      break;
    case DOWN_RIGHT_ACCEL://
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT) {
        gMotorStatus = DOWN_RIGHT_DECEL;
      } else {
        ;
      }
      if (pwm >= 255) {
        pwm = 255;
        gMotorStatus = DOWN_RIGHT_MAX;
      }
      Down_Right();
      break;
    case DOWN_RIGHT_MAX:
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT || mode == MODE_UP_LEFT || mode == MODE_DOWN_LEFT || mode == MODE_UP_RIGHT) {
        gMotorStatus = DOWN_RIGHT_DECEL;
      } else {
        ;
      }
      Down_Right();
      break;
    case DOWN_RIGHT_DECEL:
      pwm = pwm - dpwm_decel;
      if (mode == MODE_DOWN_RIGHT) {
        gMotorStatus = DOWN_RIGHT_ACCEL;
      } else {
        ;
      }
      if (pwm <= 0) {
        pwm = 0;
        gMotorStatus = INIT;
      }
      Down_Right();
      break;
    case NONE:
      break;
    default:
      break;
  }
}

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

  Timer1.initialize(callbackCycle);
  Timer1.attachInterrupt(callback);
  
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, 0);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
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
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
}
