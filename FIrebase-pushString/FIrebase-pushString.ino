#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "luna-ai-secretary.firebaseio.com"
#define FIREBASE_AUTH "sAR8yXUhP0KTmV8FMTfYfnmPwb1KjAvNSbCHNnza"
#define WIFI_SSID "Angelhackathon"
#define WIFI_PASSWORD "angel1234"
#define relayPin 5

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/queue");
}

void loop() {
  Firebase.pushString("queue", "relay1on");
  delay(3000);
  Serial.println("relay1on");
  Firebase.pushString("queue", "relay1off");
  delay(3000);
  Serial.println("relay1off");
}
