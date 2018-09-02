const int pin1 = 9;
const int pin2 = 10;
const int pwm = 11;

const int leftsensor = 0;
const int rightsensor = 1;

const int threshold = 300;

const unsigned int timeout = 1000;

void forward(int value) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  analogWrite(pwm, value);
}

void reverse(int value) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  analogWrite(pwm, value);
}

void despin(boolean usbBreak = true) {
  if (usbBreak) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    analogWrite(pwm, 255);
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(pwm, 0);
  }
}

void left() {
  forward(50);

  unsigned int start = millis();

  while(analogRead(rightsensor) > threshold) {
    delay(1);

    if ((millis() - start) > timeout) {
      break;
    }
  }
  despin(true);
}

void right() {
  reverse(50);

  unsigned int start = millis();

  while(analogRead(leftsensor) > threshold) {
    delay(1);
    
    if ((millis() - start) > timeout) {
      break;
    }
  }

  despin(false);
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 9; i < 12; i++) {
    pinMode(i, OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("left");
  left();
  delay(1000);
  
  Serial.println("right");
  right();
  delay(1000);
}
