void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_333ms) > 333L) {
    TIMEMACHINE_333ms();
    TIMEMACHINE_prevMicros_333ms = TIMEMACHINE_currMillis;
  }
}


void TIMEMACHINE_333ms() {
  SPORT_telemetry_send();
}
