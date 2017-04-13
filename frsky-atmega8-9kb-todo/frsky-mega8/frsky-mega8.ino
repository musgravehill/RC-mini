#include <SoftwareSerial.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h> 


#define FRS_TX_PIN        A2            // not used
#define FRS_RX_PIN        A3            // telemetry data
#define FRAME_SIZE        12            // max 12 bytes
#define FRAME_RVLQ      0xFE            // second byte 0xFE - Remote Voltage and Link Quality
#define FRAME_USER      0xFD            // second byte 0xFD - User Data

 
SoftwareSerial FrSky = SoftwareSerial(FRS_TX_PIN, FRS_RX_PIN, true);  // orig false
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins! 
 
byte next = 0;
byte buff[FRAME_SIZE];                  // frame array
byte index  = 0;                        // index in frame array
byte link   = 0;                        // link established, data received
byte frame  = 0;                        // frame received indicator
byte stuff  = 0;                        // byte stuffing indicator

 
void setup() {
  FrSky.begin(9600);  
  
  display.begin();  
  display.setContrast(50); 
  display.clearDisplay();
  display.setRotation(1);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Rotation");
 
  frame = 0;
  index = 0;
  link  = 0;
  stuff = 0;  
}
 
void loop() {
  if (FrSky.available()) {              // reading input data
    next = (byte)FrSky.read();
    if (next != 0x7E)
      if (next == 0x7D)                 // byte stuffing indicator
        stuff = 1;                      // set the flag and discard byte
      else if (stuff == 0)
        buff[index++] = next;         // normal byte
      else {
        buff[index++] = next | 0x20;  // byte stuffing set, change next byte
        stuff = 0;                    // and reset the flag
      }
    else {
      if (index == 10 || index == 11) { // end byte
        buff[index] = next;
        frame = 1;
        index = 0;
      } else {                          // start byte?
        index = 0;
        buff[index++] = next;
      }
    }
    if (index >= FRAME_SIZE)
      index = FRAME_SIZE - 1;           // prevent buffer overflow
  }
 
  if (buff[1] == FRAME_RVLQ && frame == 1) {  // second byte 0xFE - Remote Voltage and Link Quality
    //V1[nvals] =  buff[2] * 4 * 330.0 / 255;          // V1 - Voltage, up to 13.2V, Internal divider 1:4
   // V2[nvals] =  buff[3] * (22 + 100) / 22 * 330.0 / 255;          // V2 - Voltage, up to 18.3V
    //Rx[nvals] =  buff[4];                            // Up Link Quality RSSI   (min 36, max 116-121)
    //Tx[nvals] =  buff[5] / 2;                        // Down Link Quality RSSI (min 36, max 116-121)
    
    frame = 0;
    link = 1;    // valid data received
    //countReceived++;
    
  }
 
 // timeMachine 
 //displau /countReceived++; THEN countReceived=0;
  if (link == 1) {
     
   // lcd.setCursor(0, 0);
    
  //  lcd.print("V  "); 
 //   lcd.setCursor(7, 0);
  //  lcd.print("RX="); 
    
   // lcd.print("dBc ");
   // lcd.setCursor(0, 1);
    
   // lcd.print("V  "); 
   // lcd.setCursor(7, 1);
   // lcd.print("TX="); 
    
  //  lcd.print("dBc "); 
    
  }
}
 
