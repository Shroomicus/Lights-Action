#include <FastLED.h>

#define LED_PIN     10
#define NUM_LEDS    100

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    Serial.println("Hello?");
}

void loop() {
  if(Serial.available()){
    String incomingByte = Serial.readString();
    Serial.println(incomingByte);
  }
  for(int i = 0; i<NUM_LEDS; i++){
      leds[i] = 0x2b0045;
    }
  FastLED.show();

}