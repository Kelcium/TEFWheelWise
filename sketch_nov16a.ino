#include <HttpClient.h>
#include <b64.h>
#include <WiFi.h>
#include <WiFiClient.h>

// defines pins numbers
// trigger pin for all ultrasounds are the same
const int trigPin = 9;

// echo or input pin for all ultrasounds are different and they matter
const int echo1Pin = 10;
const int echo2Pin = 11;
const int echo3Pin = 12;
const int echo4Pin = 13;

// set all ultrasound positions in 90 degree intervals, starting with 45
const int echo1Pos = 45;
const int echo2Pos = 135;
const int echo3Pos = 225;
const int echo4Pos = 315;

// simulate wheelchair locking
const int LEDPin = 7;

// defines variables
long duration1;
long duration2;
long duration3;
long duration4;

int distance1;
int distance2;
int distance3;
int distance4;

int check = 0;
bool locked;
bool speed;
long time;
long time_next;

String echoType = "ultrasound";

// void speed_out(distance_past, distance) {
//   if (distance_past - distance >= 100) {
//     return true;
//   }
//   else {
//     return false;
//   }
// }

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo1Pin, INPUT);
  pinMode(echo2Pin, INPUT);
  pinMode(echo3Pin, INPUT);
  pinMode(echo4Pin, INPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  Serial.begin(9600); // Starts the serial communication
  delay(500);
  time = millis();
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
  duration1 = pulseIn(echo1Pin, HIGH);
  duration2 = pulseIn(echo2Pin, HIGH);
  duration3 = pulseIn(echo3Pin, HIGH);
  duration4 = pulseIn(echo4Pin, HIGH);

  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  distance2 = duration2 * 0.034 / 2;
  distance3 = duration3 * 0.034 / 2;
  distance4 = duration4 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distances: ");
  //Serial.println(distance1, distance2, distance3, distance4);

  //String data = "{\"timestamp\": " + String(millis()) + ", \"data\": {\"frequency\": " + String(storedFrequency) + " , \"fall_detection\" : " + String(fallDetected) + "}}"; sendDataToServer(data);

  String data = "{\"arbitrary_key1\": [" + echoType + time + echo1Pin + distance1 + "], " + "arbitrary_key2: [" + echoType + time + echo2Pin + distance2 + "], " +
  "arbitrary_key3: [" + echoType + time + echo3Pin + distance3 + "], " + "arbitrary_key4: [" + echoType + time + echo4Pin + distance4 + "] " + "\}";
  
  // if (distance <= 30) {
  //   check = check + 1;
  // }
  // if (distance <= 5 || check >= 50) {
  //   locked = 1;
  //   Serial.println("Wheelchair Locked. Create distance.");
  //   digitalWrite(LEDPin, HIGH);
  // }

  // if (distance >= 35 && locked == 1) {
  //   locked = 0;
  //   check = 0;
  //   Serial.println("Wheelchair Unlocked.");
  //   Serial.println(locked);
  //   digitalWrite(LEDPin, LOW);
  // }

  // time_next = millis();
  // if (time_next - time > 1000) {
  //   time = millis();
  //   // return 
  // }
}