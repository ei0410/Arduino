//Matrix_LED_dynamic
//cathode_common

int anodepin[8]   = {10,11,12,14,15,16,17,18};
int cathodepin[8] = {2,3,4,5,6,7,8,9};

void setup() {
  for (int ano = 0; ano < 8; ano++) {
    pinMode(anodepin[ano],OUTPUT);
    digitalWrite(anodepin[ano],LOW);
  }
  for (int cat = 0; cat < 8; cat++) {
    pinMode(cathodepin[cat],OUTPUT);
    digitalWrite(cathodepin[cat],HIGH);
  }
}

boolean matrix[8][8] =
{ 
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0}, 
  {0,1,0,0,0,0,1,0}, 
  {0,1,0,0,0,0,1,0}, 
  {0,1,0,0,0,0,1,0}, 
  {0,1,1,1,1,1,1,0}, 
  {0,1,0,0,0,0,1,0}, 
  {0,1,0,0,0,0,1,0}
};

void loop() {
  for (int cat = 0; cat < 8; cat++) {
    digitalWrite(cathodepin[cat],LOW);
    for (int ano = 0; ano < 8; ano++) {
      digitalWrite(anodepin[ano],matrix[cat][ano]);
    }
    delayMicroseconds(100);
    for (int ano = 0; ano < 8; ano++) {
      digitalWrite(anodepin[ano],LOW);
    }
    digitalWrite(cathodepin[cat],HIGH);
  }
}

