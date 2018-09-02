const int numpatterns = 8;

const int fingeringtable[numpatterns] = {
  B1111,
  B1101,
  B0111,
  B0101,
  B1100,
  B0100,
  B0010,
  B0000
};

const int notfound = -1;

const int frequency[numpatterns] = {
  262,
  294,
  330,
  349,
  392,
  440,
  494,
  523
};

const int button0 = 2;
const int button1 = 3;
const int button2 = 4;
const int button3 = 5;

const int speakerpin = 8;

const int sensor = 0;

const int thresholdH = 200;
const int thresholdL = 100;

int lastindex = notfound;

boolean waspressed = false;

void setup() {
  
}

void loop() {
  int value = analogRead(sensor);

  boolean ispressed = waspressed;
  if (value > thresholdH) {
    ispressed = true;
  } else if (value < thresholdL) {
    ispressed = false;
  }

  int buttonstate;
  buttonstate = digitalRead(button0);
  buttonstate += digitalRead(button1) << 1;
  buttonstate += digitalRead(button2) << 2;
  buttonstate += digitalRead(button3) << 3;

  int index = findpattern(buttonstate);

  if (!waspressed && ispressed) {
    if (index != notfound) {
      tone(speakerpin, frequency[index]);
    }
  } else if (waspressed && !ispressed) {
    noTone(speakerpin);
  } else if (waspressed && ispressed) {
    if (lastindex != index) {
      noTone(speakerpin);
      if(index != notfound) {
        tone(speakerpin, frequency[index]);
      }
    }
  }
  waspressed = ispressed;
  lastindex = index;
}

int findpattern(const int buttonstate) {
  for (int i = 0; i < numpatterns; i++) {
    if (fingeringtable[i] == buttonstate) {
      return i;
    }
  }
  return notfound;
}

