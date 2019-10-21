/* --- FILE INFORMATION: ------------------------------------------------------------------------------------------------

    Filename:    Stepp_DPTv2_Helmet_Firmware_rev02
    Project:     Daft Punk Thomas Helmet
    Component:   Helmet Control Board Firmware
    Created By:  Nathaniel A. Stepp
    Created On:  August 2018
    
    IMPORTANT: To reduce LED pixel burnout risk, add 1000 uF capacitor across
    pixel power leads for each LED array, add 300 - 500 Ohm resistor on first
    pixel's data input, and minimize distance between Arduino and first pixel.  
    Avoid connecting on a live circuit... if you must, connect GND first.

    TEENSY 3.2 PIN CONNECTIONS:
      PIN  2 = LED STRIP #1 - Visor LED Array, Rows 1 & 2
      PIN 14 = LED STRIP #2 - Visor LED Array, Rows 3 & 4
      PIN  7 = LED STRIP #3 - Visor LED Array, Rows 5 & 6
      PIN  8 = LED STRIP #4 - Visor LED Array, Rows 7 & 8
      PIN  6 = LED STRIP #5 - Left Ear LED Array
      PIN 20 = LED STRIP #6 - Right Ear LED Array
      PIN 21 = LED STRIP #7 - Right Temple LED Array
      PIN  5 = LED STRIP #8 - Left Temple LED Array
      PIN 19 = Adafruit Bluefruit UART Friend Breakout Board, MOD Pin
      PIN  1 = Adafruit Bluefruit UART Friend Breakout Board, RX Pin
      PIN  0 = Adafruit Bluefruit UART Friend Breakout Board, TX Pin
      PIN  3 = PJRC SD Card Adapter, CS Pin
      PIN 13 = PJRC SD Card Adapter, SCK Pin
      PIN 11 = PJRC SD Card Adapter, MOSI Pin
      PIN 12 = PJRC SD Card Adapter, MISO Pin
      PIN  9 = PJRC SD Card Adapter, CD Pin
      PIN A3 = Microphone Analog Input
      PIN 18 = Fan Control On/Off Control

---------------------------------------------------------------------------------------------------------------------- */

/* --- CODING LIBRARY INCLUSION STATEMENTS: -----------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

#include <OctoWS2811.h>
#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

/* --- PARAMETER DEFINITIONS --------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

// Teensy 3.2 Pin Definitions:
#define BT_MOD_PIN  19 // Bluetooth Mode Control Pin (On/Off) Defintion
#define SD_CS_PIN    3 // SD Card Chip Select Pin Definition
#define SD_CD_PIN    9 // SD Card Card Detect Pin Definition
#define MIC_PIN     A3 // Microphone Signal Analog Input Pin Definition
#define FAN_PIN     18 // Fan MOSFET Control Pin (On/Off) Definition

// Visor LED Array Definitions:
#define MAX_LED_STRIP_LEN   80 // Maximimum number of LEDs attached to each Teensy 3.2 LED pin
#define VISOR_WIDTH         40 // Number of LEDs along visor LED array width
#define VISOR_HEIGHT         8 // Number of LEDs along visor LED array height
#define EAR_LENGTH          24 // Number of LEDs along ear LED array circumference
#define VISOR_STRT_IDX       0 // Visor LED Array first LED pixel index
#define VISOR_STOP_IDX     319 // Visor LED Array last LED pixel index
#define LEAR_STRT_IDX      320 // Left Ear LED Array first LED pixel index
#define LEAR_STOP_IDX      343 // Left Ear LED Array last LED pixel index
#define REAR_STRT_IDX      400 // Right Ear LED Array first LED pixel index
#define REAR_STOP_IDX      423 // Right Ear LED Array last LED pixel index
#define RTEMP_STRT_IDX     480 // Right Temple LED Array first LED pixel index
#define RTEMP_STOP_IDX     483 // Right Temple LED Array last LED pixel index
#define LTEMP_STRT_IDX     560 // Left Temple LED Array first LED pixel index
#define LTEMP_STOP_IDX     563 // Left Temple LED Array last LED pixel index

// Other Definitions:
#define FACTORYRESET_ENABLE   1 // Bluetooth Factory Reset on Startup Flag
#define BLE_PACKET_BYTESIZE  21 // Expected maximum packet size in bytes recived over bluetooth

byte visorBrightness = 20;
byte earBrightness = 150;
byte templeBrightness = 90;

byte animationState = 0;

/* INITIALIZATIONS: -----------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

// OctoWS2811 Library Initialization:
DMAMEM int displayMemory[MAX_LED_STRIP_LEN*6]; // Memory Preallocation
int drawingMemory[MAX_LED_STRIP_LEN*6]; // Memory Preallocation
const int config = WS2811_RGB | WS2811_800kHz;
OctoWS2811 LED(MAX_LED_STRIP_LEN, displayMemory, drawingMemory, WS2811_800kHz); // OctoWS2811 Library Initialization

// Adafruit BLE / Bluefruit Library Initialziation:
Adafruit_BluefruitLE_UART BLE(Serial1, BT_MOD_PIN);
// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *BLE, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);
// the packet buffer
extern uint8_t packetbuffer[];
uint8_t previousPacketBuffer[BLE_PACKET_BYTESIZE];
uint8_t commandPacket[BLE_PACKET_BYTESIZE];

/* --- ARDUINO SETUP FUNCTION: ------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void setup() {
  
/* ------------------------------------------------------------------------------------------------------------------- */
  
  // Initialization of LED Arrays:
  LED.begin(); // Turning on LED arrays
  clearLEDArrays(); // Setting all LED colors to display no color (off, 0x000000):
  delay(500);
  Animation_EarAndTempleRainbow();
  delay(500);
  
/* ------------------------------------------------------------------------------------------------------------------- */
  
  pinMode(FAN_PIN,OUTPUT);
  digitalWrite(FAN_PIN,HIGH);
  delay(500);
  
/* ------------------------------------------------------------------------------------------------------------------- */
  
  AudioMemory(12);
  computeVisorVerticalLevels();
  computeEarVerticalLevels();
  
/* ------------------------------------------------------------------------------------------------------------------- */
  
  // Initiating serial communication via Teensy 3.2 USB @ BAUD = 115200
  Serial.begin(115200);
//  while(!Serial) {
//    ; // Wait for serial port to connect. Needed for native USB port only
//  }
  
/* ------------------------------------------------------------------------------------------------------------------- */
  
  if (!SD.begin(SD_CS_PIN)) {
    stopWithErrorMsg(F("Could not access SD card"));
  }
  Serial.println("SD card ok");
  
/* ------------------------------------------------------------------------------------------------------------------- */
  
  // Inialization of Adafruit Bluefruit UART Friend Breakout Board:
  Serial.println(F("Initialising the Bluefruit LE module: "));
  if (!BLE.begin(VERBOSE_MODE)) {
    stopWithErrorMsg(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println(F("OK!"));
  if (FACTORYRESET_ENABLE) {
    Serial.println(F("Performing a factory reset: "));
    if ( ! BLE.factoryReset() ) {
      stopWithErrorMsg(F("Couldn't factory reset"));
    }
  }
  BLE.echo(false);
  Serial.println("Requesting Bluefruit info:");
  BLE.info();
  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  BLE.verbose(true);
  while (! BLE.isConnected()) {
    delay(500);
  }
  Serial.println(F("***********************"));
  Serial.println( F("Switching to DATA mode!") );
  BLE.setMode(BLUEFRUIT_MODE_DATA);
  Serial.println(F("***********************"));
  
/* ------------------------------------------------------------------------------------------------------------------- */
  
}

/* --- ARDUINO LOOP FUNCTION: -------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void loop() {
  
  checkAnimationCMD();
  
  if (animationState == 1){
    Animation_AudioSpectrumAnalyzer();
  }
  
  if (animationState == 2){
    Animation_Cylon();
  }
  
  if (animationState == 3){
    Animation_HeartBeat();
  }
  
  if (animationState == 4){
    Animation_RainbowFade();
  }

  if (animationState == 5){
    Animation_EarAndTempleRainbow();
  }
  
  if (animationState == 6){
    Animation_VisorFire();
  }
  
  if (animationState == 8){
    clearLEDArrays();
  }
  
}
