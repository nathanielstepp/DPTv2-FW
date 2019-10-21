void Animation_Cylon() {
  
  const uint8_t rowA = 4;
  const uint8_t rowB = 3;
  const uint8_t wait = 35;
  const uint8_t animationBrightness = 3;

  for(unsigned int i = 0; i < EAR_LENGTH; i++){
    LED.setPixel(REAR_STRT_IDX + i, generateColor24(0,255,0,earBrightness));
    LED.setPixel(LEAR_STRT_IDX + i, generateColor24(0,255,0,earBrightness));
  }

  templeLEDArrayDefault(templeBrightness);
  
  // Scroll right to left:
  for(unsigned int i = 0; i < VISOR_WIDTH; i++) {
    for(unsigned int j = VISOR_STRT_IDX; j < VISOR_STOP_IDX; j++) {
      LED.setPixel(j,0x000000);
    }
    for(unsigned int j = 0; j < VISOR_WIDTH; j++) {
      LED.setPixel(VISOR_XY(j,rowA + 1),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(j,rowA    ),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(j,rowB    ),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(j,rowB - 1),generateColor24(255,0,0,animationBrightness));
    }
    if(i >= 2 && i <= ((VISOR_WIDTH - 1) - 2)){
      // Two pixels left
      LED.setPixel(VISOR_XY(i - 2,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i - 2,(rowA + 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i - 2,(rowB - 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i - 2,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      // One pixel left
      LED.setPixel(VISOR_XY(i - 1,(rowA + 3)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i - 1,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i - 1,(rowA + 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(i - 1,(rowA    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i - 1,(rowB    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i - 1,(rowB - 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(i - 1,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i - 1,(rowB - 3)),generateColor24(255,0,0,animationBrightness));
      // Middle pixel
      LED.setPixel(VISOR_XY(i    ,(rowA + 3)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(i    ,(rowA + 2)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(i    ,(rowA + 1)),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i    ,(rowA    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i    ,(rowB    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i    ,(rowB - 1)),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i    ,(rowB - 2)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(i    ,(rowB - 3)),generateColor24(255,0,0,visorBrightness));
      // One pixel right
      LED.setPixel(VISOR_XY(i + 1,(rowA + 3)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i + 1,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i + 1,(rowA + 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(i + 1,(rowA    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i + 1,(rowB    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(i + 1,(rowB - 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(i + 1,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i + 1,(rowB - 3)),generateColor24(255,0,0,animationBrightness));
      // Two pixels right
      LED.setPixel(VISOR_XY(i + 2,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i + 2,(rowA + 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i + 2,(rowB - 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(i + 2,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      LED.show();
      monitoredDelay(wait);
      if(animationState != 2) return;
    }
  }
  // Scroll left to right:
  for(unsigned int i = 0; i < VISOR_WIDTH; i++) {
    for(unsigned int j = VISOR_STRT_IDX; j < VISOR_STOP_IDX; j++) {
      LED.setPixel(j,0x000000);
    }
    for(unsigned int j = 0; j < VISOR_WIDTH; j++) {
      LED.setPixel(VISOR_XY(j,rowA + 1),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(j,rowA    ),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(j,rowB    ),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(j,rowB - 1),generateColor24(255,0,0,animationBrightness));
    }
    if(i >= 2 && i <= ((VISOR_WIDTH - 1) - 2)){
      // Two pixels left
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 2,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 2,(rowA + 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 2,(rowB - 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 2,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      // One pixel left
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowA + 3)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowA + 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowA    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowB    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowB - 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) - 1,(rowB - 3)),generateColor24(255,0,0,animationBrightness));
      // Middle pixel
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowA + 3)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowA + 2)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowA + 1)),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowA    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowB    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowB - 1)),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowB - 2)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i)    ,(rowB - 3)),generateColor24(255,0,0,visorBrightness));
      // One pixel right
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowA + 3)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowA + 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowA    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowB    )),generateColor24(255,63,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowB - 1)),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 1,(rowB - 3)),generateColor24(255,0,0,animationBrightness));
      // Two pixels right
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 2,(rowA + 2)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 2,(rowA + 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 2,(rowB - 1)),generateColor24(255,0,0,animationBrightness));
      LED.setPixel(VISOR_XY(((VISOR_WIDTH - 1) - i) + 2,(rowB - 2)),generateColor24(255,0,0,animationBrightness));
      LED.show();
      monitoredDelay(wait);
      if(animationState != 2) return;
    }
  }
  
}
