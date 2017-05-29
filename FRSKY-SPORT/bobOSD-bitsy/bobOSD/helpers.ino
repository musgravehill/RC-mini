/**
  * (Helpers)
  */

void unplugSlaves() {
    //Unplug list of SPI
    digitalWrite(MAX7456_SELECT, HIGH); // unplug OSD
}
