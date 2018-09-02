#include <TimerOne.h>

long value = 0;

int a = 0;
int b = 0;
int prea = 0;
int preb = 0;

void callback() {
  a = digitalRead(2);
  b = digitalRead(3);

  if (prea == 0 && a == 1 && b == 0) {
    value++;
  } else if (preb == 0 && b == 1 && a == 0) {
    value--;
  } else {
    value = value;
  }

//  Serial.print(a);
//  Serial.print("\t");
//  Serial.println(b);
  prea = a;
  preb = b;
}

void setup() {
  pinMode(2, INPUT); 
  pinMode(3, INPUT);

  Timer1.initialize(150);
  Timer1.attachInterrupt(callback);
  
  Serial.begin(250000);
}

void loop() {
  Serial.println(value);
}
