//Matrix_LED
//cathode_common
int anodepin[8]   = {10,11,12,14,15,16,17,18};
int cathodepin[8] = {2,3,4,5,6,7,8,9};

void setup() {
  for(int ano = 0; ano < 8; ano++) {
    pinMode(anodepin[ano],OUTPUT);
    digitalWrite(anodepin[ano],LOW);
  }

  for (int cat = 0; cat < 8; cat++) {
    pinMode(cathodepin[cat],OUTPUT);
    digitalWrite(cathodepin[cat],HIGH);
  }
}

void loop() {
  for (int cat = 0; cat < 8; cat++) {
    digitalWrite(cathodepin[cat],LOW);
    for (int ano = 0; ano < 8; ano++) {
      digitalWrite(anodepin[ano],HIGH);
      delay(100);
      digitalWrite(anodepin[ano],LOW);
    }
    digitalWrite(cathodepin[cat],HIGH);
  }
}

