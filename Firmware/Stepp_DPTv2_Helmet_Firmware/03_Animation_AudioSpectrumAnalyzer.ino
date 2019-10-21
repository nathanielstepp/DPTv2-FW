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
const float maxLevel = 0.5;      // 1.0 = max, lower is more "sensitive"
const float dynamicRange = 15.0; // total range to display, in decibels
const float linearBlend = 0.25;   // useful range is 0 to 0.7
const float smoothingCoeff_POS = 0.1; // 0.0 to 1.0, lower value == more responsive
const float smoothingCoeff_NEG = 0.85; // 0.0 to 1.0, higher value == slower fall

// Frequency bin defintions:
int freqUpperBin[spectrumWidth] = {0,2,4,7,10,14,19,25,32,41,52,65,81,101,125,154,189,232,285,349};
int freqLowerBin[spectrumWidth] = {0,1,3,5,8,11,15,20,26,33,42,53,66,82,102,126,155,190,233,286};

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
            LED[VISOR_XY(x, y)] = Wheel(12*y - 85);
          } else {
            LED[VISOR_XY(x, y)] = 0x000000;
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
        LED[LEAR_STRT_IDX + k].setRGB(0,255,0); // Left ear
        LED[REAR_STRT_IDX + (EAR_LENGTH - k)].setRGB(0,255,0); // Right ear
      } else {
        LED[LEAR_STRT_IDX + k] = 0x000000; // Left ear
        LED[REAR_STRT_IDX + (EAR_LENGTH - k)] = 0x000000; // Right ear
      }
    }

    // Updating temple LED arrays:
    templeLEDArrayDefault();
    LEDS.show(); // Updating LED arrays
    
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
