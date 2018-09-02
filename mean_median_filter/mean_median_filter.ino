const int buffer_length = 5;
const int index_of_middle = buffer_length/2;
int buffer[buffer_length];
int index = 0;

const int sensorpin = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(sensorpin);

  buffer[index] = raw;

  index = (index + 1) % buffer_length;

  int smoothedByMeanFilter = smoothByMeanFilter();
  int smoothedByMedianFilter = smoothByMedianFilter();

  Serial.print(raw);
  Serial.print("\t");
  Serial.print(smoothedByMeanFilter);
  Serial.print("\t");
  Serial.print(smoothedByMedianFilter);
  Serial.println();

  delay(100);
}

int smoothByMeanFilter() {
  long sum = 0;

  for (int i = 0; i < buffer_length; i++) {
    sum += buffer[i];
  }

  return (int)(sum / buffer_length);
}

int smoothByMedianFilter() {
  static int sortbuffer[buffer_length];

  for (int i = 0; i < buffer_length; i++) {
    sortbuffer[i] = buffer[i];
  }

  qsort(sortbuffer, buffer_length, sizeof(int), comparisonfunction);

  return sortbuffer[index_of_middle];
}

int comparisonfunction(const void *a, const void *b) {
  int _a = *(int *)a;
  int _b = *(int *)b;

  if (_a < _b) {
    return -1;
  } else if (_a > _b) {
    return 1;
  } else {
    return 0;
  }
  
  //return *(int *)a - *(int *)b;
  //if you prefer the latter to the former, it's OK.
  
}

