
#include <SPI.h>
#include <max7456.h>
Max7456 osd;

#include "FrSkySportSensor.h"
#include "FrSkySportSensorXjt.h"
#include "FrSkySportSingleWireSerial.h"
#include "FrSkySportDecoder.h"
#include "SoftwareSerial.h"

FrSkySportSensorXjt xjt;            // Create XJT sensor with default ID
FrSkySportDecoder decoder;        // Create decoder object without polling

static float GPS_scaleLonDown; // this is used to offset the shrinking longitude as we go towards the poles
float GPS_HOME_lat = 57.693978; //HOME
float GPS_HOME_long = 39.768207; //HOME
float GPS_NOW_lat;
float GPS_NOW_long;
uint16_t GPS_HOME_dist;
int16_t GPS_HOME_bearing;

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_250ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;

void setup() {
  SPI.begin();
  osd.init(10);
  osd.setDisplayOffsets(60, 18);
  osd.setBlinkParams(_8fields, _BT_BT);
  osd.activateOSD();

  // Configure the decoder serial port and sensors (remember to use & to specify a pointer to sensor)
  decoder.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_5, &xjt);
  Serial.begin(115200);
}

void loop() {
  TIMEMACHINE_loop();
}



