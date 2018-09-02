#define ON HIGH
#define OFF LOW

#define ECA 2 //D2
#define ECB 3 //D3

#define inputEc(x) digitalRead(x)

byte curDat;
byte befDat = 0;
byte rotDir = 0;
int Count = 0;

byte inputMatch;
byte matchCnt;

byte rotPat = 0;

void setup() {
  pinMode(ECA , INPUT);
  pinMode(ECB , INPUT);

  curDat = 0;
  if (inputEc(ECA)) {
    befDat |= 2;
  }
  if (inputEc(ECB)) {
    befDat |= 1;
  }

  Serial.begin(19200);
}

void loop() {
  byte dat;
  signed char val;

  curDat = 0;
  if (inputEc(ECA)) {
    curDat |= 2;
  }
  if (inputEc(ECB)) {
    curDat |= 1;
  }

  if (befDat == curDat) {
    if (!inputMatch) {
      matchCnt++;
      if(matchCnt >= 5) {
        inputMatch = true;
        val = checkEnc(curDat);
        if (val != 0) {
          Count += val;
          Serial.println(Count);
        }
      }
    }
  } else {
    befDat = curDat;
    matchCnt = 0;
    inputMatch = false;
  }
}

signed char checkEnc(byte dat) {
    byte pat , i , j;

    rotPat <<= 2;
    rotPat |= (dat &0x03);

    if (rotPat == 0x4B) {
      return 1;
    } else if (rotPat == 0x87) {
      return -1;
    } else {
      return 0;
    }
}
