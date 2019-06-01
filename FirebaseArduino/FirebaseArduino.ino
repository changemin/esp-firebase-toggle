#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define WF_NAME "Angelhackathon"
#define WF_PASSWORD "angel1234"
#define FB_HOST "luna-ai-secretary.firebaseio.com"
#define FB_AUTH "sAR8yXUhP0KTmV8FMTfYfnmPwb1KjAvNSbCHNnza"

void setup() {
  Serial.begin(115200);
  WiFi.begin(WF_NAME, WF_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.print("Connect to ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FB_HOST, FB_AUTH);
  Firebase.stream("/queue");

}

void loop(){
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
}
