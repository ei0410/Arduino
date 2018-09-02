double volt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  volt = ((double)analogRead(A0)/1023) * 5;
  Serial.print(volt);
  Serial.print(F("\n\r"));
}
