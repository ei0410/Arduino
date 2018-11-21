#include <Servo.h>

#define SERVO_DEFAULT 90
#define SERVO_MAX     135
#define SERVO_MIN     45

Servo myservo;
int pos = 0;

const int senser_numbers = 8;
int sensors[senser_numbers];

int thresholds[senser_numbers] = {300, 360, 390, 350, 390, 470, 290, 250};

#define DEBUG

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  myservo.attach(6);
  myservo.write(SERVO_DEFAULT);
  //Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < senser_numbers; i++) {
    sensors[i] = analogRead(i);
    #ifdef DEBUG
    Serial.print(sensors[i]);
    Serial.print("\t");
    #endif
  }
  #ifdef DEBUG
  Serial.println("");
  #endif

  int count = 0;
  for(int i = 0; i < senser_numbers; i++) {
    if (sensors[i] < thresholds[i]) {
      count += (1 << i);
    }
  }
  //Serial.println(count);

  switch(count) {
      case 24:
      pos = SERVO_DEFAULT;
      Up(255, 255);
      break;
    case 12:
      pos += 3;
      Up(255, 255);
      break;
    case  6:
      pos +=  5;
      Up(255, 255);
      break;
    case  3:
      pos +=  7;
      Up(255, 255);
      break;
    case 48:
      pos -=  3;
      Up(255, 255);
      break;
    case 96:
      pos -=  5;
      Up(255, 255);
      break;
    case 195:
      pos -=  7;
      Up(255, 255);
      break; 
    case 255:
      Stop();
      break;
    default:
      break;
//    case 24:
//      pos = SERVO_DEFAULT;
//      break;
//    case 12:
//      pos =  105;
//      break;
//    case  6:
//      pos =  115;
//      break;
//    case  3:
//      pos =  135;
//      break;
//    case 48:
//      pos =  75;
//      break;
//    case 96:
//      pos =  50;
//      break;
//    case 195:
//      pos =  45;
//      break;    
//     
//    default:
//      break;
  }

  if (pos > SERVO_MAX ) {
    pos = SERVO_MAX;
  }
  if (pos < SERVO_MIN ) {
    pos = SERVO_MIN;
  }
    
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
