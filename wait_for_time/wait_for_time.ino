//inputs with shifing a time match the pattern.
const unsigned long sampling_interval = 5;

const int xpin = 0;
const int ypin = 1;
const int zpin = 2;

const int button_pin = 2;
const byte sample_data_length = 25;

char sample_data[sample_data_length][3];

int sample_count = 0;

boolean is_capturing = false;
boolean was_button_pressed = false;

void begin_capture() {
  sample_count = 0;
  is_capturing = true;
}

void end_capture() {
  if(!is_capturing) {
    return;
  }

  is_capturing = false;

  Serial.print("data\n");
  for (int i = 0; i < sample_data_length; i++) {
    Serial.print(sample_data[i][0], DEC);
    Serial.print("\t");
    Serial.print(sample_data[i][1], DEC);
    Serial.print("\t");
    Serial.print(sample_data[i][2], DEC);
    Serial.print("\n");
  }
  Serial.print("\r\n");
}

void process_sample(int x, int y, int z) {
  const int samples_to_average = 4;

  static int count = 0;

  static int totalx, totaly, totalz = 0;

  totalx += x;
  totaly += y;
  totalz += z;

  count++;

  if (count == samples_to_average) {
    sample_data[sample_count][0] = quantize_accel_data(totalx / samples_to_average);
    sample_data[sample_count][1] = quantize_accel_data(totaly / samples_to_average);
    sample_data[sample_count][2] = quantize_accel_data(totalz / samples_to_average);

    sample_count++;

    totalx = totaly = totalz = 0;
    count = 0;
  }

  if (sample_count > (sample_data_length - 1)) {
    end_capture();
  }
}

byte quantize_accel_data(int acc_data) {
  const int plus2g = 919;
  const int plus1g = 715;
  const int zerog = 511;
  const int minus1g = 307;
  const int minus2g = 103;

  byte quantized = 0;

  if (plus2g < acc_data) {
    quantized = 16;
  } else if (plus1g < acc_data && acc_data <= plus2g) {
    quantized = map(acc_data, plus1g + 1, plus2g, 11, 15);
  } else if (zerog < acc_data && acc_data <= plus1g) {
    quantized = map(acc_data, zerog + 1, plus1g, 1, 10);
  } else if (minus1g <= acc_data && acc_data < zerog) {
    quantized = map(acc_data, minus1g, zerog - 1, -10, -1);
  } else if (minus2g <= acc_data && acc_data < minus1g) {
    quantized = map(acc_data, minus2g + 1, minus1g, -15, -11);
  } else if (acc_data < minus2g) {
    quantized = -16;
  }

  return quantized;
}

void wait_for_action() {
  char initx = quantize_accel_data(analogRead(xpin));
  char inity = quantize_accel_data(analogRead(ypin));
  char initz = quantize_accel_data(analogRead(zpin));

  int count = 200;

  while ( --count > 0) {
    char x = quantize_accel_data(analogRead(xpin));
    char y = quantize_accel_data(analogRead(ypin));
    char z = quantize_accel_data(analogRead(zpin));

    unsigned int distance = 0;
    distance += abs(x - initx);
    distance += abs(y - inity);
    distance += abs(z - initz);

    if (distance > 5) {
      return;
    }

    delay(1);
  }
}

void setup() {
  Serial.print(9600);
}

void loop() {
  unsigned long start = millis();

  boolean is_button_pressed = (digitalRead(button_pin) == HIGH);

  if (!was_button_pressed && is_button_pressed) {
    wait_for_action();
    begin_capture();
  }

  if (is_capturing) {
    int x = analogRead(xpin);
    int y = analogRead(ypin);
    int z = analogRead(zpin);
    process_sample(x, y, z);
  }

  was_button_pressed = is_button_pressed;

  unsigned long elapsed_time = millis() - start;

  if (elapsed_time < sampling_interval) {
    delay(sampling_interval - elapsed_time);
  }
}
