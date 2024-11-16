// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int IRPin = 3;
const int LEDPin = 7;
// defines variables
long duration;
int distance;
int IRdistance;
int check = 0;
bool locked;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(IRPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  //attachInterrupt(digitalPinToInterrupt(IRPin), lock, RISING);
  //attachInterrupt(digitalPinToInterrupt(IRPin), unlock, FALLING);
  Serial.begin(9600); // Starts the serial communication
  delay(500);
}
void loop() {
  // Clears the trigPin
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
  if (distance <= 30) {
    check = check + 1;
    Serial.println(check);
    if (distance <= 5 || check >= 50) {
      locked = 1;
      Serial.println("Wheelchair Locked. Create distance.");
      digitalWrite(LEDPin, HIGH);
    }
  }

  if (distance >= 35 && locked == 1) {
    locked = 0;
    check = 0;
    Serial.println("Wheelchair Unlocked.");
    Serial.println(locked);
    digitalWrite(LEDPin, LOW);
  }
}

void lock() {
  Serial.println("Danger! Back off!");
}

void unlock() {
  Serial.println("Wheelchair unlocked.");
}