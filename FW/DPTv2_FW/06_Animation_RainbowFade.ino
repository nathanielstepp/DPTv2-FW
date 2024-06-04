void Animation_RainbowFade(int currentAnimationState) {
  
  static uint8_t visorColorState = 0;
  static uint8_t earColorState = 0;
  const int animationBrightness = 15;
  const int wait = 10;
  
  if(visorColorState > 255) {
    visorColorState = 0;
  }
  
  if(earColorState > 255) {
    earColorState = 0;
  }
  
  // Setting visor LED array:
  for(unsigned int x = 0; x < VISOR_WIDTH; x++) {
    for(unsigned int y = 0; y < VISOR_HEIGHT; y++) {
      LED.setPixel(VISOR_XY(x,y), colorWheel((((x + y) * 256 / MAX_LED_STRIP_LEN) + visorColorState) & 255, animationBrightness));
    }
  }
  visorColorState++;
  
  // Setting ear LED arrays:
  for(unsigned int i = 0; i < EAR_LENGTH; i++) {
    LED.setPixel(REAR_STRT_IDX + i, colorWheel(((i * 256 / EAR_LENGTH) + earColorState) & 255, earBrightness));
    LED.setPixel(LEAR_STRT_IDX + ((EAR_LENGTH - 1) - i), colorWheel(((i * 256 / EAR_LENGTH) + earColorState) & 255, earBrightness));
  }
  earColorState++;
  
  // Setting temple LED arrays:
  templeLEDArrayDefault(templeBrightness);
  
  LED.show(); // Updating LED arrays
  monitoredDelay(wait);
  if(animationState != currentAnimationState) return;
}
