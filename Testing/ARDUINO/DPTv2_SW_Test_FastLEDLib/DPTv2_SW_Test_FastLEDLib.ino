#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>

#include <Audio.h>
AudioInputAnalog     adc1(A3);

#define NUM_LEDS_PER_STRIP 80
#define NUM_STRIPS 8

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void setup() {
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(30);
 // pinMode(18,OUTPUT);
 // digitalWrite(18,HIGH);
}

void loop() {
  static uint8_t hue = 0;
  for(int i = 0; i < 40; i++) {
    for(int j = 0; j < 8; j++) {
      leds[xy(i,j)] = CHSV((1*j) + hue+i,255,255);
    }
  }

//  // Set the first n leds on each strip to show which strip it is
//  for(int i = 0; i < NUM_STRIPS; i++) {
//    for(int j = 0; j <= i; j++) {
//      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
//    }
//  }

  hue++;

  LEDS.show();
  LEDS.delay(30);
}

unsigned int xy(unsigned int x, unsigned int y) {
  return ( 40 * ( 8 - y ) ) + ( x - 40 );
}
