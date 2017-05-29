// see max7456registers.h  SET PAL


/*
  #define AMPERAGEPIN   A1
  #define TEMPPIN       A3  // also used for airspeed
  #define RSSIPIN       A3
  #define LEDPIN        7

    # define MAX7456ENABLE    PORTD&=B10111111;
    # define MAX7456DISABLE   PORTD|=B01000000;
    # define MAX7456SETHARDWAREPORTS

    DDRB|=B00101100;
    DDRB&=B11101111;
    DDRD|=B01000000;
    DDRD&=B11111011;

    pinMode(MAX7456RESET,OUTPUT);
    pinMode(MAX7456SELECT,OUTPUT);
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(VSYNC, INPUT);

   # define MAX7456ENABLE    PORTD&=B10111111;  //d6 = SS  PORTD отображается на цифровые выводы Arduino от 0 до 7.
    # define MAX7456DISABLE   PORTD|=B01000000; //d6 = SS  PORTD отображается на цифровые выводы Arduino от 0 до 7.
    # define MAX7456HWRESET   PORTB&=B11111011;delay(100);PORTB|=B00000100;   //d11 ?  PORTB отображается на цифровые выводы Arduino от 8 до 13


*/

void OSD_render() {
  osd.printMax7456Char(0x01, 0, 1);
  osd.print("Hello world :)", 1, 3);
  osd.print("Current Arduino time :", 1, 4);

  osd.printMax7456Char(0xD1, 9, 6, true);
  osd.print("00'00\"", 10, 6);
  byte tab[] = {0xC8, 0xC9};
  osd.printMax7456Chars(tab, 2, 12, 7);
}
