const int red   = 9;
const int green = 10;
const int blue  = 11;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  for (int i = 0; i < 2*PI; i += 0.01) {
    analogWrite(red,   sin((i+PI*0.0/3.0) * PI/180));
    analogWrite(green, sin((i+PI*2.0/3.0) * PI/180));
    analogWrite(blue,  sin((i+PI*4.0/3.0) * PI/180));
    delay(10);
  }
}
