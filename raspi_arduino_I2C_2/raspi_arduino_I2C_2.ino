#include <Wire.h>

int SLAVE_ADDRESS = 0x04;

int cmd = 0;
int val = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveAnalogReading);
  Wire.onRequest(sendData);
  Serial.begin(9600);
  Serial.println("Ready!");
}

void loop() {
  delay(10);
}

void receiveAnalogReading(int byteCount) {
  while(Wire.available()) {
    cmd = Wire.read();
    Serial.print("data received: ");
    Serial.println(cmd);

    switch(cmd) {
      case 0:
        val = analogRead(A0);
        break;
      case 1:
        val = analogRead(A1);
        break;
      case 2:
        val = analogRead(A2);
        break;
      case 3:
        val = analogRead(A3);
        break;
      case 4:
        val = analogRead(A4);
        break;
      case 5:
        val = analogRead(A5);
        break;
      default:
        break;
    }
  }
}

void sendData() {
  val = map(val, 0, 1024, 0, 256);
  Serial.print("send data: ");
  Serial.println(val);
  Wire.write(val);
}

