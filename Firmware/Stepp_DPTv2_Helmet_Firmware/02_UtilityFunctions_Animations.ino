/* --- VISOR LED MAPPING FUNCTION: --------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

// Function used for converting visor X and Y pixel coordinates to LED IDXs using the following format:
//
//            [LOOKING AT FRONT OF VISOR LED ARRAY]
//
// -------------------------------------------------------------
// |   Y   |     P     |                           |     P     |
// -------------------------------------------------------------
// |  y=7  |  P =  39  |  (*)  (*)  (*)  ...  (*)  |  P =   0  |
// |  y=6  |  P =  79  |  (*)  (*)  (*)  ...  (*)  |  P =  40  |
// |  y=5  |  P = 119  |  (*)  (*)  (*)  ...  (*)  |  P =  81  |
// |  y=4  |  P = 159  |  (*)  (*)  (*)  ...  (*)  |  P = 120  |
// |  y=3  |  P = 199  |  (*)  (*)  (*)  ...  (*)  |  P = 160  |
// |  y=2  |  P = 239  |  (*)  (*)  (*)  ...  (*)  |  P = 200  |
// |  y=1  |  P = 279  |  (*)  (*)  (*)  ...  (*)  |  P = 240  |
// |  y=0  |  P = 319  |  (*)  (*)  (*)  ...  (*)  |  P = 280  |
// -------------------------------------------------------------
// |   X   | --------- |  x=0  x=1  x=2       x=39 | --------- |
// -------------------------------------------------------------

unsigned int VISOR_XY(unsigned int x, unsigned int y) {
  
  if( y < VISOR_HEIGHT/2 ) { // y = 0, 1, 2, 3
    
    return ( VISOR_WIDTH * ( VISOR_HEIGHT - ( ( 2 * y                        ) + 1 ) ) ) + ( VISOR_WIDTH - ( x + 1 ) );
    
  } else { // y = 4, 5, 6, 7
    
    return ( VISOR_WIDTH * ( VISOR_HEIGHT - ( ( 2 * y - ( VISOR_HEIGHT - 1 ) ) + 1 ) ) ) + ( VISOR_WIDTH - ( x + 1 ) );
    
  }
  
}

/* --- 24-BIT COLOR GENERATION FUNCTION: --------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

uint32_t generateColor24(uint8_t r, uint8_t g, uint8_t b, uint8_t bright) {
  
  r = (r * bright) >> 8;
  g = (g * bright) >> 8;
  b = (b * bright) >> 8;
  
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  
}

/* --- COLOR WHEEL FUNCTION: --------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

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

/* --- FUNCTION FOR CLEARING LED ARRAYS (OFF): --------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void clearLEDArrays() {
  
  for(unsigned int i = 0; i < MAX_LED_STRIP_LEN*8; i++) {
    LED.setPixel(i,0x000000);
  }
  
  LED.show(); // Displaying on LED arrays
  
}

/* --- TEMPLE LED ARRAY DEFAULT COLORING (THOMAS DISCOVERY HELMET) ------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void templeLEDArrayDefault(uint8_t bright) {
  
  // Setting default colors (Daft Punk Discovery Helmet Style) for right temple LED array:
  LED.setPixel((RTEMP_STRT_IDX + 0), generateColor24(255,   0,   0, bright)); // Red
  LED.setPixel((RTEMP_STRT_IDX + 1), generateColor24(255, 255,   0, bright)); // Yellow
  LED.setPixel((RTEMP_STRT_IDX + 2), generateColor24(  0, 255,   0, bright)); // Green
  LED.setPixel((RTEMP_STRT_IDX + 3), generateColor24(  0,   0, 255, bright)); // Blue
  
  // Setting default colors (Daft Punk Discovery Helmet Style) for left temple LED array:
  LED.setPixel((LTEMP_STRT_IDX + 0), generateColor24(255,   0,   0, bright)); // Red
  LED.setPixel((LTEMP_STRT_IDX + 1), generateColor24(255, 255,   0, bright)); // Yellow
  LED.setPixel((LTEMP_STRT_IDX + 2), generateColor24(  0, 255,   0, bright)); // Green
  LED.setPixel((LTEMP_STRT_IDX + 3), generateColor24(  0,   0, 255, bright)); // Blue

  LED.show();
}
