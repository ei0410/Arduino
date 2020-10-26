#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  display.clearDisplay();

  display.drawLine(0, 0, 127, 31, WHITE);
  display.drawLine(127, 0, 0, 31, WHITE);

  display.display();
  delay(1000);
}
