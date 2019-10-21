/* --- VISOR LED MAPPING FUNCTION: --------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

// Function used for converting visor X and Y pixel coordinates to LED IDXs using the following: format:
//
// -------------------------------------------------------------
// |   Y   |     P     |                           |     P     |
// -------------------------------------------------------------
// |  y=8  |  P =  39  |  (*)  (*)  (*)  ...  (*)  |  P =   0  |
// |  y=7  |  P =  79  |  (*)  (*)  (*)  ...  (*)  |  P =  40  |
// |  y=6  |  P = 119  |  (*)  (*)  (*)  ...  (*)  |  P =  81  |
// |  y=5  |  P = 159  |  (*)  (*)  (*)  ...  (*)  |  P = 120  |
// |  y=4  |  P = 199  |  (*)  (*)  (*)  ...  (*)  |  P = 160  |
// |  y=3  |  P = 239  |  (*)  (*)  (*)  ...  (*)  |  P = 200  |
// |  y=2  |  P = 279  |  (*)  (*)  (*)  ...  (*)  |  P = 240  |
// |  y=1  |  P = 319  |  (*)  (*)  (*)  ...  (*)  |  P = 280  |
// -------------------------------------------------------------
// |   X   | --------- |  x=1  x=2  x=3       x=40 | --------- |
// -------------------------------------------------------------

unsigned int VISOR_XY(unsigned int x, unsigned int y) {
  return ( VISOR_WIDTH * ( VISOR_HEIGHT - y ) ) + ( x - VISOR_WIDTH );
  
}

/* --- 24-BIT COLOR GENERATION FUNCTION: --------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

uint32_t generateColor24(uint8_t r, uint8_t g, uint8_t b, uint8_t bright) {
  
//  r = (r * bright) >> 8;
//  g = (g * bright) >> 8;
//  b = (b * bright) >> 8;
  
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  
}

/* --- COLOR WHEEL FUNCTION: --------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

uint32_t Wheel(byte WheelPos) {
  
  uint8_t bright = 255;
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

/* --- FUNCTION FOR CLEARING LED ARRAYS (OFF): --------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void clearLEDArrays() {
  for(unsigned int i = 0; i < MAX_LED_STRIP_LEN*8; i++) {
    LED[i] = 0x000000;
  }
  LEDS.show(); // Updating LED arrays
}

/* --- TEMPLE LED ARRAY DEFAULT COLORING (THOMAS DISCOVERY HELMET) ------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void templeLEDArrayDefault() {
  
  // Setting default colors (Daft Punk Discovery Helmet Style) for right temple LED array:
  LED[RTEMP_STRT_IDX + 0] = CRGB::Red; // Red
  LED[RTEMP_STRT_IDX + 1] = CRGB::Yellow; // Yellow
  LED[RTEMP_STRT_IDX + 2] = CRGB::Green; // Green
  LED[RTEMP_STRT_IDX + 3] = CRGB::Blue; // Blue
  
  // Setting default colors (Daft Punk Discovery Helmet Style) for left temple LED array:
  LED[LTEMP_STRT_IDX + 0] = CRGB::Red; // Red
  LED[LTEMP_STRT_IDX + 1] = CRGB::Yellow; // Yellow
  LED[LTEMP_STRT_IDX + 2] = CRGB::Green; // Green
  LED[LTEMP_STRT_IDX + 3] = CRGB::Blue; // Blue
  
  LEDS.show();
}
