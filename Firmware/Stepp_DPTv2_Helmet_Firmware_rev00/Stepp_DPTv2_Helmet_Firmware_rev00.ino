/* --- FILE INFORMATION: ------------------------------------------------------------------------------------------------

    Filename:    Stepp_DPTv2_Helmet_Firmware_rev00
    Project:     Daft Punk Thomas Helmet
    Created By:  Nathaniel A. Stepp
    Created On:  09 February 2018
    
    IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
    pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
    and minimize distance between Arduino and first pixel.  Avoid connecting
    on a live circuit...if you must, connect GND first.

---------------------------------------------------------------------------------------------------------------------- */

/* --- CODING LIBRARY INCLUSION STATEMENTS: -----------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

#include <OctoWS2811.h>
#include <SPI.h>
#include <SD.h>

/* --- PARAMETER DEFINITIONS FOR HELMET LED ARRAYS ----------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

// Defining parameter constants for helmet visor LED array:
#define VISOR_LED_STRIP_IDX_A  1 // Index representing starting LED strip (1-8 per OctoWS2811 libary)
#define VISOR_LED_STRIP_IDX_B  4 // Index representing ending LED strip (1-8 per OctoWS2811 libary)
#define VISOR_WIDTH           40 // Number of LEDs along visor array width
#define VISOR_HEIGHT           8 // Number of LEDs along visor array height
// Calculating helmet visor LED array LED strip length:
const int VISOR_LED_STRIP_LEN = (VISOR_WIDTH * VISOR_HEIGHT) / (VISOR_LED_STRIP_IDX_B - (VISOR_LED_STRIP_IDX_A - 1));

// Defining parameter constants for helmet right ear LED array:
#define REAR_LED_STRIP_IDX_A   5 // Index representing starting LED strip (1-8 per OctoWS2811 libary)
#define REAR_LED_STRIP_IDX_B   5 // Index representing ending LED strip (1-8 per OctoWS2811 libary)
#define REAR_WIDTH            24 // Number of LEDs along right ear array width
#define REAR_HEIGHT            1 // Number of LEDs along right ear array height
// Calculating helmet right ear LED array LED strip length:
const int REAR_LED_STRIP_LEN = (REAR_WIDTH * REAR_HEIGHT) / (REAR_LED_STRIP_IDX_B - (REAR_LED_STRIP_IDX_A - 1));

// Defining parameter constants for helmet left ear LED array:
#define LEAR_LED_STRIP_IDX_A   6 // Index representing starting LED strip (1-8 per OctoWS2811 libary)
#define LEAR_LED_STRIP_IDX_B   6 // Index representing ending LED strip (1-8 per OctoWS2811 libary)
#define LEAR_WIDTH            24 // Number of LEDs along left ear array width
#define LEAR_HEIGHT            1 // Number of LEDs along left ear array height
// Calculating helmet left ear LED array LED strip length:
const int LEAR_LED_STRIP_LEN = (LEAR_WIDTH * LEAR_HEIGHT) / (LEAR_LED_STRIP_IDX_B - (LEAR_LED_STRIP_IDX_A - 1));

// Defining parameter constants for helmet right temple LED array:
#define RTEMP_LED_STRIP_IDX_A  7 // Index representing starting LED strip (1-8 per OctoWS2811 libary)
#define RTEMP_LED_STRIP_IDX_B  7 // Index representing ending LED strip (1-8 per OctoWS2811 libary)
#define RTEMP_WIDTH            1 // Number of LEDs along right temple array width
#define RTEMP_HEIGHT           5 // Number of LEDs along right temble array height
// Calculating helmet right temple LED array LED strip length:
const int RTEMP_LED_STRIP_LEN = (RTEMP_WIDTH * RTEMP_HEIGHT) / (RTEMP_LED_STRIP_IDX_B - (RTEMP_LED_STRIP_IDX_A - 1));

// Defining parameter constants for helmet left temple LED array:
#define LTEMP_LED_STRIP_IDX_A  8 // Index representing starting LED strip (1-8 per OctoWS2811 libary)
#define LTEMP_LED_STRIP_IDX_B  8 // Index representing ending LED strip (1-8 per OctoWS2811 libary)
#define LTEMP_WIDTH            1 // Number of LEDs along left temple array width
#define LTEMP_HEIGHT           5 // Number of LEDs along left temple array height
// Calculating helmet left temple LED array LED strip length:
const int LTEMP_LED_STRIP_LEN = (LTEMP_WIDTH * LTEMP_HEIGHT) / (LTEMP_LED_STRIP_IDX_B - (LTEMP_LED_STRIP_IDX_A - 1));

// Determining from all defined LED arrays what the max LED strip length is:
const int TEMP_ARRAY[] = { VISOR_LED_STRIP_LEN,
                           REAR_LED_STRIP_LEN ,
                           LEAR_LED_STRIP_LEN ,
                           RTEMP_LED_STRIP_LEN,
                           LTEMP_LED_STRIP_LEN };
const int MAX_LED_STRIP_LEN = TEMP_ARRAY[1];

// Defining the start and stop LED indicies for the helmet visor LED array:
const int VISOR_STRT_IDX =   MAX_LED_STRIP_LEN * ( VISOR_LED_STRIP_IDX_A - 1 );
const int VISOR_STOP_IDX = ( MAX_LED_STRIP_LEN *   VISOR_LED_STRIP_IDX_B ) - 1;

// Defining the start and stop LED indicies for the helmet right ear LED array:
const int REAR_STRT_IDX  =   MAX_LED_STRIP_LEN * ( REAR_LED_STRIP_IDX_A - 1 );
const int REAR_STOP_IDX  = ( MAX_LED_STRIP_LEN *   REAR_LED_STRIP_IDX_B ) - 1;

// Defining the start and stop LED indicies for the helmet left ear LED array:
const int LEAR_STRT_IDX  =   MAX_LED_STRIP_LEN * ( LEAR_LED_STRIP_IDX_A - 1 );
const int LEAR_STOP_IDX  = ( MAX_LED_STRIP_LEN *   LEAR_LED_STRIP_IDX_B ) - 1;

// Defining the start and stop LED indicies for the helmet right temple LED array:
const int RTEMP_STRT_IDX  =   MAX_LED_STRIP_LEN * ( RTEMP_LED_STRIP_IDX_A - 1 );
const int RTEMP_STOP_IDX  = ( MAX_LED_STRIP_LEN *   RTEMP_LED_STRIP_IDX_B ) - 1;

// Defining the start and stop LED indicies for the helmet left temple LED array:
const int LTEMP_STRT_IDX  =   MAX_LED_STRIP_LEN * ( LTEMP_LED_STRIP_IDX_A - 1 );
const int LTEMP_STOP_IDX  = ( MAX_LED_STRIP_LEN *   LTEMP_LED_STRIP_IDX_B ) - 1;

/* ----------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

DMAMEM int displayMemory[MAX_LED_STRIP_LEN*6];
int drawingMemory[MAX_LED_STRIP_LEN*6];
elapsedMicros elapsedSinceLastFrame = 0;
bool playing = false;

#define SD_CS_PIN 3

/* ----------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

OctoWS2811 led(MAX_LED_STRIP_LEN, displayMemory, drawingMemory, WS2811_800kHz);
File videoFile;

/* --- INITIAL SETUP & DEFINITIONS: -------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void setup() {
  
  // Initiating serial communication via Teensy 3.2 USB @ BAUD = 115200
  Serial.begin(115200);
  
  led.begin();
  led.show();
  
//  if (!SD.begin(SD_CS_PIN)) {
//    stopWithErrorMessage("Could not access SD card.");
//  }
//  Serial.println("SD card detected and accessed.");
//  
//  videoFile = SD.open(DEFAULT_FILE, FILE_READ);
//  if (!videofile) {
//    stopWithErrorMessage("Could not read filename: " DEFAULT_FILE);
//  }
//  Serial.println("Filename '" DEFAULT_FILE "' successfully read and opened.");
//  playing = true;
//  elapsedSinceLastFrame = 0;
  
}

/* ----------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void loop() {

  delay(5000);
  
  Serial.print("Visor LED Start IDX: ");
  Serial.println(VISOR_STRT_IDX);
  Serial.println("");

  Serial.print("Visor LED Stop IDX: ");
  Serial.println(VISOR_STOP_IDX);
  Serial.println("");

  while(1);
  
}

/* ----------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

const int findMax(const int TEMP_ARRAY[]) {
  int MAX_VAL = 0;
  for ( int i = 0; i < sizeof(TEMP_ARRAY); i++ ) {
    if ( TEMP_ARRAY[i] > MAX_VAL ) {
      MAX_VAL = TEMP_ARRAY[i];
    }
  }
  return MAX_VAL;
}

/* ----------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void stopWithErrorMessage(const char *str) {
  while (1) {
    Serial.println(str);
    delay(1000);
  }
}

