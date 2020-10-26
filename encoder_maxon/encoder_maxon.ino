#define ENC_A 2
#define ENC_B 3

volatile int oldEncB;
volatile long encValue;

void doEncoderCounter(void) {
  int newEncB = PING & _BV(5);  // int newEncB = digitalRead(ENC_B);
  int newEncA = PINE & _BV(4);  // int newEncA = digitalRead(ENC_A);

  if (newEncA){
    if (oldEncB && !newEncB) { // up
      ++encValue;
    } else { // down
      --encValue;
    }
  } else {
    if (oldEncB && !newEncB) { // down
      --encValue;
    } else { // up
      ++encValue;
    }
  }
  oldEncB = newEncB;
}
 
void setup() {
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  encValue = 0;
  oldEncB = digitalRead(ENC_B);;
  attachInterrupt(0, doEncoderCounter, CHANGE);
  Serial.begin(115200);
}
 
void loop() {
  Serial.println(encValue,DEC);
  delayMicroseconds(10);
  //delay(1000);
}
