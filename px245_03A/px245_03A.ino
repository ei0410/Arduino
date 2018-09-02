#define delay_time 2

//int count = 0;

#include <FlexiTimer2.h>

void steps() {
  static boolean output = HIGH;
  static int pin = 2;
  digitalWrite(pin, output);
  output = !output;
  if (output == LOW) {
    pin++;
    if (pin >= 6) {
      pin = 2;
    }
  }
}

void setup() {
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
  }

  FlexiTimer2::set(10, steps);
  FlexiTimer2::start();
}

void loop() {
  //for (int i = 2; i <= 5; i++) {
    //digitalWrite(i, HIGH);
    //PORTD |= _BV(i);
    //delay(delay_time);
    //PORTD &= ~_BV(i);
    //digitalWrite(i, LOW);
    //count++;
//    while(count >= 200) {
//      ;
//    }
  //}
}
