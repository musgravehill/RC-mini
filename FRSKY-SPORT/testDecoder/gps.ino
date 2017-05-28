// Demonstrate the use of a function to generate the NMEA 8-bit CRC
// - A message is built and placed into a buffer string
// - The checksum is computed, and formatted to two chars
// - The full string is printed both to the IDE monitor and to a hardware UART
// EX1:  $test*   --> 16
// EX2:  $GPRMC,023405.00,A,1827.23072,N,06958.07877,W,1.631,33.83,230613,,,A*  --> 42



// -----------------------------------------------------------------------
void GPS_outputMsg(String GPS_msg) {
  GPS_msg.toCharArray(GPS_CRCbuffer, sizeof(GPS_CRCbuffer)); // put complete string into GPS_CRCbuffer
  int GPS_crc = GPS_convertToCRC(GPS_CRCbuffer);

  Serial.print(GPS_msg);
  if (GPS_crc < 16) Serial.print("0"); // add leading 0
  Serial.println(GPS_crc);
}

// -----------------------------------------------------------------------
byte GPS_convertToCRC(char *buff) {
  // NMEA CRC: XOR each byte with previous for all chars between '$' and '*'
  char c;
  byte i;
  byte start_with = 0;
  byte end_with = 0;
  byte CRC = 0;

  for (i = 0; i < GPS_buff_len; i++) {
    c = buff[i];
    if (c == '$') {
      start_with = i;
    }
    if (c == '*') {
      end_with = i;
    }
  }
  if (end_with > start_with) {
    for (i = start_with + 1; i < end_with; i++) { // XOR every character between '$' and '*'
      CRC = CRC ^ buff[i] ;  // compute CRC
    }
  }
  else { // print locations if error
    Serial.println("CRC ERROR");    
  }
  return CRC;
  //based on code by Elimeléc López - July-19th-2013
}
