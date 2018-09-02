const int senserpin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(senserpin);

  int temperature = map(value, 0, 205, 0, 100);
  Serial.print(temperature);
  Serial.print(F("\r\n"));
  delay(1000);
}
