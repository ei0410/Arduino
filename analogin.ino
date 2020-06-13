#define out 9
#define in  A0

void setup() {
  pinMode(out, OUTPUT);
  pinMode(in,  INPUT);
}

void loop() {
  int value = analogRead(in);
  if (value < 127) {
    digitalWrite(out, HIGH);
  } else {
    digitalWrite(out, LOW);
  }
}
