const int sensor_pin = 0;
const int led_pin = 9;

const int INIT = 0;
const int bright = 1;
const int dark = 2;

const unsigned long update_interval = 3000;
const unsigned long timeout_duration = 10000;

int threshold = 0;
int hysteresis = 0;

int last_state = INIT;
int count = 0;
long total = 0;
unsigned long last_calibration = 0;
unsigned long last_falling_edge = 0;

void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int state = last_state;

  int sensor_value = analogRead(sensor_pin);

  unsigned long now = millis();

  total += sensor_value;
  count++;

  if (sensor_value > (threshold + hysteresis)) {
    state = bright;
  } else if (sensor_value < (threshold - hysteresis)) {
    state = dark;
  }

  if ((last_state != bright) && (state == bright)) {
    on_brighten_up();

    total = sensor_value;
    count = 1;
    last_calibration = now;
  } else if ((last_state != dark) && (state == dark)) {
    last_falling_edge = now;
    on_darken_up();
  }

  if ((state == bright) && ((now - last_calibration) > update_interval)) {
    calibration();
    total = sensor_value;
    count = 1;
    last_calibration = now;
  }
  
  if ((state == dark) &&((now - last_falling_edge) > timeout_duration)) {
    timeout();
  }

  last_state = state;
  delay(100);
}

void calibration() {
  if (count < 1) {
    return;
  }

  int average = total / count;
  Serial.print("average = ");
  Serial.println(average);

  threshold = int((float)average * 0.9);
  if (threshold > 511) {
    hysteresis = (1023 - threshold) / 10;
  } else {
    hysteresis = threshold / 10;
  }

  Serial.print("threshold = ");
  Serial.println(threshold);
  Serial.print("hysteresis = ");
  Serial.println(hysteresis);
}

void timeout() {
  threshold = 0;
  hysteresis = 0;
  Serial.println("timeout!");
}

void on_brighten_up() {
  digitalWrite(led_pin, LOW);
  Serial.println("brighten up");
}

void on_darken_up() {
  digitalWrite(led_pin, HIGH);
  Serial.println("darken up");
}

