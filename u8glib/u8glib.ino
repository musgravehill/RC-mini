// Henry's Bench
// Arduino Nokia 5110 U8Glib Tutorial


#include "U8glib.h"
U8GLIB_PCD8544 u8g(5, 6, 8, 7, 9); // CLK=5, DIN=6, CE=8, DC=7, RST=9

#include <SoftwareSerial.h>
SoftwareSerial gpsSerial(3, 4); // RX, TX

#include <TinyGPS++.h>
TinyGPSPlus gps;


void draw() {
  u8g.setFont(u8g_font_profont11);  // select font
  u8g.drawStr(0, 15, "Nokia 5110..");  // put string of display at position X, Y
}

void setup() {
  gpsSerial.begin(57600);
  delay(1000);
}

void loop() {



  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    String dataString = String(gps.location.lat(), 6) + ';' + String(gps.location.lng(), 6) + ';';

    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_profont11);  // select font
      u8g.setPrintPos(0, 0); 
      u8g.print(dataString);
    } while ( u8g.nextPage() );

  }

}
