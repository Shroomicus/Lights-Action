#include <FastLED.h>

#define LED_PIN     10
#define NUM_LEDS    100

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

CRGB color = 500394;

char currChar;
char message[64];
int mPoint = 0;
boolean notTerm = true;

void loop() {
    if(Serial.available()){
        while(Serial.available()){
            Serial.readBytesUntil(NULL, message, 64);
        }
        Serial.println(message);
        unsigned long int col = 0;
        if(message[0] == 'C'){
            for(int i = 1; message[i] != 0; i++){
                // Serial.println(col);
                col = (col * 10) + (message[i] - '0');
            }
        }
    }
    for(int i = 0; i<NUM_LEDS; i++){
        leds[i] = color;
    }
    FastLED.show();

}