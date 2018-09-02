int sensors[2];
int inByte;

void setup(){
  Serial.begin(9600);
  sensors[0] = 0;
  sensors[1] = 0;
  inByte = 0;
  establishContact();
}

void loop(){
  if (Serial.available() > 0) {
    inByte = Serial.read();
    sensors[0] = analogRead(A0);
    sensors[1] = analogRead(A1);
    Serial.print(sensors[0]);
    Serial.print(",");
    Serial.println(sensors[1]);          
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0"); 
    delay(300);
  }
}
