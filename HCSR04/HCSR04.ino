#define echoPin 2
#define trigPin 3

double Duration = 0;
double Distance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  Duration = pulseIn(echoPin, HIGH);
  
  if (Duration > 0) {
    Duration = Duration/2;
    Distance = Duration*340*100/1000000;
    
    Serial.print("Distance:");
    Serial.print(Distance);
    Serial.println(" cm");
  }
  
  delay(500);
}
