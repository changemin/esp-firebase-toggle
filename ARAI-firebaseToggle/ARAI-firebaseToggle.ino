#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Adafruit_NeoPixel.h>
#define FIREBASE_HOST "luna-ai-secretary.firebaseio.com"
#define FIREBASE_AUTH "sAR8yXUhP0KTmV8FMTfYfnmPwb1KjAvNSbCHNnza"
#define WIFI_SSID "Angelhackathon"
#define WIFI_PASSWORD "angel1234"
#define relayPin 16
#define neopixelPin 2
#define neopixelNum 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, neopixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
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

  strip.begin();
  strip.show();
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
  if(data == "neoPixelToggle") {  
    int relayState = digitalRead(relayPin);
    if (relayState == HIGH) { 
       digitalWrite(relayPin , LOW);
       for (int i=0; i < neopixelNum; i++) {
          strip.setPixelColor(i, 255, 255, 255);
       }
       strip.show();
       removeData("neopixelToggle");
      } 
    if (relayState == LOW){
      digitalWrite(relayPin, HIGH);
      for (int i=0; i < neopixelNum; i++) {
        strip.setPixelColor(i, 0, 0, 0);
      }
      strip.show();
      removeData("neopixelToggle");
    } 
  }
}

void removeData(String path) {
  Firebase.remove("/queue" + path);
}
