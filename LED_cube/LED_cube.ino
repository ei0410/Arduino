const int anode_pins[] = {34, 35, 36, 37, 38, 39, 40, 41, 42};
const int cathode_pins[] = {43, 44, 45,};
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
  helix();
}

void helix() {
  for (int j = 0; j < number_of_cathode_pins; j++) {
    for (int i = 0; i < number_of_anode_pins; i++) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(10);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
  }
}
