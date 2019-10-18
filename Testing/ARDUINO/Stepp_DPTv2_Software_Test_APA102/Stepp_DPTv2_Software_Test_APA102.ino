#include <FastLED.h>
#define NUM_LEDS  1
#define DATA_PIN  12
#define CLOCK_PIN 13

static uint8_t earColorState = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(1);
}

void loop() {
      leds[0] = CRGB::Red; 
      FastLED.show();
      delay(1000);

      leds[0] = CRGB::Yellow; 
      FastLED.show();
      delay(1000);
      
      leds[0] = CRGB::Green;
      FastLED.show();
      delay(1000);
      
      leds[0] = CRGB::Cyan; 
      FastLED.show();
      delay(1000);
      
      leds[0] = CRGB::Blue;
      FastLED.show();
      delay(1000);
      
      leds[0] = CRGB::Magenta;
      FastLED.show();
      delay(1000);

      leds[0] = CRGB::White;
      FastLED.show();
      delay(1000);
      
      leds[0] = CRGB::Black;
      FastLED.show();
      delay(1000);
}

uint32_t colorWheel(byte wheelPos, uint8_t bright) {
  
  uint32_t color24;
  
  wheelPos = 255 - wheelPos;
  
  if(wheelPos < 85) {
    color24 = generateColor24(255 - wheelPos * 3, 0, wheelPos * 3, bright);
    return color24;
  }
  
  if(wheelPos < 170) {
    wheelPos -= 85;
    color24 = generateColor24(0, wheelPos * 3, 255 - wheelPos * 3, bright);
    return color24;
  }
  
  wheelPos -= 170;
  color24 = generateColor24(wheelPos * 3, 255 - wheelPos * 3, 0, bright);
  return color24;
  
}

uint32_t generateColor24(uint8_t r, uint8_t g, uint8_t b, uint8_t bright) {
  
  r = (r * bright) >> 8;
  g = (g * bright) >> 8;
  b = (b * bright) >> 8;
  
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  
}
