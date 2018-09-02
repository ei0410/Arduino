const int senserpin = 0;
const int threshold = 80;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(senserpin);

  if (value > threshold) {
    int range = (6787 / (value - 3)) - 4;
    Serial.print(range);  
  } else {
    Serial.print("OFF");
  }
  
  Serial.print(F("\r\n"));
  delay(100);
}
