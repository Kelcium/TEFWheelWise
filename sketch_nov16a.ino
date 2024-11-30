#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>

// defines pins numbers
// trigger pin for all ultrasounds are the same
const int trigPin = 27;
// echo or input pin for all ultrasounds are different and they matter
const int echo1Pin = 13;
const int echo2Pin = 15;
const int echo3Pin = 16;
const int echo4Pin = 17;

// set all ultrasound positions in 90 degree intervals, starting with 45
const int echo1Pos = 45;
const int echo2Pos = 135;
const int echo3Pos = 225;
const int echo4Pos = 315;

// simulate wheelchair locking
// const int LEDPin = 7;

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
long time_now;
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
//  pinMode(LEDPin, OUTPUT);
//  digitalWrite(LEDPin, LOW);
  Serial.begin(115200); // Starts the serial communication
  delay(500);
  time_now = millis();
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

  String data = "{\"arbitrary_key1\": [" + String(echoType) + String(time_now) + String(echo1Pin) + String(distance1) + "], " + "arbitrary_key2: [" + String(echoType) + String(time_now) + String(echo2Pin) + String(distance2) + "], " +
  "arbitrary_key3: [" + String(echoType) + String(time_now) + String(echo3Pin) + String(distance3) + "], " + "arbitrary_key4: [" + String(echoType) + String(time_now) + String(echo4Pin) + String(distance4) + "] " + "\}";  
  
  sendDataToServer(data);
}

void sendDataToServer(String data)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.setReuse(true);
        http.begin("https://192.168.0.104:8080/api/v1/sensors-data");
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(data);

        if (httpResponseCode > 0)
        {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        }
        else
        {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    }
    else
    {
        Serial.println("Error in WiFi connection");
    }
}

