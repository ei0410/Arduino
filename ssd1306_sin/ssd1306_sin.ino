#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

float i = 0.0;
int out = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  if (i >= 2.0*PI) {
    i = 0.0;
  } else {
    i += 0.01;
  }
  display.clearDisplay();

  for (int j = 0; j < display.width(); j++) {
    display.drawPixel(j, int(display.height()/2-1 + (display.height()/2-1)*sin(j*(2.0*PI)/display.width())), WHITE);
  }

  display.display();
  //delay(10);
}
