#include <Adafruit_NeoPixel.h>
#define neopixelPin 2
#define neopixelNum 8
#define relayPin 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, neopixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connected: ");
  pinMode(relayPin, OUTPUT);
  strip.begin();
  strip.show();
}

void loop() {
  digitalWrite(relayPin, HIGH);
  delay(2000);
  for (int i=0; i < neopixelNum; i++) {
    strip.setPixelColor(i, 255, 255, 255);
  }
  strip.show();
  digitalWrite(relayPin, LOW);
  delay(2000);
  for (int i=0; i < neopixelNum; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}
