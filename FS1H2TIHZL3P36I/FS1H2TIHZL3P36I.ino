//#include <MsTimer2.h>
//int i = 0;

byte countS = 0;

//long zeroOmegaI = 0;

int recOmegaI[10];
int omegaI = 0;

long thetaI = 0;
long sumPower = 0;
long sumSumP = 0;

const int kAngle = 50;
const int kOmega = 500;
const long kSpeed = 60;
const long kDistance = 20;

long powerScale;
int power;

long vE5 = 0;
long xE5 = 0;

#include <SPI.h>

int ry;
long R;
  
void L3GD20_write(byte reg, byte val) {
  digitalWrite(10, LOW);
  
  SPI.transfer(reg);
  SPI.transfer(val);
  
  digitalWrite(10, HIGH);
}
  
byte L3GD20_read(byte reg) {
  byte ret = 0;
  
  digitalWrite(10, LOW);
  
  SPI.transfer(reg | 0x80);
  ret = SPI.transfer(0);
  
  digitalWrite(10, HIGH);
  
  return ret;
}

void setup () {
  Serial .begin(115200);
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  for ( int i = 0 ; i < 10 ; i++ ) { 
    recOmegaI[i] = 0; 
  }
  
  pinMode(10, OUTPUT);
  
  digitalWrite(10, HIGH);
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  
  L3GD20_write(0x20, B11001111);
  L3GD20_write(0x23, B00000000);
  
  delay(300);

// training();
// MsTimer2::set(5, chkAndCtl);
// MsTimer2::start();
}

void loop () {
  
  chkAndCtl();
  
  if ( power > 0 ) {
//    analogWrite( 6, power );
//    digitalWrite( 4, HIGH );
//    digitalWrite( 5, LOW );
//    analogWrite( 9, power );
//    digitalWrite( 7, HIGH );
//    digitalWrite( 8, LOW );
    analogWrite(3, 0);
    analogWrite(5, power);
    analogWrite(6, power);
    analogWrite(9, 0);
  } else {
//    analogWrite( 6, - power );
//    digitalWrite( 4, LOW );
//    digitalWrite( 5, HIGH );
//    analogWrite( 9, - power );
//    digitalWrite( 7, LOW );
//    digitalWrite( 8, HIGH );
    analogWrite(3, 0);
    analogWrite(5, -power);
    analogWrite(6, -power);
    analogWrite(9, 0);
  }
  
// delayMicroseconds(3600);
}

//void training(){
// delay (1000);
// for ( i = 0 ; i < 500 ; i++ ){
// zeroOmegaI = zeroOmegaI + analogRead(A5);
// }
// zeroOmegaI = zeroOmegaI / i;
//}

void chkAndCtl() {
// omegaI = 0;
// for ( i = 0 ; i < 10 ; i++ ) {
// omegaI = omegaI + analogRead(A5) - zeroOmegaI;
// delayMicroseconds(10);
// }
// omegaI = omegaI / 10;

  R = 0;
  for ( int i = 0 ; i < 45 ; i++ ) {
    ry = ( (L3GD20_read(0x2B) << 8) | L3GD20_read(0x2A) );
    R = R + ry;
    delayMicroseconds(90);
  }
  
  omegaI = R * 0.00875 / 45;
  
// omegaI = analogRead(A5) - zeroOmegaI;

  if ( abs( omegaI ) < 2 ) { 
    omegaI = 0; 
  }
  
  recOmegaI[0] = omegaI;
  thetaI = thetaI + omegaI;
  countS = 0;
  
  for ( int i = 0 ; i < 10 ; i++ ) {
    if ( abs( recOmegaI[i] ) < 4 ) { 
      countS++; 
    }
  }
  
  if ( countS > 9 ) {
    thetaI = 0;
    
    vE5 = 0;
    xE5 = 0;
    
    sumPower = 0;
    sumSumP = 0;
  }

  for ( int i = 9 ; i > 0 ; i-- ) { 
    recOmegaI[ i ] = recOmegaI[ i-1 ]; 
  }
  
  powerScale = ( kAngle * thetaI / 100 ) + ( kOmega * omegaI / 100 ) + ( kSpeed * vE5 / 1000 ) + ( kDistance * xE5 / 1000 );
  power = max ( min ( 95 * powerScale / 100 , 255 ) , -255 );
  sumPower = sumPower + power;
  sumSumP = sumSumP + sumPower;
  
// vE5 = ???
// xE5 = ???
}

