#define DEBUG

const int sensor_numbers_x = 3;
int sensors_x[sensor_numbers_x];

const int sensor_numbers_y = 3;
int sensors_y[sensor_numbers_y];

int pwm = 0;

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < sensor_numbers_x; i++) {
    sensors_x[i] = analogRead(i);
    #ifdef DEBUG
    Serial.print(sensors_x[i]);
    Serial.print("\t");
    #endif
  }

  for (int i = 0; i < sensor_numbers_y; i++) {
    sensors_y[i] = analogRead(i + sensor_numbers_x);
    #ifdef DEBUG
    Serial.print(sensors_y[i]);
    Serial.print("\t");
    #endif
  }
  
  #ifdef DEBUG
  Serial.println("");
  #endif
}

void Up() {
  analogWrite(2, pwm);
  analogWrite(3, 0);
  analogWrite(4, pwm);
  analogWrite(5, 0);
  analogWrite(6, pwm);
  analogWrite(7, 0);
  analogWrite(8, pwm);
  analogWrite(9, 0);
}

//void Left() {
//  analogWrite(2, pwm);
//  analogWrite(3, 0);
//  analogWrite(4, pwm);
//  analogWrite(5, 0);
//  analogWrite(6, pwm);
//  analogWrite(7, 0);
//  analogWrite(8, pwm);
//  analogWrite(9, 0);
//}

void Stop() {
  for (int i = 2; i <= 9; i++) {
    analogWrite(i, 0);
  }
}

