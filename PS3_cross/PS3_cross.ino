#include <TimerOne.h>
#include <Servo.h>
#include <PS3BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

Servo myservo;
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

bool printTemperature, printAngle;
float dt = 4000;

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
  NONE
} MotorStatus;

MotorStatus gMotorStatus = INIT;

#define MODE_STOP       0
#define MODE_UP         1
#define MODE_LEFT       2
#define MODE_DOWN       3
#define MODE_RIGHT      4

float pwm = 0;
float dpwm_accel = 1;
float dpwm_decel = 3;
int callbackCycle = 10000; //us

void callback() {
  
  int mode = 0;
  
//  switch(mode) {
//    case 0:
//      mode = MODE_STOP;
//      break;
//    case 0:
//      mode = MODE_STOP;
//      break;
//    case 0:
//      mode = MODE_STOP;
//      break;
//    case 0:
//      mode = MODE_STOP;
//      break;
//    case 0:
//      mode = MODE_STOP;
//      break;
//    default:
//      break;
//  }

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
      } else {
        ;
      }
      Stop();
      break;
    case UP_ACCEL:
      pwm = pwm + dpwm_accel;
      if (mode == MODE_STOP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT) {
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
      if (mode == MODE_STOP || mode == MODE_LEFT || mode == MODE_DOWN || mode == MODE_RIGHT) {
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
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_DOWN || mode == MODE_RIGHT) {
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
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_DOWN || mode == MODE_RIGHT) {
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
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_RIGHT) {
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
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_RIGHT) {
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
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN) {
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
      if (mode == MODE_STOP || mode == MODE_UP || mode == MODE_LEFT || mode == MODE_DOWN) {
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
    case NONE:
      break;
    default:
      break;
  }
}

void setup() {
  for (int i = 3; i <= 6; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  for (int i = 22; i <= 29; i++) {
    pinMode(i, OUTPUT);
  }

  myservo.attach(7);
  myservo.write(0);

  Timer1.initialize(dt);
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
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      if (PS3.PS3Connected) {
        Serial.print(F("\tRightHatX: "));
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.print(F("\tRightHatY: "));
        Serial.print(PS3.getAnalogHat(RightHatY));
      }
    }

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

      if (PS3.getButtonPress(L1)) {
        Serial.print(F("\r\nL1"));
      }
      if (PS3.getButtonPress(L3)) {
        Serial.print(F("\r\nL3"));
      }
      if (PS3.getButtonPress(R1)) {
        Serial.print(F("\r\nR1"));
      }
      if (PS3.getButtonPress(R3)) {
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

void Stop() {
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, 0);
  }
}

void Up() {
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
}

void Right() {
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
}

void Down() {
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
}

void Left() {
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  for (int i = 3; i <= 6; i++) {
    analogWrite(i, pwm);
  }
}
