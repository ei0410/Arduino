#include "Arduino.h"
#include "analogHat.h"

analogHat::analogHat(int split) {
  split_num = split;
}

int analogHat::get_pattern(int x, int y) {
  pattern_x = x;
  pattern_y = y;
  pattern_x -= 128;
  pattern_y = abs(pattern_y - 256) - 128;
  radian = atan2((double)pattern_y, (double)pattern_x);
  deg = radian * 180.0 / (atan(1.0) * 4.0);

  angle = 360.0 / split_num;

  if (abs(pattern_x) > 16 || abs(pattern_y) > 16) {
    deg += 180.0;
    for (int i = 0; i < split_num; i++) {
      if (deg >= (i * angle) && deg < ((i+1) * angle)) {
        pattern = i + 1;
      } else {
        ;
      }
    }
  } else {
    pattern = 0;
  }
    
  return pattern;
}

int analogHat::get_radius(int x, int y) {
  radius_x = x;
  radius_y = y;
  radius_x -= 128;
  radius_y = abs(radius_y - 256) - 128;
  radius = pow(radius_x, 2) + pow(radius_y, 2);
  radius = sqrt(radius);
  if (radius > 0) {  
    return radius;
  } else {
    return 0;
  }
}
