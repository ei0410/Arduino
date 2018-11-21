#include <arduino.h>




void set_output( int number, int *motorpin){
  for( int i = 0; i < number; i++){
    pinMode( motorpin[i], OUTPUT);
    digitalWrite( motorpin[i], LOW);
  }
}


void set_input( int number, int *inputpin){
  for( int i = 0; i < number; i++){
    pinMode( inputpin[i], INPUT);
  }
}


void motor( int pwm_val,int *motorpin){
 //モーターを扱うための関数　これを使ってもよいし作り直してもよいです]

  int abs_pwm_val;
  abs_pwm_val = abs(pwm_val);
  if( pwm_val>0){
    analogWrite( motorpin[0], abs_pwm_val);
    digitalWrite( motorpin[1], LOW);
  }
  else if( pwm_val<0){
    digitalWrite( motorpin[0], LOW);
    analogWrite( motorpin[1], abs_pwm_val);
  }
  else{
    digitalWrite( motorpin[0], LOW);
    digitalWrite( motorpin[1], LOW);
  }
  Serial.print(F("["));
  Serial.print(pwm_val);
  Serial.print(F("]"));
}

void accel( int *pwm_val, int n){
  if(n == 0){
    if(pwm_val[0] > 0){
         pwm_val[0]--;
    }else if(pwm_val[0] < 0){
      pwm_val[0]++;
    }else{
      pwm_val[0] = 0;
    }
  }else if(n != 0){
    if(pwm_val[0] > 0){
      pwm_val[0] += n;
    }
    else if(pwm_val[0] < 0){
      pwm_val[0] += n;
    }
    else
    {
      pwm_val[0] = 0;
      pwm_val[0] += n;
    }
  }
  if( pwm_val[0] > 254){
    pwm_val[0] = 255;
  }
  else if( pwm_val[0] < -254){
    pwm_val[0] = -255;
  }
}


void deccel( int *pwm_val, int n){
  if(pwm_val[0] > 0){
    pwm_val[0] -= n;
  }
  else if(pwm_val[0] < 0){
    pwm_val[0] += n;
  }
  else
  {
    pwm_val[0] = 0;
  }
  
  if( pwm_val[0] > 254){
    pwm_val[0] = 255;
  }
  else if( pwm_val[0] < -254){
    pwm_val[0] = -255;
  }
}



int *trace( int number, int *read_pin){
//number:
//read_pin:
//代入先はポインタ指定（例　int *a; a = K_trace(
  int x[number];
  for ( int i = 0; i < number; i++) { //x[0]～x[NUMBER]
    x[i] = analogRead( read_pin[i]);
  }
  return x;
}

int K_direction( int x, int y) {//K_direction(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY))
  double deg, rad;
  int pattern = 0;
  x -= 128;
  y = abs(y - 256) - 128;
  rad = atan2((double)y, (double)x);
  deg = rad * 180.0 / (atan(1.0) * 4.0);
  if (abs(x) > 16 || abs(y) > 16)
  {
    pattern = 8;
    deg += 180.0;
    for ( int i = 0; i < 7; i++) {

      if ( deg >= 22.5 + (i * 45.0) && deg < 67.5 + (i * 45.0)) {
        pattern = i + 1;

      }
    }
    Serial.print( deg);
  }
  return pattern;
}
