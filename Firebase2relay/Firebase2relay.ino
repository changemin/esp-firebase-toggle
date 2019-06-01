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
}

int n = 0;

void loop() {

  // get value 
  Serial.print("relayIO: ");
  Serial.println(Firebase.getBool("relayIO"));
  delay(1000);

  if(Firebase.getBool("relayIO")==true){
    digitalWrite(relayPin, HIGH);
  }
  else if(Firebase.getBool("relayIO")==false){
    digitalWrite(relayPin, LOW);
  }
  // remove value
  //Firebase.remove("number");
  delay(1000);
  
  // set bool value
  Firebase.setBool("relayIO", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  if(Firebase.getBool("relayIO")==true){
    digitalWrite(relayPin, HIGH);
  }
  else if(Firebase.getBool("relayIO")==false){
    digitalWrite(relayPin, LOW);
  }
  Serial.print("relayIO: ");
  Serial.println(Firebase.getBool("relayIO"));
  delay(1000);
  Firebase.setBool("relayIO", true);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);


  delay(1000);
}
