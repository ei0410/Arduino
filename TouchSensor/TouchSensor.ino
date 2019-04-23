#define LEDPIN1 4
#define LEDPIN2 5

#define THRESHOLD 30

void setup() {
  Serial.begin(115200);
  
  pinMode(LEDPIN1, OUTPUT);
  pinMode(LEDPIN2, OUTPUT);
}

void loop() {
  const int iTch2 = touchRead(T2);
  const int iTch3 = touchRead(T3);
  
  Serial.printf("Touch 2=%d 3=%d\n", iTch2, iTch3);
  
  digitalWrite(LEDPIN1, iTch2 < THRESHOLD ? HIGH : LOW);
  digitalWrite(LEDPIN2, iTch3 < THRESHOLD ? HIGH : LOW);
  
  delay(100);
}
