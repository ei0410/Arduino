typedef enum {
  INIT,
  TRACE,
  TURN_R,
  TURN_L,
  CROSS_LINE,
  STOP,
  NONE
} Status;

Status gStatus = INIT;

//#define DEBUG

int threshold = 500;
//from 200 to 800
const int motorR = 5;
const int motorL = 6;

const int sensor_number = 5;
int sensor[sensor_number];
int trace = 0;
int pre_trace = 0;
int cross_count = 0;

void setup() {
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);

  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

void loop() {
  for (int i = 0; i < sensor_number; i++) {
    sensor[i] = analogRead(i);
    //constrain(sensor[i], 200, 800);
    #ifdef DEBUG
    Serial.print(sensor[i]);
    Serial.print("\t");
    #endif
  }

  if (sensor[0] < threshold){
    trace += 1;
  }
  if (sensor[1] < threshold){
    trace += 2;
  }
  if (sensor[2] < threshold){
    trace += 4;
  }
  if (sensor[3] < threshold){
    trace += 8;
  }
  if (sensor[4] < threshold) {
    trace += 16;
  }

  switch(gStatus) {
    case INIT:
      while(millis() < 2000) {
        ;
      }
      gStatus = TRACE;
      break;
    case TRACE:
      linetrace();
      break;
    case TURN_R:
      Motor(80, 0);
      if (trace == 12) {
        gStatus = TRACE;
      } else {
        ;
      }
      break;
    case TURN_L:
      Motor(0, 80);
      if (trace == 6) {
        gStatus = TRACE;
      } else {
        ;
      }
      break;
    case CROSS_LINE:
      cross_count = cross_count + 1;
      delay(1000);
      if (cross_count == 8) {
        gStatus = STOP;
      } else {
        gStatus = TRACE;
      }
      break;
    case STOP:
      Motor(0, 0);
      break;
  }

  #ifdef DEBUG
  Serial.print(cross_count);
  Serial.print("\t");
  Serial.print(trace);
  Serial.print("\t");
  Serial.println(gStatus);
  #endif

  pre_trace = trace;
  trace = 0;
}

void Motor(int motor_r, int motor_l) {
  analogWrite(motorR, motor_r);
  analogWrite(motorL, motor_l);
}

void linetrace () {
  switch (trace) {
    case 1:  //00001
      Motor(80, 0);
      break;
    case 3:  //00011
      Motor(100, 70);
      break;
    case 7:  //00111
      Motor(100, 80);
      break;
    case 6:  //00110
      Motor(100, 90);
      break;
    case 14: //01110
      Motor(100, 100);
      break;
    case 12: //01100
      Motor(90, 100);
      break;
    case 28: //11100
      Motor(80, 100);
      break;
    case 24: //11000
      Motor(70, 100);
      break;
    case 16: //10000
      Motor(0, 70);
      break;
    case 31://11111
      gStatus = CROSS_LINE;
      break;
    default:
      break;
    }
}
