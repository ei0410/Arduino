#define Lpin 5
#define Rpin 6
#define pwm 9
#define cw 10
#define ccw 11

int Speed = 0;
boolean state = 0;

void setup() {
  pinMode(pwm, OUTPUT);
  pinMode(Rpin, OUTPUT);
  pinMode(Lpin, OUTPUT);
  pinMode(cw, INPUT);
  pinMode(ccw, INPUT);
}

void loop() {
  if (digitalRead(cw) == HIGH && digitalRead(ccw) == LOW) {
    state = 1;
    Speed = 40;
    while(digitalRead(cw)) {
      if (Speed > 255) {
        Speed = 255;
      }
      digitalWrite(Lpin, HIGH);
      digitalWrite(Rpin, LOW);
      analogWrite(pwm, Speed);
      Speed = Speed + 1;
      delay(30);
    }
  } else if (digitalRead(cw) == LOW && digitalRead(ccw) == HIGH) {
    state = 0;
    Speed = 40;
    while(digitalRead(ccw)) {
      if (Speed > 255) {
        Speed = 255;
      }
      digitalWrite(Lpin, LOW);
      digitalWrite(Rpin, HIGH);
      analogWrite(pwm, Speed);
      Speed = Speed + 1;
      delay(30);
    }
  } else {
    if (state == 1) {
      if (Speed < 0) {
        Speed = 0;
      }
      digitalWrite(Lpin, HIGH);
      digitalWrite(Rpin, LOW);
      analogWrite(pwm, Speed);
      Speed = Speed - 1;
      delay(3);
    } else {
    if (Speed < 0) {
        Speed = 0;
      }
      digitalWrite(Lpin, LOW);
      digitalWrite(Rpin, HIGH);
      analogWrite(pwm, Speed);
      Speed = Speed - 1;
      delay(3);
    }
  }
}
