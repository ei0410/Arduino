unsigned int a = 0;
unsigned int b = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sendIntData(a);
  delay(1000);

  sendIntData(b);
  delay(1000);
}

void sendIntData(int value) {
  Serial.write('H');
  Serial.write(value);
  //Serial.write(highByte(value));
}

