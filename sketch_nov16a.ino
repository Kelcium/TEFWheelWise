// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int IRPin = 3;
// defines variables
long duration;
int distance;
int IRdistance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(IRPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(IRPin), lock, RISING);
  attachInterrupt(digitalPinToInterrupt(IRPin), unlock, FALLING);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  // IRdistance = digitalRead(IRPin);
  IRdistance = 0;
  if (IRdistance == 0) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  else {
    delay(100);
    Serial.println("Danger! Back off!");
  }
}

void lock() {
  Serial.println("Danger! Back off!");
}

void unlock() {
  Serial.println("Wheelchair unlocked.");
}