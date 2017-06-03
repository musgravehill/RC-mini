/*
      USE RESISTOR TO S.PORT FROM 5v-ARDUINO.

			  The default S.Port rate for polling a GPS is 1 hz.

			  Use hardware serial for GPS. Disconnect GPS when programming.

          Also note that to avoid interrupt conflict with the mentioned SoftwareSerial library you need to disable attitude (roll/pitch)
          sensing in the NazaDecoder library by uncommenting the following line in NazaDecoder.h file:
          //#define ATTITUDE_SENSING_DISABLED
*/

#include "FrSkySportTelemetry/FrSkySportSensor.h"
#include "FrSkySportTelemetry/FrSkySportSingleWireSerial.h"
#include "FrSkySportTelemetry/FrSkySportTelemetry.h"
#include "FrSkySportTelemetry/FrSkySportPolling.h"

#include "FrSkySportTelemetry/FrSkySportSensor.cpp"
#include "FrSkySportTelemetry/FrSkySportSingleWireSerial.cpp"
#include "FrSkySportTelemetry/FrSkySportTelemetry.cpp"
#include "FrSkySportTelemetry/FrSkySportPolling.cpp"
#include <SoftwareSerial.h>

#include "FrSkySportTelemetry/FrSkySportSensorGps.h"
#include "FrSkySportTelemetry/FrSkySportSensorFcs.h"

#include "FrSkySportTelemetry/FrSkySportSensorGps.cpp"
#include "FrSkySportTelemetry/FrSkySportSensorFcs.cpp"

FrSkySportSensorFcs sensor_fcs_main;
FrSkySportSensorFcs sensor_fcs_video(FrSkySportSensor::ID15);
FrSkySportSensorGps sensor_gps;

FrSkySportTelemetry frsky_telemetry;

#include <TinyGPS++.h>
TinyGPSPlus gps_parser;

float gps_lat, gps_lng; //float -48.99999999
int16_t gps_alt; //+- m
int16_t gps_speed; // m/s
float    gps_course; // 90.23 Course over ground in degrees (0-359, 0 = north)
int16_t gps_y, gps_m, gps_d; //17, 4, 29,  Date (year - 2000, month, day)
int16_t gps_h, gps_i, gps_s; // 12,59, 59);   // Time (hour, minute, second) - will be affected by timezone setings in your radio

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_333ms = 0L;

void setup() {
  frsky_telemetry.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_12, &sensor_fcs_main, &sensor_fcs_video, &sensor_gps);
  Serial.begin(57600);
  Serial.flush();
  delay(3000); //5s
  Serial.println(F("$PMTK300,1000,0,0,0,0*1C")); //1Hz
  Serial.flush();
}

void loop() {
  while (Serial.available() > 0) {
    GPS_process();
  }
  TIMEMACHINE_loop();
}







