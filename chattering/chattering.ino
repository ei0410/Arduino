const int button = 2;
int state = 0;
int old_state = 0;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(button);
  Serial.print(count);
  Serial.print(F("\r\n"));
  if ((state == HIGH) && (old_state == LOW)) {
    count++;
  }
  old_state = state;
}
