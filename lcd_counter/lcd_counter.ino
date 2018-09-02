#include <LiquidCrystal.h>

LiquidCrystal g_lcd( 12, 11, 5, 4, 3, 2 );  // rs, enable, d4, d5, d6, d7
int g_iCounter = 0; // カウンター

void setup()
{
  g_lcd.begin( 16, 2 ); // 16文字×2行

  g_lcd.clear();  // LCD画面消去
  g_lcd.setCursor( 0, 0 );
  g_lcd.print( "Hello World!" );
}

void loop()
{
  g_lcd.setCursor( 0, 1 );
  g_lcd.print(g_iCounter);
  g_iCounter++;

  delay( 1000 );
}
