void OSD_render() {
  osd.printMax7456Char(0x01, 0, 1);
  osd.print("Hello world :)", 1, 3);
  osd.print("Current Arduino time :", 1, 4);

  osd.printMax7456Char(0xD1, 9, 6, true);
  osd.print("00'00\"", 10, 6);
  byte tab[] = {0xC8, 0xC9};
  osd.printMax7456Chars(tab, 2, 12, 7);
}
