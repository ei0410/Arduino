const int anode_pins[] = {32, 33, 34, 35, 36, 37, 38, 39};
const int cathode_pins[] = {40, 41, 42, 43, 44, 45, 46, 47};
const int number_of_anode_pins = sizeof(anode_pins) / sizeof(anode_pins[0]);
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < number_of_anode_pins; i++) {
    pinMode(anode_pins[i], OUTPUT);
  }

  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);
    digitalWrite(cathode_pins[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int anode_pin = anode_pins[random(number_of_anode_pins)];
  int cathode_pin = cathode_pins[random(number_of_cathode_pins)];

  digitalWrite(cathode_pin, LOW);
  digitalWrite(anode_pin, HIGH);
  delay(5);
  digitalWrite(cathode_pin, HIGH);
  digitalWrite(anode_pin, LOW);
}
