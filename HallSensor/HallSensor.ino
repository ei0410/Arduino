#define LEDPIN 4

#define THRESHOLD 100

void setup() {
  Serial.begin(115200);
  
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  int iHalSns = hallRead();

  Serial.printf("iHalSns = %d\n", iHalSns);
  
  digitalWrite(LEDPIN, THRESHOLD  < iHalSns ? HIGH : LOW);
  
  delay(100);
}
