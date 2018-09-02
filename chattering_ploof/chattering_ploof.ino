const int buttonpin = 8;
int lastbuttonstate = LOW;

long lastdebouncetime = 0;
long debouncedelay = 50;

int count = 0;

void setup() {
  pinMode(buttonpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonstate = digitalRead(buttonpin);
  
  if (lastbuttonstate == LOW && buttonstate == HIGH) {
    int now = millis();

    if ((now - lastdebouncetime) > debouncedelay) {
      onpress();
    }

    lastdebouncetime = now;
  }

  lastbuttonstate = buttonstate;
}

void onpress() {
  count = count + 1;
  Serial.print(count);
  Serial.print("\n");
}
