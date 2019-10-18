// LED Audio Spectrum Analyzer Display
// 
// Creates an impressive LED light show to music input
//   using Teensy 3.1 with the OctoWS2811 adaptor board
//   http://www.pjrc.com/store/teensy31.html
//   http://www.pjrc.com/store/octo28_adaptor.html
//
// Line Level Audio Input connects to analog pin A3
//   Recommended input circuit:
//   http://www.pjrc.com/teensy/gui/?info=AudioInputAnalog
//
// This example code is in the public domain.


#include <OctoWS2811.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

// The display size and color to use
const unsigned int matrix_height = 24;
const unsigned int matrix_width = 8;
const unsigned int myColor = 0x400020;

// These parameters adjust the vertical thresholds
const float maxLevel = 0.9;      // 1.0 = max, lower is more "sensitive"
const float dynamicRange = 60.0; // total range to display, in decibels
const float linearBlend = 0.3;   // useful range is 0 to 0.7

// OctoWS2811 objects
const int ledsPerPin = matrix_width * matrix_height / 8;
DMAMEM int displayMemory[ledsPerPin*6];
int drawingMemory[ledsPerPin*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerPin, displayMemory, drawingMemory, config);

// Audio library objects
AudioInputAnalog     adc1(A3); //xy=99,55
AudioAnalyzeFFT1024  fft;      //xy=265,75
AudioConnection      patchCord1(adc1, fft);


// This array holds the volume level (0 to 1.0) for each
// vertical pixel to turn on.  Computed in setup() using
// the 3 parameters above.
float thresholdVertical[matrix_height];

// This array specifies how many of the FFT frequency bin
// to use for each horizontal pixel.  Because humans hear
// in octaves and FFT bins are linear, the low frequencies
// use a small number of bins, higher frequencies use more.
//int frequencyBinsHorizontal[matrix_width] = {1,1,1,1,2,2,2,3,3,4,5,6,7,8,9,10,11,13,15,16,18,20,23,25};
int frequencyBinsHorizontal[matrix_width] = {0,0,0,0,4,100,100,100};

// Run setup once
void setup() {
  Serial.begin(9600);
  // the audio library needs to be given memory to start working
  AudioMemory(12);

  // compute the vertical thresholds before starting
  computeVerticalLevels();

  // turn on the display
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
  //Serial.println(thresholdVertical[24]);
  unsigned int x, y, freqBin;
  float level;

  if (fft.available()) {
    // freqBin counts which FFT frequency data has been used,
    // starting at low frequency
    freqBin = 0;

    for (x=0; x < matrix_width; x++) {
      // get the volume for each horizontal pixel position
      level = fft.read(freqBin, freqBin + frequencyBinsHorizontal[x] - 1);

      // uncomment to see the spectrum in Arduino's Serial Monitor
      // Serial.print(level);
      // Serial.print("  ");

      for (y=0; y < matrix_height; y++) {
        // for each vertical pixel, check if above the threshold
        // and turn the LED on or off
        if (level >= thresholdVertical[matrix_height - y]) {
          leds.setPixel(xy(x, y), Wheel(y & 255));
        } else {
          leds.setPixel(xy(x, y), 0x000000);
        }
      }
      // increment the frequency bin count, so we display
      // low to higher frequency from left to right
      freqBin = freqBin + frequencyBinsHorizontal[x];
    }
    // after all pixels set, show them all at the same instant
    leds.show();
    // Serial.println();
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  uint8_t bright = 50;
  uint32_t color24;
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    color24 = generateColor24(255 - WheelPos * 3, 0, WheelPos * 3, bright);
    //Serial.println(color24,HEX);
    return color24;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    color24 = generateColor24(0, WheelPos * 3, 255 - WheelPos * 3, bright);
    //Serial.println(color24,HEX);
    return color24;
  }
  WheelPos -= 170;
  color24 = generateColor24(WheelPos * 3, 255 - WheelPos * 3, 0, bright);
  //Serial.println(color24,HEX);
  return color24;
}


uint32_t generateColor24(uint8_t r, uint8_t g, uint8_t b, uint8_t bright) {
  r = (r * bright) >> 8;
  g = (g * bright) >> 8;
  b = (b * bright) >> 8;
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Run once from setup, the compute the vertical levels
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
