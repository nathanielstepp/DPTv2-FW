#include <Adafruit_NeoPixel.h>
#define PIXELNUM 2
#define NUMPIXEL 4
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXEL, PIXELNUM, NEO_RGB + NEO_KHZ800);

int delaytime = 500;

void setup() {
  leds.begin();
}

void loop() {
  leds.setPixelColor(0, leds.Color(255,  0,  0)); // Moderately bright red color.
  leds.setPixelColor(1, leds.Color(255,255,  0)); // Moderately bright yellow color.
  leds.setPixelColor(2, leds.Color(  0,255,  0)); // Moderately bright green color.
  leds.setPixelColor(3, leds.Color(  0,  0,255)); // Moderately bright blue color.
  leds.show();
  delay(delaytime);
  leds.setPixelColor(0, leds.Color(  0,  0,255)); // Moderately bright red color.
  leds.setPixelColor(1, leds.Color(255,  0,  0)); // Moderately bright yellow color.
  leds.setPixelColor(2, leds.Color(255,255,  0)); // Moderately bright green color.
  leds.setPixelColor(3, leds.Color(  0,255,  0)); // Moderately bright blue color.
  leds.show();
  delay(delaytime);
  leds.setPixelColor(0, leds.Color(  0,255,  0)); // Moderately bright red color.
  leds.setPixelColor(1, leds.Color(  0,  0,255)); // Moderately bright yellow color.
  leds.setPixelColor(2, leds.Color(255,  0,  0)); // Moderately bright green color.
  leds.setPixelColor(3, leds.Color(255,255,  0)); // Moderately bright blue color.
  leds.show();
  delay(delaytime);
  leds.setPixelColor(0, leds.Color(255,255,  0)); // Moderately bright red color.
  leds.setPixelColor(1, leds.Color(  0,255,  0)); // Moderately bright yellow color.
  leds.setPixelColor(2, leds.Color(  0,  0,255)); // Moderately bright green color.
  leds.setPixelColor(3, leds.Color(255,  0,  0)); // Moderately bright blue color.
  leds.show();
  delay(delaytime);
}
