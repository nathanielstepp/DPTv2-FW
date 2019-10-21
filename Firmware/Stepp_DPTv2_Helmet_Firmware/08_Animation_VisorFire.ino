// These parameters control the fire appearance
// (try controlling these with knobs / analogRead....)
unsigned int heat = VISOR_WIDTH / 5;
unsigned int focus = 9;
unsigned int cool = 26;

// Arrays for fire animation
unsigned char canvas[VISOR_WIDTH*VISOR_HEIGHT];
extern const unsigned int fireColor[100];
const int fireAnimationBrightness = 30;

void Animation_VisorFire(){
  
  unsigned int i, c, n, x, y;
  const int wait = 45;

  for(unsigned int i = 0; i < EAR_LENGTH; i++){
    LED.setPixel(REAR_STRT_IDX + i, generateColor24(0,255,0,earBrightness));
    LED.setPixel(LEAR_STRT_IDX + i, generateColor24(0,255,0,earBrightness));
  }

  templeLEDArrayDefault(templeBrightness);

  // Step 1: move all data up one line
  memmove(canvas + VISOR_WIDTH, canvas, VISOR_WIDTH * (VISOR_HEIGHT - 1));
  memset(canvas, 0, VISOR_WIDTH);

  // Step 2: draw random heatspots on bottom line
  i = heat;
  if (i > VISOR_WIDTH - 8) i = VISOR_WIDTH - 8;
  while (i > 0) {
    x = random(VISOR_WIDTH - 2) + 1;
    if (canvas[x] == 0) {
      canvas[x] = 99;
      i--;
    }
  }

  // Step 3: interpolate
  for (y=0; y < VISOR_HEIGHT; y++) {
    for (x=0; x < VISOR_WIDTH; x++) {
      c = canvas[y * VISOR_WIDTH + x] * focus;
      n = focus;
      if (x > 0) {
        c = c + canvas[y * VISOR_WIDTH + (x - 1)];
        n = n + 1;
      }
      if (x < VISOR_WIDTH - 1) {
        c = c + canvas[y * VISOR_WIDTH + (x + 1)];
        n = n + 1;
      }
      if (y > 0) {
        c = c + canvas[(y -1) * VISOR_WIDTH + x];
        n = n + 1;
      }
      if (y < VISOR_HEIGHT - 1) {
        c = c + canvas[(y + 1) * VISOR_WIDTH + x];
        n = n + 1;
      }
      c = (c + (n / 2)) / n;
      i = (random(1000) * cool) / 10000;
      if (c > i) {
        c = c - i;
      } else {
        c = 0;
      }
      canvas[y * VISOR_WIDTH + x] = c;
    }
  }

  // Step 4: render canvas to LEDs
  for (y=0; y < VISOR_HEIGHT; y++) {
    for (x=0; x < VISOR_WIDTH; x++) {
      c = canvas[((VISOR_HEIGHT - 1) - y) * VISOR_WIDTH + x];
      LED.setPixel(VISOR_XY(x, y), fireColor[c]);
    }
  }
  
  LED.show();
  monitoredDelay(wait);
  if(animationState != 6) return;
}

const unsigned int fireColor[100] = {
generateColor24(0,0,0,fireAnimationBrightness),
generateColor24(1,0,0,fireAnimationBrightness),
generateColor24(2,0,0,fireAnimationBrightness),
generateColor24(3,0,0,fireAnimationBrightness),
generateColor24(5,0,0,fireAnimationBrightness),
generateColor24(7,0,0,fireAnimationBrightness),
generateColor24(9,0,0,fireAnimationBrightness),
generateColor24(11,0,0,fireAnimationBrightness),
generateColor24(13,0,0,fireAnimationBrightness),
generateColor24(15,0,0,fireAnimationBrightness),
generateColor24(18,0,0,fireAnimationBrightness),
generateColor24(20,0,0,fireAnimationBrightness),
generateColor24(23,0,0,fireAnimationBrightness),
generateColor24(26,0,0,fireAnimationBrightness),
generateColor24(28,0,0,fireAnimationBrightness),
generateColor24(31,0,0,fireAnimationBrightness),
generateColor24(34,0,0,fireAnimationBrightness),
generateColor24(37,0,0,fireAnimationBrightness),
generateColor24(41,0,0,fireAnimationBrightness),
generateColor24(44,0,0,fireAnimationBrightness),
generateColor24(47,0,0,fireAnimationBrightness),
generateColor24(52,0,0,fireAnimationBrightness),
generateColor24(55,0,0,fireAnimationBrightness),
generateColor24(59,0,0,fireAnimationBrightness),
generateColor24(63,0,0,fireAnimationBrightness),
generateColor24(66,0,0,fireAnimationBrightness),
generateColor24(70,0,0,fireAnimationBrightness),
generateColor24(74,0,0,fireAnimationBrightness),
generateColor24(78,0,0,fireAnimationBrightness),
generateColor24(83,0,0,fireAnimationBrightness),
generateColor24(88,0,0,fireAnimationBrightness),
generateColor24(92,0,0,fireAnimationBrightness),
generateColor24(96,0,0,fireAnimationBrightness),
generateColor24(100,0,0,fireAnimationBrightness),
generateColor24(105,0,0,fireAnimationBrightness),
generateColor24(109,0,0,fireAnimationBrightness),
generateColor24(114,0,0,fireAnimationBrightness),
generateColor24(119,0,0,fireAnimationBrightness),
generateColor24(123,0,0,fireAnimationBrightness),
generateColor24(128,0,0,fireAnimationBrightness),
generateColor24(133,0,0,fireAnimationBrightness),
generateColor24(138,0,0,fireAnimationBrightness),
generateColor24(142,0,0,fireAnimationBrightness),
generateColor24(147,0,0,fireAnimationBrightness),
generateColor24(152,0,0,fireAnimationBrightness),
generateColor24(158,0,0,fireAnimationBrightness),
generateColor24(164,0,0,fireAnimationBrightness),
generateColor24(169,0,0,fireAnimationBrightness),
generateColor24(174,0,0,fireAnimationBrightness),
generateColor24(180,0,0,fireAnimationBrightness),
generateColor24(184,0,0,fireAnimationBrightness),
generateColor24(187,1,0,fireAnimationBrightness),
generateColor24(189,2,0,fireAnimationBrightness),
generateColor24(192,3,0,fireAnimationBrightness),
generateColor24(195,5,0,fireAnimationBrightness),
generateColor24(197,6,0,fireAnimationBrightness),
generateColor24(200,8,0,fireAnimationBrightness),
generateColor24(203,10,0,fireAnimationBrightness),
generateColor24(206,13,0,fireAnimationBrightness),
generateColor24(209,15,0,fireAnimationBrightness),
generateColor24(211,18,0,fireAnimationBrightness),
generateColor24(214,20,0,fireAnimationBrightness),
generateColor24(217,23,0,fireAnimationBrightness),
generateColor24(220,26,0,fireAnimationBrightness),
generateColor24(223,28,0,fireAnimationBrightness),
generateColor24(226,31,0,fireAnimationBrightness),
generateColor24(228,34,0,fireAnimationBrightness),
generateColor24(231,37,0,fireAnimationBrightness),
generateColor24(234,41,0,fireAnimationBrightness),
generateColor24(237,44,0,fireAnimationBrightness),
generateColor24(240,47,0,fireAnimationBrightness),
generateColor24(245,52,0,fireAnimationBrightness),
generateColor24(248,55,0,fireAnimationBrightness),
generateColor24(251,59,0,fireAnimationBrightness),
generateColor24(254,63,0,fireAnimationBrightness),
generateColor24(255,67,0,fireAnimationBrightness),
generateColor24(255,73,0,fireAnimationBrightness),
generateColor24(255,79,1,fireAnimationBrightness),
generateColor24(255,85,1,fireAnimationBrightness),
generateColor24(255,93,2,fireAnimationBrightness),
generateColor24(255,99,2,fireAnimationBrightness),
generateColor24(255,106,3,fireAnimationBrightness),
generateColor24(255,113,4,fireAnimationBrightness),
generateColor24(255,120,4,fireAnimationBrightness),
generateColor24(255,127,5,fireAnimationBrightness),
generateColor24(255,134,6,fireAnimationBrightness),
generateColor24(255,141,7,fireAnimationBrightness),
generateColor24(255,150,8,fireAnimationBrightness),
generateColor24(255,158,9,fireAnimationBrightness),
generateColor24(255,165,10,fireAnimationBrightness),
generateColor24(255,173,11,fireAnimationBrightness),
generateColor24(255,181,12,fireAnimationBrightness),
generateColor24(255,189,13,fireAnimationBrightness),
generateColor24(255,197,14,fireAnimationBrightness),
generateColor24(255,206,15,fireAnimationBrightness),
generateColor24(255,214,16,fireAnimationBrightness),
generateColor24(255,224,18,fireAnimationBrightness),
generateColor24(255,233,20,fireAnimationBrightness),
generateColor24(255,242,21,fireAnimationBrightness),
generateColor24(255,251,22,fireAnimationBrightness),
};

