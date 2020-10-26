const float AREF   = 3.3;
const float SENS   = 0.660;
const int   OFFSET = 512;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int X, Y, Z;
  float x, y, z;

  X = analogRead(A0);
  Y = analogRead(A1);
  Z = analogRead(A2);
  
  x = (X-OFFSET);
  y = (Y-OFFSET);
  z = (Z-OFFSET);
  
  x = x / 1024.0 * AREF / SENS;
  y = y / 1024.0 * AREF / SENS;
  z = z / 1024.0 * AREF / SENS;
  
  Serial.print(X);
  Serial.print(" ");
  Serial.print(Y);
  Serial.print(" ");
  Serial.print(Z);
  Serial.print(" ");
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.println(z);
  
  delay(100);
}
