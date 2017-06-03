void GPS_process() {
  if (gps_parser.encode(Serial.read())) {

    if (gps_parser.satellites.isValid() && gps_parser.satellites.value() > 5) {

      if (gps_parser.location.isValid())  {
        gps_lat = gps_parser.location.lat();
        gps_lng = gps_parser.location.lng();
      }
      if (gps_parser.altitude.isValid()) {
        gps_alt = gps_parser.altitude.meters();
      }
      if (gps_parser.speed.isValid()) {
        gps_speed = gps_parser.speed.kmph() * 1000 / 3600; // m\s
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
