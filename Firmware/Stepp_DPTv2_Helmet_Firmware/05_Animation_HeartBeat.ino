void Animation_HeartBeat(int currentAnimationState) {
  static uint8_t earColorState = 0;
  const int startRow = 4;
  const int endRow = 3;
  const int breakCol_1 = 5;
  const int breakCol_2 = 8;
  const int breakCol_3 = 15;
  const int breakCol_4 = 18;
  const int breakCol_5 = 21;
  const int breakCol_6 = 25;
  const int breakCol_7 = 32;
  const int breakCol_8 = 36;
  int y;
  const int wait = 50;
  
  templeLEDArrayDefault(templeBrightness);
  for(unsigned int x = 0; x < VISOR_WIDTH; x++) {
    if(x >= 0 && x < breakCol_1) {
      y = startRow;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_1 && x < breakCol_2) {
      y++;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(x,y - 1),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_2 && x < breakCol_3) {
      y--;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(x,y + 1),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_3 && x < breakCol_4) {
      y++;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(x,y - 1),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_4 && x < breakCol_5) {
      y = endRow;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_5 && x < breakCol_6) {
      y++;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(x,y - 1),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_6 && x < breakCol_7) {
      y--;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(x,y + 1),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_7 && x < breakCol_8) {
      y++;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
      LED.setPixel(VISOR_XY(x,y - 1),generateColor24(255,0,0,visorBrightness));
    } else if(x >= breakCol_8 && x < VISOR_WIDTH) {
      y = startRow;
      LED.setPixel(VISOR_XY(x,y),generateColor24(255,0,0,visorBrightness));
    }
    for(unsigned int i = 0; i < EAR_LENGTH; i++) {
      LED.setPixel(REAR_STRT_IDX + i, colorWheel(((i * 256 / EAR_LENGTH) + earColorState) & 255, earBrightness));
      LED.setPixel(LEAR_STRT_IDX + ((EAR_LENGTH - 1) - i), colorWheel(((i * 256 / EAR_LENGTH) + earColorState) & 255, earBrightness));
    }
    earColorState++;
    LED.show();
    monitoredDelay(wait);
    if(animationState != currentAnimationState) return;
  }
  for(unsigned int x = 0; x < VISOR_WIDTH; x++) {
    for(unsigned int y = 0; y < VISOR_HEIGHT; y++) {
      LED.setPixel(VISOR_XY(x,y),0x000000);
    }
    for(unsigned int i = 0; i < EAR_LENGTH; i++) {
      LED.setPixel(REAR_STRT_IDX + i, colorWheel(((i * 256 / EAR_LENGTH) + earColorState) & 255, earBrightness));
      LED.setPixel(LEAR_STRT_IDX + ((EAR_LENGTH - 1) - i), colorWheel(((i * 256 / EAR_LENGTH) + earColorState) & 255, earBrightness));
    }
    earColorState++;
    LED.show();
    monitoredDelay(wait);
    if(animationState != currentAnimationState) return;
  }
  
}
