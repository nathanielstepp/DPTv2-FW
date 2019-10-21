void Animation_EarAndTempleRainbow(int currentAnimationState) {
  
  static uint8_t earColorState = 0;
  const int wait = 10;
  
  if(earColorState > 255) {
    earColorState = 0;
  }
  
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
