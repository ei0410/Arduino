#define target 2.5
#define Kp 30
#define Ki 300
#define Kd 0.1
//Ku 103, Tu 0.24
//PI        0.45Ku = 46, 0.83Tu = 0.19, 0
//PID(TIME) 0.6Ku  = 78, 0.5Tu  = 0.12, 0.125Tu = 0.03
//PID(FREC) 0.5Ku  = 52, 0.5Tu  = 0.12, 0.16Tu  = 0.04

boolean LED = LOW;
float duty = 0;
float dt, preTime;
float vol;
float P, I, D, preP;

void PID() {
  dt = (micros() - preTime) / 1000000;
  preTime = micros();
  P = target - vol;
  I += P * dt;
  D = (P - preP) / dt;
  preP = P;

  duty += Kp * P + Ki * I + Kd * D;
}

void serialMonitor() {
//  Serial.print(dt); Serial.print(",");
//  Serial.print(duty, 3); Serial.print(",");
//  Serial.print(P, 3); Serial.print(",");
//  Serial.print(I, 3); Serial.print(",");
//  Serial.print(D, 3); Serial.print(",");
  Serial.print(target); Serial.print(",");
  Serial.println(vol);
}

void setup() {
  pinMode(13, OUTPUT);
  
  Serial.begin(115200);
  while(!Serial) {
    digitalWrite(13, LED);
    delay(200);
    LED = 1 - LED;
  }
  digitalWrite(13, LED);
  preTime = micros();
}

void loop() {
  analogWrite(3, duty);
  for (int i = 0; i < 1000; i++) {
    vol += analogRead(0);
  }
  vol = 5.0 * (vol / 1000) / 1023;

  PID();

  serialMonitor();
}
