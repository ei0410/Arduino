#include <PS3BT.h>
#include <usbhub.h>
#include <Servo.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#define SERVO_DEFAULT 90
#define SERVO_L_MAX   45
#define SERVO_R_MAX   135

Servo servo;
int servo_pos = SERVO_DEFAULT;

#define MOTOR_MIN 50

int l_pwm = 255;
int r_pwm = 255;

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

bool printTemperature, printAngle;

int direction(int x,int y){
  double deg,rad;
  int pattern = 0;
  
  x -= 128;
  y = abs(y - 256) - 128;
  
  rad = atan2((double)y,(double)x);
  deg = rad * 180.0 /(atan(1.0) * 4.0);
  
  if(abs(x) > 16 || abs(y) > 16){
    deg += 180.0;
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
  servo.write(SERVO_DEFAULT);
  
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

    switch(direction(PS3.getAnalogHat(RightHatX),PS3.getAnalogHat(RightHatY))){
      case 0:
        Serial.print(F("\r\nStop"));
        Stop();
        break;
      case 1:
      case 2:
      case 12:
        Serial.print(F("\r\nLeft"));
        l_pwm = map(PS3.getAnalogHat(RightHatX), 127, 0, MOTOR_MIN, 255);
        r_pwm = map(PS3.getAnalogHat(RightHatX), 127, 0, MOTOR_MIN, 255);
        Left(l_pwm, r_pwm);
        break;
      case 3:
      case 4:
      case 5:
        Serial.print(F("\r\nDown"));
        l_pwm = map(PS3.getAnalogHat(RightHatY), 127, 255, MOTOR_MIN, 255);
        r_pwm = map(PS3.getAnalogHat(RightHatY), 127, 255, MOTOR_MIN, 255);
        Down(l_pwm, r_pwm);
        break;
      case 6:
      case 7:
      case 8:
        Serial.print(F("\r\nRight"));
        l_pwm = map(PS3.getAnalogHat(RightHatX), 127, 255, MOTOR_MIN, 255);
        r_pwm = map(PS3.getAnalogHat(RightHatX), 127, 255, MOTOR_MIN, 255);
        Right(l_pwm, r_pwm);
        break;
      case 9:
      case 10:
      case 11:
        Serial.print(F("\r\nUp"));
        l_pwm = map(PS3.getAnalogHat(RightHatY), 127, 0, MOTOR_MIN, 255);
        r_pwm = map(PS3.getAnalogHat(RightHatY), 127, 0, MOTOR_MIN, 255);
        Up(l_pwm, r_pwm);
        break;
      default:
        Stop();
        break;
    }

    if (PS3.getAnalogHat(LeftHatX) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      servo_pos = map(PS3.getAnalogHat(LeftHatX), 127, 0, SERVO_DEFAULT, SERVO_L_MAX);
    } else if (PS3.getAnalogHat(LeftHatX) > 137) {
      Serial.print(F("\r\nLeftHatX: "));
      servo_pos = map(PS3.getAnalogHat(LeftHatX), 127, 255, SERVO_DEFAULT, SERVO_R_MAX);
    } else {
      servo_pos = SERVO_DEFAULT;
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

void Up(int l, int r) {
  analogWrite(2, 0);
  analogWrite(3, l);
  analogWrite(4, 0);
  analogWrite(5, r);
}

void Left(int l, int r) {
  analogWrite(2, l);
  analogWrite(3, 0);
  analogWrite(4, 0);
  analogWrite(5, r);
}

void Down(int l, int r) {
  analogWrite(2, l);
  analogWrite(3, 0);
  analogWrite(4, r);
  analogWrite(5, 0);
}

void Right(int l, int r) {
  analogWrite(2, 0);
  analogWrite(3, l);
  analogWrite(4, r);
  analogWrite(5, 0);
}
