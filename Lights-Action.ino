#include <FastLED.h>
#include <math.h>

#define LED_PIN     10
#define NUM_LEDS    100

CRGB leds[NUM_LEDS];
int lines[3];

CRGB color = 500394;

char currChar;
char message[64];
int mPoint = 0;
boolean notTerm = true;
int mode = 1;

void setup() {
    lines[0] = 29;
    lines[1] = 33;
    lines[2] = 16 + 22;
    Serial.begin(9600);
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(100);
}

void loop() {
    if(Serial.available()){
        while(Serial.available()){
            Serial.readBytesUntil(NULL, message, 64);
        }
        Serial.println(message);
        unsigned long int col = 0;
        if(message[0] == 'C'){
            col = 0;
            for(int i = 1; message[i] != 0; i++){
                // Serial.println(col);
                col = (col * 10) + (message[i] - '0');
            }
            color = col;
        }
        else if(message[0] == 'B'){
            int bright = 0;
            for(int i = 1; message[i] != 0; i++){
                bright = (bright * 10) + (message[i] - '0');
            }
            FastLED.setBrightness(bright);
        }
        else if(message[0] == 'M'){
            mode = 0;
            for(int i = 1; message[i] != 0; i++){
                mode = (mode * 10) + (message[i] - '0');
            }
            Serial.println(mode);
        }
        for(int i = 0; i<64; i++){
            message[i] = 0;
        }
    }



    if(mode == 0){
        for(int i = 0; i<NUM_LEDS; i++){
            leds[i] = color;
        }
    }
    if(mode == 1){
        fadeToBlackBy(leds, NUM_LEDS, 20);
        for(int i = 0; i < 3; i++){
          int prev = 0;
          for(int j = 0; j < i; j++){
            prev += lines[j];
          }
          int pos = 0;
          if(i % 2 == 0){
            pos += abs(beat8(16) - 256.0/2) / (256.0/2) * lines[i] + prev;
          }
          else {
            pos += lines[i] - (abs(beat8(16) - 256.0/2) / (256.0/2) * lines[i]) + prev;
          }
          leds[pos] += color;
        }
    }
    if(mode == 2){
        fadeToBlackBy(leds, NUM_LEDS, 20);
        for(int i = 0; i < 3; i++){
          int prev = 0;
          for(int j = 0; j < i; j++){
            prev += lines[j];
          }
          int pos = 0;
          pos = abs(beat8(16) - 256.0/2) / (256.0/2) * lines[i] + prev;\
          leds[pos] += color;
          pos = lines[i] - (abs(beat8(16) - 256.0/2) / (256.0/2) * lines[i]) + prev;
          leds[pos] += color;
        }
    }
    FastLED.show();
}