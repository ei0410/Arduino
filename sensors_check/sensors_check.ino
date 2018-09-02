const int sensor_numbers = 8;
int sensors[sensor_numbers];

#define DEBUG

void setup() {
  #ifdef  DEBUG
  Serial.begin(9600);
  #endif
}

void loop() {
  for (int i = 0; i < sensor_numbers; i++) {
    sensors[i] = analogRead(i);
    #ifdef DEBUG
    Serial.print(sensors[i]);
    Serial.print("\t");
    #endif
  }
  Serial.println("");
}
