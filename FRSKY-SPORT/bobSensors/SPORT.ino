void SPORT_telemetry_send() {
  sensor_fcs_main.setData(1, 12.58);
  sensor_fcs_video.setData(1, 4.37);

  //setData(float lat, float lon, float alt, float speed, float cog, uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
  sensor_gps.setData(gps_lat, gps_lng,   // Latitude and longitude in degrees decimal (positive for N/E, negative for S/W)
                     gps_alt ,                 // Altitude in m (can be negative)
                     gps_speed,                 // Speed in m/s
                     gps_course,                 // Course over ground in degrees (0-359, 0 = north)
                     gps_y, gps_m, gps_d,             // Date (year - 2000, month, day)
                     gps_h, gps_i, gps_s);           // Time (hour, minute, second) - will be affected by timezone setings in your radio

  frsky_telemetry.send();
}
