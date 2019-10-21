/* --- TBD: -------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

// Initializing microphone audio connection:
AudioInputAnalog    adc1(MIC_PIN); //xy=99,55
AudioAnalyzeFFT1024 FFT1024;       //xy=265,75
AudioConnection     patchCord1(adc1, FFT1024);

 // Spectrum analyzer display configuration parameters:
const unsigned int audioBarWidth = 2;
const unsigned int spectrumWidth = VISOR_WIDTH/audioBarWidth;

// Audio processing parameters:
const float maxLevel = 0.6;      // 1.0 = max, lower is more "sensitive"
const float dynamicRange = 20.0; // total range to display, in decibels
const float linearBlend = 0.3;   // useful range is 0 to 0.7
const float smoothingCoeff_POS = 0.1; // 0.0 to 1.0, lower value == more responsive
const float smoothingCoeff_NEG = 0.85; // 0.0 to 1.0, higher value == slower fall

// Frequency bin defintions:
const unsigned int freqUpperBin[spectrumWidth] = {0,2,4,7,10,14,19,25,32,41,52,65,81,101,125,154,189,232,285,349};
const unsigned int freqLowerBin[spectrumWidth] = {0,1,3,5,8,11,15,20,26,33,42,53,66,82,102,126,155,190,233,286};

// Calculating audio threshhold arrays for visor and ear LED arrays:
float visorThresholdVertical[VISOR_HEIGHT]; // Visor LED array thresholds
float earThresholdVertical[EAR_LENGTH]; // Ear LED array thresholds

// General definitions for temporary variables:
float LEVEL_NEW, LEVEL_OLD[spectrumWidth], LEVEL_EAR_OLD, DIFF;

/* --- TBD: -------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void Animation_AudioSpectrumAnalyzer() {
  
  if (FFT1024.available()) {
    
    // Updating visor LED array:
    for (unsigned int i = 0; i < spectrumWidth; i++) {
      LEVEL_NEW = FFT1024.read(freqLowerBin[i], freqUpperBin[i]);
      DIFF = LEVEL_NEW - LEVEL_OLD[i];
      if (DIFF > 0.0) {
        LEVEL_NEW = LEVEL_NEW - DIFF*smoothingCoeff_POS;
      } else {
        LEVEL_NEW = LEVEL_NEW - DIFF*smoothingCoeff_NEG;
      }
      LEVEL_OLD[i] = LEVEL_NEW;
      for (unsigned int j = 0; j < audioBarWidth; j++) {
        unsigned int x = i*audioBarWidth + j;
        for (unsigned int y = 0; y < VISOR_HEIGHT; y++) {
          if (LEVEL_NEW >= visorThresholdVertical[(VISOR_HEIGHT - 1) - y]) {
            LED.setPixel(VISOR_XY(x, y), colorWheel(12*y - 85,visorBrightness));
          } else {
            LED.setPixel(VISOR_XY(x, y), 0x000000);
          }
        }
      }
    }
    
    // Updating ear LED arrays:
    LEVEL_NEW = FFT1024.read(freqLowerBin[0], freqUpperBin[1]);
    DIFF = LEVEL_NEW - LEVEL_EAR_OLD;
    if (DIFF > 0.0) {
      LEVEL_NEW = LEVEL_NEW - DIFF*smoothingCoeff_POS;
    } else {
      LEVEL_NEW = LEVEL_NEW - DIFF*smoothingCoeff_NEG;
    }
    LEVEL_EAR_OLD = LEVEL_NEW;
    for (unsigned int k = 0; k < EAR_LENGTH; k++) {
      if (LEVEL_NEW >= earThresholdVertical[k]) {
        LED.setPixel((LEAR_STRT_IDX + k), generateColor24(0,255,0,earBrightness)); // Left ear
        LED.setPixel((REAR_STRT_IDX + ((EAR_LENGTH - 1) - k)), generateColor24(0,255,0,earBrightness)); // Right ear
      } else {
        LED.setPixel((LEAR_STRT_IDX + k), 0x000000); // Left ear
        LED.setPixel((REAR_STRT_IDX + ((EAR_LENGTH - 1) - k)), 0x000000); // Right ear
      }
    }

    // Updating temple LED arrays:
    templeLEDArrayDefault(templeBrightness);
    
    // Updating LED arrays:
    LED.show();
    
  }
  
}

/* --- TBD: -------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void computeVisorVerticalLevels() {
  
  float n, logLevel, linearLevel;
  
  for (unsigned int y = 0; y < VISOR_HEIGHT; y++) {
    n = (float)y / (float)(VISOR_HEIGHT - 1);
    logLevel = pow10f(n * -1.0 * (dynamicRange / 20.0));
    linearLevel = 1.0 - n;
    linearLevel = linearLevel * linearBlend;
    logLevel = logLevel * (1.0 - linearBlend);
    visorThresholdVertical[y] = (logLevel + linearLevel) * maxLevel;
  }
  
}

/* --- TBD: -------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void computeEarVerticalLevels() {
  
  float n, logLevel, linearLevel;
  
  for (unsigned int y = 0; y < EAR_LENGTH; y++) {
    n = (float)y / (float)(EAR_LENGTH - 1);
    logLevel = pow10f(n * -1.0 * (dynamicRange / 20.0));
    linearLevel = 1.0 - n;
    linearLevel = linearLevel * linearBlend;
    logLevel = logLevel * (1.0 - linearBlend);
    earThresholdVertical[y] = (logLevel + linearLevel) * maxLevel;
  }
  
}
