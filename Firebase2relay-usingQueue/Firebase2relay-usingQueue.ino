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
  
  String path = "";
  String data = "";
  if(Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    eventType.toLowerCase();
    if(eventType == "put") {
      path = event.getString("path");
      data = event.getString("data");
      Serial.print("DATA : ");
      Serial.println(data);
      Serial.print("PATH : ");
      Serial.println(path);
    }
  }
  if(data == "relay1on") {
    digitalWrite(relayPin,HIGH);
    removeData(path);
  }
  if(data == "relay1off") {
    digitalWrite(relayPin,LOW);
    removeData(path);
  }
}

void removeData(String path) {
  Firebase.remove("/queue" + path);
}
