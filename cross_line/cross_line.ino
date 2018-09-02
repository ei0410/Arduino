#define DEBUG

const int sensor_numbers_x = 3;
int sensor_x[sensor_numbers_x];

const int sensor_numbers_y = 3;
int sensor_y[sensor_numbers_y];

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

void loop() {
  for (int i = 0; i < sensor_numbers_x; i++) {
    sensor_x[i] = analogRead(i);
    #ifdef DEBUG
    Serial.print(sensor_x[i]);
    Serial.print("\t");
    #endif
  }

  for (int i = 0; i < sensor_numbers_y; i++) {
    sensor_y[i] = analogRead(i + sensor_numbers_x);
    #ifdef DEBUG
    Serial.print(sensor_y[i]);
    Serial.print("\t");
    #endif
  }
  
  #ifdef DEBUG
  Serial.println("");
  #endif
}
