/*
 // System data
    uint8_t getRssi();
    float getAdc1();
    float getAdc2();
    float getRxBatt();
    uint8_t getSwr();

    // FGS sensor data: fuel in percent
    float getFuel();

    // FLVS sensor data: each cell voltage in volts.
    float getCell1();
    float getCell2();
    float getCell3();
    float getCell4();
    float getCell5();
    float getCell6();
    float getCell7();
    float getCell8();
    float getCell9();
    float getCell10();
    float getCell11();
    float getCell12();

    // FAS sensor data: current in amperes, voltage in volts
    float getCurrent();
    float getVoltage();

    // FVAS sensor data: altitude in meters (can be negative), vertical speed in m/s (can be nevative)
    float getAltitude();
    float getVsi();

    // GPS sensor data: lat/lon in degrees decimal (positive for N/E, negative for S/W), alt in meters (can be negative), speed in m/s, course over ground (cog) in degrees 0-359
    //                  add 2000 to year, hours in 24h format
    float getLat();
    float getLon();
    float getGpsAltitude();
    float getSpeed();
    float getCog();
    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();



*/



void decoder_dbg() {
  // Read and decode the telemetry data, note that the data will only be decoded for sensors
  // that that have been passed to the begin method. Print the AppID of the decoded data.
  //uint16_t decodeResult;
  //decodeResult = decoder.decode();
  //if (decodeResult != SENSOR_NO_DATA_ID) {
  //Serial.print("Decoded data with AppID 0x");
  //Serial.println(decodeResult, HEX);
  //}

  // Display data once a second to not interfeere with data decoding

  // Get basic XJT data (RSSI/ADC1/ADC2/RxBatt/SWR data)
  Serial.print("Basic: RSSI = "); Serial.print(xjt.getRssi()); // RSSI
  Serial.print(", ADC1 = "); Serial.print(xjt.getAdc1());      // ADC1 voltage in volts
  Serial.print("V, ADC2 = "); Serial.print(xjt.getAdc2());     // ADC2 voltage in volts
  Serial.print("V, RxBatt = "); Serial.print(xjt.getRxBatt()); // RxBatt voltage in volts
  Serial.print("V, SWR = "); Serial.println(xjt.getSwr());     // SWR

  /*
    // Get fuel sensor (FGS) data
    Serial.print("FGS: fuel = "); Serial.print(xjt.getFuel()); Serial.println("%"); // Fuel level in percent

    // Get LiPo voltage sensor (FLVS) data (each cell1-cell12 voltage in volts)
    Serial.print("FLVS: cell1 = "); Serial.print(xjt.getCell1()); Serial.print("V, cell2 = "); Serial.print(xjt.getCell2());
    Serial.print("V, cell3 = "); Serial.print(xjt.getCell3()); Serial.print("V, cell4 = "); Serial.print(xjt.getCell4());
    Serial.print("V, cell5 = "); Serial.print(xjt.getCell5()); Serial.print("V, cell6 = "); Serial.print(xjt.getCell6());
    Serial.print("V, cell7 = "); Serial.print(xjt.getCell7()); Serial.print("V, cell8 = "); Serial.print(xjt.getCell8());
    Serial.print("V, cell9 = "); Serial.print(xjt.getCell9()); Serial.print("V, cell10 = "); Serial.print(xjt.getCell10());
    Serial.print("V, cell11 = "); Serial.print(xjt.getCell11()); Serial.print("V, cell12 = "); Serial.print(xjt.getCell12()); Serial.println("V");

    // Get current/voltage sensor (FAS) data
    Serial.print("FAS: current = "); Serial.print(xjt.getCurrent());                    // Current consumption in amps
    Serial.print("A, voltage = "); Serial.print(xjt.getVoltage()); Serial.println("V"); // Battery voltage in volts

    // Get variometer sensor (FVAS) data
    Serial.print("FVAS: altitude = "); Serial.print(xjt.getAltitude()); Serial.print("m"); // Altitude in m (can be nevative)
    Serial.print("m, VSI = "); Serial.print(xjt.getVsi()); Serial.println("m/s");          // Verticas speed in m/s (can be nevative)
  */
  // Get GPS data
  Serial.print("GPS: lat = "); Serial.print(xjt.getLat(), 6); Serial.print(", lon = "); Serial.print(xjt.getLon(), 6); // Latitude and longitude in degrees decimal (positive for N/E, negative for S/W)
  Serial.print(", altitude = "); Serial.print(xjt.getAltitude()); // Altitude in m (can be negative)
  Serial.print("m, speed = "); Serial.print(xjt.getSpeed()); // Speed in m/s
  Serial.print("m/s, COG = "); Serial.print(xjt.getCog());   // Course over ground in degrees (0-359, 0 = north)
  char dateTimeStr[18];
  sprintf(dateTimeStr, "%02u-%02u-%04u %02u:%02u:%02u", xjt.getDay(), xjt.getMonth(), xjt.getYear() + 2000, xjt.getHour(), xjt.getMinute(), xjt.getSecond());
  Serial.print(", date/time = "); Serial.println(dateTimeStr); // Date (year - need to add 2000, month, day) and time (hour, minute, second)
  /*
        // Get accelerometer sensor (TAS) data
        Serial.print("TAS: ACCX = "); Serial.print(xjt.getAccX());                    // X axis acceleraton in Gs (can be negative)
        Serial.print("G, ACCY = "); Serial.print(xjt.getAccY());                      // Y axis acceleraton in Gs (can be negative)
        Serial.print("G, ACCZ = "); Serial.print(xjt.getAccZ()); Serial.println("G"); // Z axis acceleraton in Gs (can be negative)

        // Get temperature sensor (TEMS) data
        Serial.print("TEMS: T1 = "); Serial.print(xjt.getT1());                               // Temperature #1 in degrees Celsius (can be negative, will be rounded)
        Serial.print(" deg. C, T2 = "); Serial.print(xjt.getT1()); Serial.println(" deg. C"); // Temperature #2 in degrees Celsius (can be negative, will be rounded)

        // Get RPM sensor (RPMS) data
        // (set number of blades to 2 in telemetry menu to get correct rpm value)
        Serial.print("RPMS: RPM = "); Serial.println(xjt.getRpm()); // Rotations per minute
  */

  Serial.println("");
}
