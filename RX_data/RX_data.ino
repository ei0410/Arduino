int recv_data;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() >= sizeof('H') + sizeof(int)) {
    if (Serial.read() == 'H') {
//      int low =  Serial.read();
//      int high = Serial.read();
      recv_data = Serial.read();
    }
  }

  if (recv_data == 1) {
    digitalWrite(13, HIGH);
  }
  if (recv_data == 0) {
    digitalWrite(13, LOW);
  }
  Serial.println(recv_data);
}
