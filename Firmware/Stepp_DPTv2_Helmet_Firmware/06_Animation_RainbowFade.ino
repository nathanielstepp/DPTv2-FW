void Animation_RainbowFade() {
  static uint8_t hue = 0;
  for(unsigned int i = 0; i < VISOR_WIDTH; i++) {
    for(unsigned int j = 0; j < VISOR_HEIGHT; j++) {
      LED[VISOR_XY(i,j)] = CHSV((1*j) + hue+i,255,255);
    }
  }
  hue++;
  LEDS.show(); // Updating LED arrays
  monitoredDelay(30);
}

