#include <OctoWS2811.h>

#include <Audio.h>
AudioInputAnalog     adc1(A3);

const int ledsPerStrip = 80;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  leds.begin();
  leds.show();
}

#define RED    0x160000
#define GREEN  0x001600
#define BLUE   0x000016
#define YELLOW 0x101400
#define PINK   0x120009
#define ORANGE 0x100400
#define WHITE  0x101010

#define R1_A   0
#define R1_B  39

#define R2_A  40
#define R2_B  79

#define R3_A  80
#define R3_B 119

#define R4_A 120
#define R4_B 159

#define R5_A 160
#define R5_B 199

#define R6_A 200
#define R6_B 239

#define R7_A 240
#define R7_B 279

#define R8_A 280
#define R8_B 319

void loop() {
  int i;
  for(i = R8_A; i < ( R8_B + 1 ); i++){
    leds.setPixel(i,generateColor24(255,255,255,50));
  }
  leds.show();
  delay(100);
}

uint32_t generateColor24(uint8_t r, uint8_t g, uint8_t b, uint8_t bright) {
  r = (r * bright) >> 8;
  g = (g * bright) >> 8;
  b = (b * bright) >> 8;
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
