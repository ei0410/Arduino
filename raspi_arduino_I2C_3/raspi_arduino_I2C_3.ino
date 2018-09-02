#include <Wire.h>

int SLAVE_ADDRESS = 0x04;

int cmd = 1;
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
    if (cmd == 0) {
      val = analogRead(A0);
    }
  }
}

void sendData() {
  val = map(val, 0, 1024, 0, 256);
  Serial.print("send data: ");
  Serial.println(val);
  Wire.write(val);
}

