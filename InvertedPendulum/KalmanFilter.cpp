#include "KalmanFilter.h"

KalmanFilter::KalmanFilter() {
  angle = 0.0;
  bias = 0.0;
  P[0][0] = 0.0;
  P[0][1] = 0.0;
  P[1][0] = 0.0;
  P[1][1] = 0.0;
};

void KalmanFilter::setAngle(float newAngle) {
  angle = newAngle;
};

float KalmanFilter::calcAngle(float newAngle, float newRate, float dt) {
  float Q_angle = 0.001;
  float Q_bias = 0.003;
  float R_measure = 0.03;

  float rate = newRate - bias;
  angle += dt * rate;

  P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt * P[1][1];
  P[1][0] -= dt * P[1][1];
  P[1][1] += Q_bias * dt;

  float y = newAngle - angle;

  float S = P[0][0] + R_measure;

  float K[2];
  K[0] = P[0][0] / S;
  K[1] = P[1][0] / S;

  angle += K[0] * y;
  bias  += K[1] * y;

  float P00_temp = P[0][0];
  float P01_temp = P[0][1];

  P[0][0] -= K[0] * P00_temp;
  P[0][1] -= K[0] * P01_temp;
  P[1][0] -= K[1] * P00_temp;
  P[1][1] -= K[1] * P01_temp;

  return angle;
};

