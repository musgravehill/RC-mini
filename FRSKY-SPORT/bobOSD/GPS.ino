


void GPS_distance_and_bearing() {
  // returns distance in meters between two positions, both specified
  // as signed decimal-degrees latitude and longitude. Uses great-circle
  // distance computation for hypothetical sphere of radius 6372795 meters.
  // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
  // Courtesy of Maarten Lamers
  double delta = radians(GPS_HOME_long - GPS_NOW_long);
  double sdlong = sin(delta);
  double cdlong = cos(delta);
  GPS_HOME_lat_rad = radians(GPS_HOME_lat);
  GPS_NOW_lat_rad = radians(GPS_NOW_lat);
  double sGPS_HOME_lat = sin(GPS_HOME_lat_rad);
  double cGPS_HOME_lat = cos(GPS_HOME_lat_rad);
  double sGPS_NOW_lat = sin(GPS_NOW_lat_rad);
  double cGPS_NOW_lat = cos(GPS_NOW_lat_rad);
  delta = (cGPS_HOME_lat * sGPS_NOW_lat) - (sGPS_HOME_lat * cGPS_NOW_lat * cdlong);
  delta = sq(delta);
  delta += sq(cGPS_NOW_lat * sdlong);
  delta = sqrt(delta);
  double denom = (sGPS_HOME_lat * sGPS_NOW_lat) + (cGPS_HOME_lat * cGPS_NOW_lat * cdlong);
  delta = atan2(delta, denom);
  GPS_HOME_dist = delta * 6372795;

  double dlon = radians(GPS_NOW_long - GPS_HOME_long);
  GPS_HOME_lat_rad = radians(GPS_HOME_lat);
  GPS_NOW_lat_rad = radians(GPS_NOW_lat);
  double a1 = sin(dlon) * cos(GPS_NOW_lat_rad);
  double a2 = sin(GPS_HOME_lat_rad) * cos(GPS_NOW_lat_rad) * cos(dlon);
  a2 = cos(GPS_HOME_lat_rad) * sin(GPS_NOW_lat_rad) - a2;
  a2 = atan2(a1, a2);
  if (a2 < 0.0)
  {
    a2 += TWO_PI;
  }
  GPS_HOME_bearing = degrees(a2);
}

void GPS_test() {
  //по карте точка выше дома, расстояние метров 100-200
  GPS_NOW_lat = 57.695242;
  GPS_NOW_long = 39.767611;
  GPS_distance_and_bearing();

  Serial.println("");
  Serial.print("GPS_HOME_dist=");
  Serial.println(GPS_HOME_dist, DEC);
  Serial.print("GPS_HOME_bearingt=");
  Serial.println(GPS_HOME_bearing, DEC);
}
