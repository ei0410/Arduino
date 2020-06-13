#define out 9

void setup() {
  pinMode(out, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(out, i);
    delay(10);
  }
  
  for (int i = 255; i >= 0; i--) {
    analogWrite(out, i);
    delay(10);
  }
}
