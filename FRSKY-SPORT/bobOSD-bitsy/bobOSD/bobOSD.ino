/**
  http://github.com/FPVTools/BitsyOSD
**/


/**
    PROGMEM Header, we don't really use the EEPROM (yet)
*/
/*
  #undef PROGMEM
  #define PROGMEM __attribute__(( section(".progmem.data") ))

  #undef PSTR
  #define PSTR(s) (__extension__({static prog_char __c[] PROGMEM = (s); &__c[0];}))
*/

/**
    (Includes)
*/


// Global

#include <math.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include <FastSerial.h>

// Local
#include "const.h"
#include "config.h"
#include "max7456.h"
#include "osd.h"

//FastSerialPort0

OSD osd;


void setup() {
  // select osd output
  pinMode(MAX7456_SELECT,  OUTPUT);

  // Prepare OSD for displaying
  unplugSlaves();

  osd.init();
  osd.clear();  

  // pre boot delay
  delay(500);

  // boot message
  MessageAlert(true, " BOOT");
  DrawLogo();

  // boot time
  delay(5000);
     
}


/**
    (Loop) Here is where the magic happens, keep it simple and fast
*/

void loop() {

  // Main loop
  Update();

  // Mandatory delay for proper display update
  delay(50);
}


void Update() {

  UpdateDisplay();
}

void UpdateDisplay() {
  /*  DrawTimer(vma(LAYOUT_OSDTIME_X, -1), vma(LAYOUT_OSDTIME_Y, 3), millis(), NO_SYMBOL, true);
    DrawStatus(LAYOUT_GPS_X, LAYOUT_GPS_Y, true, SYMBOL_GPS);
    DrawOneSmallValue(LAYOUT_GPS_X + 1, LAYOUT_GPS_Y, gpsdata.Satellites > 9 ? 9 : gpsdata.Satellites);
    DrawBattery(vma(LAYOUT_BATTERY1_X, -1), LAYOUT_BATTERY1_Y, runtime.voltage1, TYPE_BATTERY1, DISPLAY_MODE_BATTERY1);
    DrawBatteryAlert(SHOW_BATTERY_ALERT == 1, runtime.voltage1, TYPE_BATTERY1);
    DrawBattery(vma(LAYOUT_BATTERY2_X, -1), LAYOUT_BATTERY2_Y - (SHOW_VOLTAGE == 2 ? 1 : 0), runtime.voltage2, TYPE_BATTERY2, DISPLAY_MODE_BATTERY2);



    //if (gpsdata.Status >= GPS_ACCURACY && gpsdata.Satellites >= GPS_REQUIRED_SAT) {
    //runtime.osdredra
    //runtime.osdredraw = false;
    //osd.clear();


    //MessageAlert(true, " HOME");






    DrawLabelBox(vma(LAYOUT_SPEED_X - 1, -1), vma(LAYOUT_SPEED_Y - 1, 1), 6, 3, 0x60, GetUnitSpeedSymbol(UNIT_SPEED, true));
    DrawLabelBox(LAYOUT_ALT_X - 1, vma(LAYOUT_ALT_Y - 1, 1), 6, 3, GetUnitSymbol(UNIT_ALTITUDE, true), 0x65);

    DrawBox(vma(LAYOUT_SPEED_X - 1, -1), vma(LAYOUT_SPEED_Y - 1, 1), 6, 3);
    DrawBox(LAYOUT_ALT_X - 1, vma(LAYOUT_ALT_Y - 1, 1), 6, 3);



    if (gpsdata.Heading < (runtime.gpsheading - GPS_HEADING_INTERPOLATE) || gpsdata.Heading > (runtime.gpsheading + GPS_HEADING_INTERPOLATE)) {
    DrawThreeDigitValue(vma(LAYOUT_HEADING_X, -1), LAYOUT_HEADING_Y, gpsdata.Heading, SYMBOL_DEGREE);
    runtime.gpsheading = gpsdata.Heading;
    }

    // draw speed
    DrawFourDigitValue(vma(LAYOUT_SPEED_X, -1), vma(LAYOUT_SPEED_Y, 1), fabs(gpsdata.Groundspeed * UNIT_SPEED), NO_SYMBOL, NO_SYMBOL, FONT_LARGE);

    // calculate and draw altitude
    float alt = gpsdata.Altitude;
    if (GPS_ALTITUDE_TYPE == 0) {
    alt = gpsdata.Altitude - runtime.gpsasl;
    if (alt < 0 && alt > GPS_AGL_NEGATIVE) alt = 0;
    }

    DrawFourDigitValue(LAYOUT_ALT_X, vma(LAYOUT_ALT_Y, 1), fabs(alt * UNIT_ALTITUDE), NO_SYMBOL, NO_SYMBOL, FONT_LARGE);

    // draw vertical indicator
    DrawStatus(LAYOUT_CLIMB_X, vma(LAYOUT_CLIMB_Y, 1), true, runtime.gpsclimb);

    // draw home arrow
    DrawFancyHeading(vma(LAYOUT_HOMEBEARING_X, -1), LAYOUT_HOMEBEARING_Y, runtime.gpshomedirection);

    // draw home distance
    DrawDistance(LAYOUT_HOMEDISTANCE_X, vma(LAYOUT_HOMEDISTANCE_Y, 3), runtime.gpshomedistance, SYMBOL_HOME);

    // draw total flight distance
    DrawDistance(LAYOUT_DISTANCE_X, vma(LAYOUT_DISTANCE_Y, 3), runtime.distance, SYMBOL_FLAG);

    // travel distance
    DrawTimer(vma(LAYOUT_FLYTIME_X, -1), vma(LAYOUT_FLYTIME_Y, 3), runtime.flytime, SHOW_LABELS ? SYMBOL_TIMEFLY : NO_SYMBOL, false);

    DrawCoordinates(vma(LAYOUT_GPSCOORD_X, -1), vma(LAYOUT_GPSCOORD_Y, 3), gpsdata.Latitude, GPS_PRECISION, SHOW_LABELS ? SYMBOL_LAT : NO_SYMBOL);

    DrawCoordinates(vma(LAYOUT_GPSCOORD_X, -1), vma(LAYOUT_GPSCOORD_Y + 1, 3), gpsdata.Longitude, GPS_PRECISION, SHOW_LABELS ? SYMBOL_LON : NO_SYMBOL);

    osd.clear();
  */


}


