const int anode_pins[] = {34, 35, 36, 37, 38, 39, 40, 41};
const int cathode_pins[] = {42, 43, 44, 45};
const int number_of_anode_pins = sizeof(anode_pins) / sizeof(anode_pins[0]);
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);

const int digits[] = {
  0b00111111,//0
  0b00000110,//1
  0b01011011,//2
  0b01001111,//3
  0b01100110,//4
  0b01101101,//5
  0b01111101,//6
  0b00100111,//7
  0b01111111,//8
  0b01101111,//9
};

void display_number (int n) {
  for (int i = 0; i < number_of_anode_pins; i++) {
    digitalWrite(anode_pins[i], digits[n] & (1 << i) ? HIGH : LOW);
  }
}

void clear_segments() {
  for (int j = 0; j < number_of_anode_pins; j++) {
    digitalWrite(anode_pins[j], LOW);
  }
}

void display_numbers (int n) {
  for (int i = 0; i < number_of_cathode_pins; i++) {
    digitalWrite(cathode_pins[i], LOW);
    display_number(n % 10);
    delay(5);
    clear_segments();
    digitalWrite(cathode_pins[i], HIGH);
    n = n / 10;
  }
}

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
  for (int i = 0; i < 10000; i++) {
    display_numbers(i);
  }
}
