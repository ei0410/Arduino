#define delta 100

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
  helix();
}

void helix() {

  int i = 0;
  int j = 0;
  int a = 0;
  
  for (a = 0; a < 4; a++) {
    for (i ; i < number_of_anode_pins - a; i++) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delta);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i - 1;
    j = j + 1;
    for (j ; j < number_of_cathode_pins - a; j++) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delta);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i - 1;
    j = j - 1;
    for (i ; i > 0 - 1 + a; i--) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delta);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i + 1;
    j = j - 1;
    for (j ; j > 0 + a; j--) {
      digitalWrite(anode_pins[i], HIGH);
      digitalWrite(cathode_pins[j], LOW);
      delay(delta);
      digitalWrite(cathode_pins[j], HIGH);
      digitalWrite(anode_pins[i], LOW);
    }
    i = i + 1;
    j = j + 1;
  }
}
