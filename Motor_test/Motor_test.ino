void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  delay(1000);
  analogWrite(5, 255);
  analogWrite(6, 0);
  delay(1000);
  analogWrite(5, 0);
  analogWrite(6, 0);
  delay(1000);
  analogWrite(5, 0);
  analogWrite(6, 255);
  delay(1000);
}
