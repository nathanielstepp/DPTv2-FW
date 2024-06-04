/* --- ANIMATION COMMAND MONITORING FUNCTION: ---------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void checkAnimationCMD() {
  
  // Wait for new data to arrive:
  uint8_t len = readPacket(&BLE, BLE_READPACKET_TIMEOUT);
  if (len == 0) {
    for(uint16_t i = 0; i < BLE_PACKET_BYTESIZE; i++) {
      commandPacket[i] = previousPacketBuffer[i];
    }
  } else {
    for(uint16_t i = 0; i < BLE_PACKET_BYTESIZE; i++) {
      commandPacket[i] = packetbuffer[i];
      previousPacketBuffer[i] = packetbuffer[i];
    }
    if ((commandPacket[1] == 'B') && (animationState != (commandPacket[2] - '0'))) {
      animationState = commandPacket[2] - '0';
      clearLEDArrays();
    }
  }
  
}

/* --- CUSTOM DELAY FUNCTION: -------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void monitoredDelay(unsigned int desiredDelay) {
  
  uint8_t initialAnimationState = animationState;
  elapsedMillis elapsedTime = 0;
  
  while(elapsedTime < desiredDelay) {
    checkAnimationCMD();
    if(animationState != initialAnimationState) {
      break;
    }
  }
  
}

/* --- ERROR HANDELING FUCNTION (CONTINUE): -----------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void continueWithErrorMsg(const __FlashStringHelper*err) {
  // TBD
}

/* --- ERROR HANDELING FUCNTION (STOP): ---------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------- */

void stopWithErrorMsg(const __FlashStringHelper*err) {
  
  Serial.println(err);
  while (1) {
    delay(1000);
  }
  
}
