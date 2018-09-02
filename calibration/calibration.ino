const int sensor_pin = 0;
const int led_pin = 9;

const int INIT = 0;
const int bright = 1;
const int dark = 2;

int threshold = 0;
int hysteresis = 0;
int last_state = INIT;

void setup() {
  pinMode(led_pin, OUTPUT);

  Serial.begin(9600);

  measure_base_line();
}

void loop() {
  int state = last_state;

  int sensor_value = analogRead(sensor_pin);

  if (sensor_value > (threshold + hysteresis)) {
    state = bright;
  } else if (sensor_value < (threshold - hysteresis)) {
    state = dark;
  }

  if ((last_state != bright) && (state == bright)) {
    on_brighten_up();
  } else if ((last_state != dark) && (state == dark)) {
    on_darken_up();
  }

  last_state = state;
  delay(100);
}

void measure_base_line() {
  //average
  long total = 0;
  int count = 0;

  Serial.println("calibrating...");

  while (millis() < 5000) {
    int sensor_value = analogRead(sensor_pin);
    total += sensor_value;
    count++;
    delay(1);
  }
  Serial.println("done!");
  Serial.println();

  int average = total / count;
  Serial.print("total = ");
  Serial.println(total);
  Serial.print("count = ");
  Serial.println(count);
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

  /*max and min
  int maximum = 0;
  int minimum = 1023;

  while(millis() < 5000) {
    int sensor_value = analogRead(sensor_pin);
    maximum = max(maximum, sensor_value);
    minimum = min(minimum, sensor_value);
    delay(1);
  }

  threshold = (maximum - minimum) / 2 + minimum;
  hysteresis = (maximum - threshold) / 10;
  
  */
}

void on_brighten_up() {
  digitalWrite(led_pin, LOW);
  Serial.println("brighten up");
}

void on_darken_up() {
  digitalWrite(led_pin, HIGH);
  Serial.println("darken up");
}

