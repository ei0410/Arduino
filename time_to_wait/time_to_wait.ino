const int unknown = 0;
const int bright = 1;
const int dark = 2;

const int timetowait = 1000;//3000
const int thresholdH = 700;
const int thresholdL = 300;

const int sensorpin = 0;
const int ledpin = 9;

int state = unknown;
int nextstate = unknown;
unsigned long lastchange = 0;
int lastsensorstate = unknown;

void setup() {
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  int brightness = analogRead(sensorpin);
  int sensorstate = lastsensorstate;

  Serial.print(brightness);
  Serial.print("\n");
  if (brightness > thresholdH) {
    sensorstate = bright;
  } else if (brightness < thresholdL) {
    sensorstate = dark;
  }

  if (lastsensorstate != sensorstate) {
    if (sensorstate == bright) {
      nextstate = bright;
      lastchange = now;
    } else if (sensorstate == dark) {
      nextstate = dark;
      lastchange = now;
    }
  }

  lastsensorstate = sensorstate;

  if (state != nextstate &&((now - lastchange) > timetowait)) {
    if (nextstate == bright) {
      digitalWrite(ledpin, LOW);
    } else if (nextstate == dark) {
      digitalWrite(ledpin, HIGH);
    }

    state = nextstate;
  }

  delay(50);
}
