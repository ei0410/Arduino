#include <Servo.h>
#include <TimerOne.h>

#define SERVO_DEFAULT 90
#define SERVO_MAX     135
#define SERVO_MIN     45

Servo myservo;
int pos = 0;

const int senser_numbers = 8;
int sensers[senser_numbers];

int thresholds[senser_numbers] = {350, 380, 400, 350, 390, 430, 330, 230};

const float kp = 0.0005;
float error;
float p;

int dt = 4000;

#define DEBUG

void func() {
  
}

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  myservo.attach(6);
  myservo.write(SERVO_DEFAULT);
  Timer1.initialize(dt);
  Timer1.attachInterrupt(func);
}

void loop() {
  for (int i = 0; i < senser_numbers; i++) {
    sensers[i] = analogRead(i);
    #ifdef DEBUG
    Serial.print(sensers[i]);
    Serial.print("\t");
    #endif
  }
  #ifdef DEBUG
  Serial.println("");
  #endif
  error = sensers[0] * (-4) * 1.4 + sensers[1] * (-3) + sensers[2] * (-2) + sensers[3] * (-1) + sensers[4] * 1 + sensers[5] * 2 + sensers[6] * 3 + sensers[7] * 4 * 1.4;
  p = kp * error;

  p = constrain(p, -5, 5);
  pos = map(p, -5, 5, SERVO_MIN, SERVO_MAX);

//  int count = 0;
//  for(int i = 0; i < senser_numbers; i++) {
//    if (sensers[i] < thresholds[i]) {
//      count += (1 << i);
//    }
//  }
//  Serial.println(count);
//
//  switch(count) {
//      case 24:
//      pos = SERVO_DEFAULT;
//      Up(255, 255);
//      break;
//    case 12:
//      pos += 3;
//      Up(255, 255);
//      break;
//    case  6:
//      pos +=  5;
//      Up(255, 255);
//      break;
//    case  3:
//      pos +=  7;
//      Up(255, 255);
//      break;
//    case 48:
//      pos -=  3;
//      Up(255, 255);
//      break;
//    case 96:
//      pos -=  5;
//      Up(255, 255);
//      break;
//    case 195:
//      pos -=  7;
//      Up(255, 255);
//      break; 
//    case 255:
//      Stop();
//      break;
//    default:
//      break;
//  }

  pos = int(constrain(pos, SERVO_MIN, SERVO_MAX));
    
  myservo.write(pos);
}

void Stop() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void Up(int l, int r) {
  analogWrite(2, l);
  analogWrite(3, 0);
  analogWrite(4, 0);
  analogWrite(5, r);
}
