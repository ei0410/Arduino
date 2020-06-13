#define out 9
#define in  A0

void setup() {
  pinMode(out, OUTPUT);
  pinMode(in,  INPUT);
}

void loop() {
  int value = digitalRead(in);
  if (value == 1) {
    digitalWrite(out, HIGH);
  } else {
    digitalWrite(out, LOW);
  }
}
