#ifndef _kadai_robo_h
#define _kadai_robo_h

void set_output( int number, int *motorpin);

void set_input( int number, int *inputpin);

void motor( int pwm_val, int *motorpin);

void accel( int *pwm_val, int n);
void deccel( int *pwm_val, int n);

int *trace( int number, int *read_pin);

int K_direction( int x, int y);

#endif
