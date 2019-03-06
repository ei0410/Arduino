const int pin = 9;

void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(pin));
  delay(100);
}
