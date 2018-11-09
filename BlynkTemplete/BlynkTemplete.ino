#include <BlynkSimpleStream.h>
 
char auth[] = "843c83d505ac455ba18fb5f31d71cb87";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  Blynk.syncAll();
}
 
void loop()
{
  Blynk.run() ;
}
