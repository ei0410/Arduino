/*

ボタン配置
○;ラック回転右回り
×：ラック回転左回り
△：ラック引き離し
□：ラック押し付け
アナログパッド：足場の移動
R2:電磁弁ON
L2：電磁弁OFF

流れ
アナログパッドでラックまで移動
ラックの下に潜り込む
R2押してエアーを起動、ラックを持ち上げる
自動機まで移動
□を押して歯車をラック側の歯車に押し付ける
×ボタン押して自動機側の装填機構を回す
　　　　　　　　　～
△を押してラック押し付けを解除
L2を押してエアーを降ろす
アナログパッドでラックから離れる

ピン配置

足場
motor1:13,12
motor2:9,8
motor3:5,4
motor4:3,2

エアー
電磁弁:22

ラックに押し付ける歯車:24,25
ラックを回す歯車:26,27






*/
#include <kadai_robo.h>

//7番、8番は調子悪い？
//11番、12番のどっちかでanalogWrite使うとarduinoバグってしまった

//ps3コントローラーを扱うための準備　弄らなくてよい
#include <PS3USB.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <Servo.h>

USB Usb;

//BTD Btd(&Usb);
PS3USB PS3(&Usb);

boolean printTemperature;
boolean printAngle;

#define MOTOR_NUMBER 2
#define PWM_NUMBER 4
#define DENJIBEN_NUMBER 2
int motor_pin1[MOTOR_NUMBER] = { 30, 31};
int motor_pin2[MOTOR_NUMBER] = { 32, 33};
int motor_pin3[MOTOR_NUMBER] = { 34, 35};
int motor_pin4[MOTOR_NUMBER] = { 36, 37};
//int motor_pin5[MOTOR_NUMBER] = { 24,25};
//int motor_pin6[MOTOR_NUMBER] = { 26, 27};
int pwm[PWM_NUMBER]= { 0, 0, 0, 0};
//int denjiben_pin = 22;
//Servo my_servo;
//int servo_pin = 44;
//int angle[1] = {0};
//int denjiben_count[DENJIBEN_NUMBER]={ 0, 0};

void my_front();
void my_f_right();
void my_right();
void my_b_right();
void my_back();
void my_b_left();
void my_left();
void my_f_left();
void my_turn_left();
void my_turn_right();
void my_stop();
void all_motor();
void my_left_analog_pad(int n);
//void my_Servo(Servo my_servo, int* angle);
//void my_denjiben(int n, int denjiben_pin);

void setup() {//ここから
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  //ここまではいじらないで良い

  set_output(MOTOR_NUMBER,motor_pin1);
  set_output(MOTOR_NUMBER,motor_pin2);
  set_output(MOTOR_NUMBER,motor_pin3);
  set_output(MOTOR_NUMBER,motor_pin4);
  //set_output(MOTOR_NUMBER,motor_pin5);
  //set_output(MOTOR_NUMBER,motor_pin6);
  //my_servo.attach(servo_pin);
  //pinMode(denjiben_pin,OUTPUT);
  //digitalWrite(denjiben_pin,LOW);

}
void loop() {
  Usb.Task();
  if (PS3.PS3Connected) {
    if (PS3.getButtonClick(PS)){//各ボタンの中にモーターを動かしたりトランジスタを動かしたりサーボを動かす処理をかいてください
      Serial.print(F("\r\nPS"));
    }
    else{
    }
    if (PS3.getButtonPress(TRIANGLE)){
      //digitalWrite(motor_pin1[0],HIGH);
      //digitalWrite(motor_pin1[1],LOW);
      Serial.print(F("\r\nTraingle"));
    }
   else if (PS3.getButtonPress(CIRCLE)){
      //digitalWrite(motor_pin5[0],HIGH);
      //digitalWrite(motor_pin5[1],LOW);
      Serial.print(F("\r\nCircle"));
    }
   else if (PS3.getButtonPress(CROSS)){
      //digitalWrite(motor_pin5[0],LOW);
      //digitalWrite(motor_pin5[1],HIGH);
      Serial.print(F("\r\nCross"));
    }
    else if (PS3.getButtonPress(SQUARE)){
      //digitalWrite(motor_pin6[0], LOW);
      //digitalWrite(motor_pin6[1], HIGH);
      Serial.print(F("\r\nSquare"));
    }
    else if (PS3.getButtonPress(UP)) {
      Serial.print(F("\r\nUp"));
      //accel(angle,1);
      //my_Servo(my_servo,angle);
      //Serial.print(angle[0]);

    }
    else  if (PS3.getButtonPress(RIGHT)) {
      Serial.print(F("\r\nRight"));

    }
    else  if (PS3.getButtonPress(DOWN)) {
      Serial.print(F("\r\nDown"));
      //accel(angle,-1);
      //my_Servo(my_servo,angle);
      //Serial.print(angle[0]);
    }
    else  if (PS3.getButtonPress(LEFT)) {
      Serial.print(F("\r\nLeft"));

    }
    else if (PS3.getButtonPress(L1)){
      Serial.print(F("\r\nL1"));
      my_turn_left();
      all_motor();
    }else if (PS3.getButtonClick(L2)) {
      Serial.print(F("\r\nL2"));
      //digitalWrite(denjiben_pin,HIGH);
      /*my_denjiben(denjiben_count[0],denjiben_pin[0]);
      if(denjiben_count >= 1){
        denjiben_count[0] = 0;
      }else
      {
        denjiben_count[0] = 1;
      }*/
    }
    else if (PS3.getButtonPress(L3)){
      Serial.print(F("\r\nL3"));
    }
    else if (PS3.getButtonPress(R1)){
      Serial.print(F("\r\nR1"));
      my_turn_right();
      all_motor();
    }
    else if (PS3.getButtonPress(R2)){
      Serial.print(F("\r\nR2"));
    }      
    else if (PS3.getButtonPress(R3)){
      Serial.print(F("\r\nR3"));
    }
    else if (PS3.getButtonPress(SELECT)) {
      Serial.print(F("\r\nSelect"));
    }
    else if (PS3.getButtonPress(START)) {
      Serial.print(F("\r\nStart"));
    }
    else{
    my_left_analog_pad(K_direction(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)));
    Serial.print(F("\r"));
    }
//    digitalWrite(motor_pin5[0],LOW);
//    digitalWrite(motor_pin5[1],LOW);
//    digitalWrite(motor_pin6[0],LOW);
//    digitalWrite(motor_pin6[1],LOW);
  }
}

void my_front(){
  accel(&pwm[0],1);
  accel(&pwm[1],1);
  accel(&pwm[2],1);
  accel(&pwm[3],1);
}

void my_f_right(){  
  accel(&pwm[0],1);
  accel(&pwm[1],0);
  accel(&pwm[2],1);
  accel(&pwm[3],0);
}

void my_right(){
  accel(&pwm[0],1);
  accel(&pwm[1],-1);
  accel(&pwm[2],1);
  accel(&pwm[3],-1);
}

void my_b_right(){
  accel(&pwm[0],0);
  accel(&pwm[1],-1);
  accel(&pwm[2],0);
  accel(&pwm[3],-1);
}

void my_back(){
  accel(&pwm[0],-1);
  accel(&pwm[1],-1);
  accel(&pwm[2],-1);
  accel(&pwm[3],-1);
}

void my_b_left(){
  accel(&pwm[0],-1);
  accel(&pwm[1],0);
  accel(&pwm[2],-1);
  accel(&pwm[3],0);
}

void my_left(){
  accel(&pwm[0],-1);
  accel(&pwm[1],1);
  accel(&pwm[2],-1);
  accel(&pwm[3],1);
}


void my_f_left(){
  accel(&pwm[0],0);
  accel(&pwm[1],1);
  accel(&pwm[2],0);
  accel(&pwm[3],1);
}

void my_stop(){
  accel(&pwm[0],0);
  accel(&pwm[1],0);
  accel(&pwm[2],0);
  accel(&pwm[3],0);
}

void my_turn_right(){
  accel(&pwm[0],1);
  accel(&pwm[1],-1);
  accel(&pwm[2],-1);
  accel(&pwm[3],1);
}

void my_turn_left(){
  accel(&pwm[0],-1);
  accel(&pwm[1],1);
  accel(&pwm[2],1);
  accel(&pwm[3],-1);
}

void all_motor(){
  motor(pwm[0],motor_pin1);
  motor(pwm[1],motor_pin2);
  motor(pwm[2],motor_pin3);
  motor(pwm[3],motor_pin4);
}



//void my_Servo(Servo my_servo, int* angle){
//  if(angle[0] >= 180){
//    angle[0] = 180;
//  }else if(angle[0] <= 0){
//    angle[0] = 0;
//  }
//  my_servo.write(angle[0]);
//}

void my_left_analog_pad(int n){
  switch(n){
    case 6:
          my_front();    
          Serial.print(F("\r\nfront"));
          break;
    case 5:
          my_f_right();
          Serial.print(F("\r\nfront_right"));
          break;
    case 4:
          my_right();
          Serial.print(F("\r\nright"));
          break;
    case 3:
          my_b_right();
          Serial.print(F("\r\nback_right"));
          break;
    case 2:
          my_back();
          Serial.print(F("\r\nback"));
          break;
    case 1:
          my_b_left();
          Serial.print(F("\r\nback_left"));
          break;
    case 8:
          my_left();
          Serial.print(F("\r\nleft"));
          break;
    case 7:
          my_f_left();
          Serial.print(F("\r\nfront_left"));
          break;
    case 0:
          my_stop();
          Serial.print(F("\r\nstop"));
          break;
    default:
          my_stop();
          Serial.print(F("\r\nstop1"));
          break;
  }
  all_motor();
}

//void encoder(int number,int *read_pin){
//  int enc_n[number];
//  *enc_n = trace(number,read_pin);
//  for(int i = 0; i < number; i++){
//    Serial.print(F("エンコーダー"));
//    Serial.print(enc_n[i]);
//  }
//}

//void my_denjiben(int n, int denjiben_pin){
//  if(n > 0){
//    digitalWrite(denjiben_pin,HIGH);
//  }
//  else if(n < 0){
//    digitalWrite(denjiben_pin,LOW);
//  }else{
//  digitalWrite(denjiben_pin,LOW);
//  }
//}


