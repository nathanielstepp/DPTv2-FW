#include <OctoWS2811.h>

// The display size and color to use
const unsigned int matrix_height = 24;
const unsigned int matrix_width = 8;

// OctoWS2811 objects
//const int ledsPerPin = matrix_width * matrix_height / 8;
const int ledsPerPin = 24;
DMAMEM int displayMemory[ledsPerPin*6];
int drawingMemory[ledsPerPin*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerPin, displayMemory, drawingMemory, config);

void setup() {
  Serial.begin(9600);
  leds.begin();
  leds.show();
}

// A simple xy() function to turn display matrix coordinates
// into the index numbers OctoWS2811 requires.  If your LEDs
// are arranged differently, edit this code...
unsigned int xy(unsigned int x, unsigned int y) {
  return x * matrix_height + y;
}

// Run repetitively
void loop() {
  unsigned int i, x, y;
  for (i=0; i < 256; i++) {
    for (x=0; x < matrix_width; x++) {
      for (y=0; y < matrix_height; y++) {
          leds.setPixel(xy(x, y), Wheel(i & 255));
          leds.show();
          //delay(1);
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  uint8_t bright = 20;
  uint32_t color24;
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    color24 = generateColor24(255 - WheelPos * 3, 0, WheelPos * 3, bright);
    Serial.println(WheelPos);
    Serial.println(WheelPos*3);
    Serial.println(color24,HEX);
    return color24;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    color24 = generateColor24(0, WheelPos * 3, 255 - WheelPos * 3, bright);
    Serial.println(color24,HEX);
    return color24;
  }
  WheelPos -= 170;
  color24 = generateColor24(WheelPos * 3, 255 - WheelPos * 3, 0, bright);
  Serial.println(color24,HEX);
  return color24;
}


uint32_t generateColor24(uint8_t r, uint8_t g, uint8_t b, uint8_t bright) {
  r = (r * bright) >> 8;
  g = (g * bright) >> 8;
  b = (b * bright) >> 8;
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
