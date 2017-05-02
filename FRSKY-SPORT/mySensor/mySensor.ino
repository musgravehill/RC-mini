/*
			  The default S.Port rate for polling a GPS is 1 hz.

			  Use hardware serial for GPS. Disconnect GPS when programming.

          Also note that to avoid interrupt conflict with the mentioned SoftwareSerial library you need to disable attitude (roll/pitch)
          sensing in the NazaDecoder library by uncommenting the following line in NazaDecoder.h file:
          //#define ATTITUDE_SENSING_DISABLED
*/

#include "FrSkySportSensor.h"
#include "FrSkySportSingleWireSerial.h"
#include "FrSkySportTelemetry.h"
#include "SoftwareSerial.h"

#include "FrSkySportSensorGps.h"
#include "FrSkySportSensorFlvss.h"

FrSkySportSensorFlvss sensor_flvss;
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



void setup() {
  frsky_telemetry.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_12, &sensor_flvss, &sensor_gps);
  Serial.begin(57600);
  delay(5000); //5s
  Serial.println("$PMTK300,1000,0,0,0,0*1C"); //1Hz
}

void loop() {

  while (Serial.available() > 0) {
    if (gps_parser.encode(Serial.read())) {
      if (gps_parser.location.isValid())  {
        gps_lat = gps_parser.location.lat();
        gps_lng = gps_parser.location.lng();
      }
      if (gps_parser.altitude.isValid()) {
        gps_alt = gps_parser.altitude.meters();
      }
      if (gps_parser.speed.isValid()) {
        gps_speed = gps_parser.speed.kmph();
      }
      if (gps_parser.course.isValid()) {
        gps_course = gps_parser.course.deg();
      }
      if (gps_parser.date.isValid()) {
        gps_y = gps_parser.date.year() - 2000;
        gps_m = gps_parser.date.month();
        gps_d = gps_parser.date.day();
      }
      if (gps_parser.time.isValid()) {
        gps_h = gps_parser.time.hour();
        gps_i = gps_parser.time.minute();
        gps_s = gps_parser.time.second();
      }

      //printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
      //printInt(gps.hdop.value(), gps.hdop.isValid(), 5);
      //printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
      //printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
      //printInt(gps.location.age(), gps.location.isValid(), 5);
      //printDateTime(gps.date, gps.time);
      //printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
      //printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
      //printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
      //printStr(gps.course.isValid() ? gps_parserlus::cardinal(gps.course.value()) : "*** ", 6);
    }
  }





  sensor_flvss.setData(4.10, 4.11, 4.12);

  //setData(float lat, float lon, float alt, float speed, float cog, uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
  sensor_gps.setData(gps_lat, gps_lng,   // Latitude and longitude in degrees decimal (positive for N/E, negative for S/W)
                     gps_alt ,                 // Altitude in m (can be negative)
                     gps_speed,                 // Speed in m/s
                     gps_course,                 // Course over ground in degrees (0-359, 0 = north)
                     gps_y, gps_m, gps_d,             // Date (year - 2000, month, day)
                     gps_h, gps_i, gps_s);           // Time (hour, minute, second) - will be affected by timezone setings in your radio

  frsky_telemetry.send();
}







