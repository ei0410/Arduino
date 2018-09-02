#include <TimerOne.h>

int pin = 2;

void callback() {
  switch(pin) {
    case 2:
      PORTD |= _BV(2);
      PORTD &= ~(_BV(3) | _BV(4) | _BV(5));
      break;
    case 3:
      PORTD |= _BV(3);
      PORTD &= ~(_BV(2) | _BV(4) | _BV(5));
      break;
    case 4:
      PORTD |= _BV(4);
      PORTD &= ~(_BV(2) | _BV(3) | _BV(5));
      break;
    case 5:
      PORTD |= _BV(5);
      PORTD &= ~(_BV(2) | _BV(3) | _BV(4));
      break;
    default:
      break;
  }
  pin++;
  if (pin > 5) {
    pin = 2;
  }
}

void setup() {
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
  }
  Timer1.initialize(2000);
  Timer1.attachInterrupt(callback);
}

void loop() {
  
}
