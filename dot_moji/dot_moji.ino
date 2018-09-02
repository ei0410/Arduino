const int anode_pins[] = {32, 33, 34, 35, 36, 37, 38, 39};
const int cathode_pins[] = {40, 41, 42, 43, 44, 45, 46, 47};
const int number_of_anode_pins = sizeof(anode_pins) / sizeof(anode_pins[0]);
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);

boolean moji[8][8] = {
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 1, 0, 0, 0},
  {0, 1, 0, 1, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {0, 1, 0, 1, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0}
};

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
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (moji[j][i]) {
        digitalWrite(anode_pins[j], HIGH);
        digitalWrite(cathode_pins[i], LOW);
        digitalWrite(anode_pins[j], LOW);
        digitalWrite(cathode_pins[i], HIGH);
      }
    }
  }
}
