void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_250ms) > 250L) {
    TIMEMACHINE_250ms();
    TIMEMACHINE_prevMicros_250ms = TIMEMACHINE_currMillis;
  }

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_1000ms) > 1000L) {
    TIMEMACHINE_1000ms();
    TIMEMACHINE_prevMicros_1000ms = TIMEMACHINE_currMillis;
  }
}


void TIMEMACHINE_250ms() {
  //OSD_render();
}

void  TIMEMACHINE_1000ms() {
  //decoder_dbg();
  GPS_test();
}
