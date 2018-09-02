#include <SNESpad.h>

SNESpad pad = SNESpad(2, 3, 4);

int input = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  input = pad.buttons();

  Serial.write('H');
  Serial.write(highByte(input));
  Serial.write(lowByte(input));
}
