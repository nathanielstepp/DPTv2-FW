#include <OctoWS2811.h>
#include <Audio.h>

const unsigned int matrix_height = 8;
const unsigned int matrix_width = 40;

const int ledsPerPin = 80;
DMAMEM int displayMemory[ledsPerPin*6];
int drawingMemory[ledsPerPin*6];
const int config = WS2811_RGB | WS2811_800kHz;
OctoWS2811 leds(ledsPerPin, displayMemory, drawingMemory, config);

AudioInputAnalog     adc1(A3); //xy=99,55
AudioAnalyzeFFT1024  fft;      //xy=265,75
AudioConnection      patchCord1(adc1, fft);

void setup() {
  leds.begin();
  leds.show();
  Serial.begin(9600);
  AudioMemory(12);
  computeVerticalLevels();
//  pinMode(18,OUTPUT);
//  digitalWrite(18,HIGH);
}

/*----------------------------------------------------------------------------------------------*/

const unsigned int led_bar_width = 2;
const unsigned int spectrum_width = matrix_width/led_bar_width;

const float maxLevel = 0.5;      // 1.0 = max, lower is more "sensitive"
const float dynamicRange = 15.0; // total range to display, in decibels
const float linearBlend = 0.25;   // useful range is 0 to 0.7
const float smoothingCoeff_POS = 0.1; // 0.0 to 1.0, lower value == more responsive
const float smoothingCoeff_NEG = 0.85; // 0.0 to 1.0, higher value == slower fall

int freqUpperBin[spectrum_width] = {0,2,4,7,10,14,19,25,32,41,52,65,81,101,125,154,189,232,285,349};
int freqLowerBin[spectrum_width] = {0,1,3,5,8,11,15,20,26,33,42,53,66,82,102,126,155,190,233,286};

float thresholdVertical[matrix_height];

float LEVEL_NEW, LEVEL_OLD[spectrum_width], DIFF;
unsigned int i, j, x, y;

void loop() {
  if (fft.available()) {
    
    for (i=0; i < spectrum_width; i++) {
      LEVEL_NEW = fft.read(freqLowerBin[i], freqUpperBin[i]);
      DIFF = LEVEL_NEW - LEVEL_OLD[i];
      if (DIFF > 0.0) {
        LEVEL_NEW = LEVEL_NEW - DIFF*smoothingCoeff_POS;
      } else {
        LEVEL_NEW = LEVEL_NEW - DIFF*smoothingCoeff_NEG;
      }
      LEVEL_OLD[i] = LEVEL_NEW;
      for (j=0; j < led_bar_width; j++) {
        x = i*led_bar_width + j;
        for (y=0; y < matrix_height; y++) {
          if (LEVEL_NEW >= thresholdVertical[matrix_height - y]) {
            leds.setPixel(VISOR_XY(x, y), Wheel(12*y-85));
          } else {
            leds.setPixel(VISOR_XY(x, y), 0x000000);
          }
        }
      }
    }
    leds.show();
  }
}

/*----------------------------------------------------------------------------------------------*/

void computeVerticalLevels() {
  unsigned int y;
  float n, logLevel, linearLevel;
  for (y=0; y < matrix_height; y++) {
    n = (float)y / (float)(matrix_height - 1);
    logLevel = pow10f(n * -1.0 * (dynamicRange / 20.0));
    linearLevel = 1.0 - n;
    linearLevel = linearLevel * linearBlend;
    logLevel = logLevel * (1.0 - linearBlend);
    thresholdVertical[y] = (logLevel + linearLevel) * maxLevel;
  }
}

/*----------------------------------------------------------------------------------------------*/

unsigned int VISOR_XY(unsigned int x, unsigned int y) {
  return ( matrix_width * ( matrix_height - y ) ) + ( x - matrix_width );
}

/*----------------------------------------------------------------------------------------------*/

uint32_t Wheel(byte WheelPos) {
  uint8_t bright = 10;
  uint32_t color24;
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    color24 = generateColor24(255 - WheelPos * 3, 0, WheelPos * 3, bright);
    return color24;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    color24 = generateColor24(0, WheelPos * 3, 255 - WheelPos * 3, bright);
    return color24;
  }
  WheelPos -= 170;
  color24 = generateColor24(WheelPos * 3, 255 - WheelPos * 3, 0, bright);
  return color24;
}

/*----------------------------------------------------------------------------------------------*/

uint32_t generateColor24(uint8_t r, uint8_t g, uint8_t b, uint8_t bright) {
  r = (r * bright) >> 8;
  g = (g * bright) >> 8;
  b = (b * bright) >> 8;
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
