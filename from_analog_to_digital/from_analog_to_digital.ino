const int threshold = 511;
const int hysteresis = 102;
const int sensorpin = 0;
const int ledpin = 9;

boolean wasbright = true;

void setup() {
  pinMode(ledpin, OUTPUT);

  digitalWrite(ledpin, LOW);
  Serial.begin(9600);
}

void loop() {
  int brightness = analogRead(sensorpin);
  Serial.print(brightness);
  Serial.print("\n");
  boolean isbright = wasbright;
  

  if (brightness > (threshold + hysteresis)) {
    isbright = true;
  } else if (brightness < (threshold - hysteresis)) {
    isbright = false;
  } else {
    
  }

  if (!wasbright && isbright) {
    onbrightenup();
  } else if (wasbright && !isbright) {
    ondarkenup();
  }

  wasbright = isbright;

  delay(10);
}

void onbrightenup() {
  digitalWrite(ledpin, LOW);
}

void ondarkenup() {
  digitalWrite(ledpin, HIGH);
}

