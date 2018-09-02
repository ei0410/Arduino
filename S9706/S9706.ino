const int doutpin = 2;
const int rangepin = 4;
const int ckpin = 5;
const int gatepin = 6;

void setup() {
  Serial.begin(9600);

  pinMode(doutpin, INPUT);
  pinMode(rangepin, OUTPUT);
  pinMode(ckpin, OUTPUT);
  pinMode(gatepin, OUTPUT);
}

void loop() {
  int red, green, blue;
  int integration = 50;
  char s[64];

  digitalWrite(gatepin, LOW);
  digitalWrite(ckpin, LOW);
  digitalWrite(rangepin, HIGH);

  digitalWrite(gatepin, HIGH);
  delay(integration);
  digitalWrite(gatepin, LOW);
  delayMicroseconds(4);
  red = shiftIn12(doutpin, ckpin);
  delayMicroseconds(3);
  green = shiftIn12(doutpin, ckpin) * 0.76;
  delayMicroseconds(3);
  blue = shiftIn12(doutpin, ckpin) * 0.88;

  sprintf(s, "red = %4d, green = %4d, blue = %4d", red, green , blue);
  Serial.println(s);

  delay(2000);
}

int shiftIn12(int datapin, int clockpin) {
  int value = 0;
  for (int i = 0; i < 12; i++) {
    digitalWrite(clockpin, HIGH);
    value |= digitalRead(datapin) << i;
    digitalWrite(clockpin, LOW);
  }
  return value;
}

