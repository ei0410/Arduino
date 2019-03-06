const int in  = 10;
const int out = 11;

bool state = false;
bool old_state = false;

void setup() {
  pinMode(in, INPUT);
  pinMode(out, OUTPUT);
}

void loop() {
  if (digitalRead(in) == HIGH && old_state == LOW) {
    state = !state;
  }

  if (state) {
    digitalWrite(out, HIGH);
  } else {
    digitalWrite(out, LOW);
  }

  old_state = state;
  delay(10);
}
