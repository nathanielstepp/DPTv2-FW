#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMPIXELS 80

int VAL_R = 0;
int VAL_G = 0;
int VAL_B = 0;
int VAL = 20;

Adafruit_NeoPixel P1 = Adafruit_NeoPixel(NUMPIXELS, 2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel P2 = Adafruit_NeoPixel(NUMPIXELS, 14, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel P3 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel P4 = Adafruit_NeoPixel(NUMPIXELS, 8, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoPixel P5 = Adafruit_NeoPixel(NUMPIXELS, 5, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoPixel P6 = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoPixel P7 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoPixel P8 = Adafruit_NeoPixel(NUMPIXELS, 8, NEO_RGB + NEO_KHZ800);

int delayval = 20; // delay for half a second

void setup() {
  P1.begin(); // This initializes the NeoPixel library.
  P2.begin(); // This initializes the NeoPixel library.
  P3.begin(); // This initializes the NeoPixel library.
  P4.begin(); // This initializes the NeoPixel library.
//  P5.begin(); // This initializes the NeoPixel library.
//  P6.begin(); // This initializes the NeoPixel library.
//  P7.begin(); // This initializes the NeoPixel library.
//  P8.begin(); // This initializes the NeoPixel library.
}

void loop() {
  
  for(int i=0;i<NUMPIXELS;i++){
    
    VAL_R = VAL;
    VAL_G = 0;
    VAL_B = 0;
    
    P1.setPixelColor(i, P1.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P2.setPixelColor(i, P2.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P3.setPixelColor(i, P3.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P4.setPixelColor(i, P4.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P5.setPixelColor(i, P5.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P6.setPixelColor(i, P6.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P7.setPixelColor(i, P7.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P8.setPixelColor(i, P8.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.

    P1.show(); // This sends the updated pixel color to the hardware.
    P2.show(); // This sends the updated pixel color to the hardware.
    P3.show(); // This sends the updated pixel color to the hardware.
    P4.show(); // This sends the updated pixel color to the hardware.
//    P5.show(); // This sends the updated pixel color to the hardware.
//    P6.show(); // This sends the updated pixel color to the hardware.
//    P7.show(); // This sends the updated pixel color to the hardware.
//    P8.show(); // This sends the updated pixel color to the hardware.    
    
    delay(delayval); // Delay for a period of time (in milliseconds).
    
  }

  for(int i=0;i<NUMPIXELS;i++){
    
    P1.setPixelColor(i, P1.Color(0,0,0)); // Moderately bright green color.
    P2.setPixelColor(i, P2.Color(0,0,0)); // Moderately bright green color.
    P3.setPixelColor(i, P3.Color(0,0,0)); // Moderately bright green color.
    P4.setPixelColor(i, P4.Color(0,0,0)); // Moderately bright green color.
//    P5.setPixelColor(i, P5.Color(0,0,0)); // Moderately bright green color.
//    P6.setPixelColor(i, P6.Color(0,0,0)); // Moderately bright green color.
//    P7.setPixelColor(i, P7.Color(0,0,0)); // Moderately bright green color.
//    P8.setPixelColor(i, P8.Color(0,0,0)); // Moderately bright green color.
    
    P1.show(); // This sends the updated pixel color to the hardware.
    P2.show(); // This sends the updated pixel color to the hardware.
    P3.show(); // This sends the updated pixel color to the hardware.
    P4.show(); // This sends the updated pixel color to the hardware.
//    P5.show(); // This sends the updated pixel color to the hardware.
//    P6.show(); // This sends the updated pixel color to the hardware.
//    P7.show(); // This sends the updated pixel color to the hardware.
//    P8.show(); // This sends the updated pixel color to the hardware.    
    
    delay(delayval); // Delay for a period of time (in milliseconds).
    
  }

  for(int i=0;i<NUMPIXELS;i++){
    
    VAL_R = 0;
    VAL_G = VAL;
    VAL_B = 0;
    
    P1.setPixelColor(i, P1.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P2.setPixelColor(i, P2.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P3.setPixelColor(i, P3.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P4.setPixelColor(i, P4.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P5.setPixelColor(i, P5.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P6.setPixelColor(i, P6.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P7.setPixelColor(i, P7.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P8.setPixelColor(i, P8.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.

    P1.show(); // This sends the updated pixel color to the hardware.
    P2.show(); // This sends the updated pixel color to the hardware.
    P3.show(); // This sends the updated pixel color to the hardware.
    P4.show(); // This sends the updated pixel color to the hardware.
//    P5.show(); // This sends the updated pixel color to the hardware.
//    P6.show(); // This sends the updated pixel color to the hardware.
//    P7.show(); // This sends the updated pixel color to the hardware.
//    P8.show(); // This sends the updated pixel color to the hardware.    
    
    delay(delayval); // Delay for a period of time (in milliseconds).
    
  }

  for(int i=0;i<NUMPIXELS;i++){
    
    P1.setPixelColor(i, P1.Color(0,0,0)); // Moderately bright green color.
    P2.setPixelColor(i, P2.Color(0,0,0)); // Moderately bright green color.
    P3.setPixelColor(i, P3.Color(0,0,0)); // Moderately bright green color.
    P4.setPixelColor(i, P4.Color(0,0,0)); // Moderately bright green color.
//    P5.setPixelColor(i, P5.Color(0,0,0)); // Moderately bright green color.
//    P6.setPixelColor(i, P6.Color(0,0,0)); // Moderately bright green color.
//    P7.setPixelColor(i, P7.Color(0,0,0)); // Moderately bright green color.
//    P8.setPixelColor(i, P8.Color(0,0,0)); // Moderately bright green color.
    
    P1.show(); // This sends the updated pixel color to the hardware.
    P2.show(); // This sends the updated pixel color to the hardware.
    P3.show(); // This sends the updated pixel color to the hardware.
    P4.show(); // This sends the updated pixel color to the hardware.
//    P5.show(); // This sends the updated pixel color to the hardware.
//    P6.show(); // This sends the updated pixel color to the hardware.
//    P7.show(); // This sends the updated pixel color to the hardware.
//    P8.show(); // This sends the updated pixel color to the hardware.    
    
    delay(delayval); // Delay for a period of time (in milliseconds).
    
  }

  for(int i=0;i<NUMPIXELS;i++){
    
    VAL_R = 0;
    VAL_G = 0;
    VAL_B = VAL;
    
    P1.setPixelColor(i, P1.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P2.setPixelColor(i, P2.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P3.setPixelColor(i, P3.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
    P4.setPixelColor(i, P4.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P5.setPixelColor(i, P5.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P6.setPixelColor(i, P6.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P7.setPixelColor(i, P7.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.
//    P8.setPixelColor(i, P8.Color(VAL_R,VAL_G,VAL_B)); // Moderately bright green color.

    P1.show(); // This sends the updated pixel color to the hardware.
    P2.show(); // This sends the updated pixel color to the hardware.
    P3.show(); // This sends the updated pixel color to the hardware.
    P4.show(); // This sends the updated pixel color to the hardware.
//    P5.show(); // This sends the updated pixel color to the hardware.
//    P6.show(); // This sends the updated pixel color to the hardware.
//    P7.show(); // This sends the updated pixel color to the hardware.
//    P8.show(); // This sends the updated pixel color to the hardware.    
    
    delay(delayval); // Delay for a period of time (in milliseconds).
    
  }

  for(int i=0;i<NUMPIXELS;i++){
    
    P1.setPixelColor(i, P1.Color(0,0,0)); // Moderately bright green color.
    P2.setPixelColor(i, P2.Color(0,0,0)); // Moderately bright green color.
    P3.setPixelColor(i, P3.Color(0,0,0)); // Moderately bright green color.
    P4.setPixelColor(i, P4.Color(0,0,0)); // Moderately bright green color.
//    P5.setPixelColor(i, P5.Color(0,0,0)); // Moderately bright green color.
//    P6.setPixelColor(i, P6.Color(0,0,0)); // Moderately bright green color.
//    P7.setPixelColor(i, P7.Color(0,0,0)); // Moderately bright green color.
//    P8.setPixelColor(i, P8.Color(0,0,0)); // Moderately bright green color.
    
    P1.show(); // This sends the updated pixel color to the hardware.
    P2.show(); // This sends the updated pixel color to the hardware.
    P3.show(); // This sends the updated pixel color to the hardware.
    P4.show(); // This sends the updated pixel color to the hardware.
//    P5.show(); // This sends the updated pixel color to the hardware.
//    P6.show(); // This sends the updated pixel color to the hardware.
//    P7.show(); // This sends the updated pixel color to the hardware.
//    P8.show(); // This sends the updated pixel color to the hardware.    
    
    delay(delayval); // Delay for a period of time (in milliseconds).
    
  }

}
