
#include <SPI.h> //for LCD and SD

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 5 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 7 - Data/Command select (D/C)
// pin 8 - LCD chip select (CS)
// pin 9 - LCD reset (RST)
Adafruit_PCD8544 myLCD = Adafruit_PCD8544(5, 6, 7, 8, 9);


/*   SD card datalogger
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
*/
#include <SdFat.h>
#define SD_CS 10
SdFat sd;
SdFile file;

#include <SoftwareSerial.h>
SoftwareSerial gpsSerial(3, 4); // RX, TX

#include <TinyGPS++.h>
TinyGPSPlus gps;

int pin = 2;
unsigned long duration;
bool isStart = false;
unsigned long durationSum = 0L;
byte i = 0;
float depth = 0.0; //metres

void setup()
{
  pinMode(pin, INPUT);

  gpsSerial.begin(57600);

  myLCD.begin();
  myLCD.setContrast(62);
  myLCD.clearDisplay();

  myLCD.setTextSize(1);
  myLCD.setTextColor(BLACK);
  myLCD.setCursor(0, 0);
  myLCD.println("ARDU GPS SONAR v1");
  myLCD.display();
  delay(2000);
  myLCD.clearDisplay();

  sd.begin(SD_CS, SPI_HALF_SPEED);

}

void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    String dataString = String(gps.location.lat()) + ';' + String(gps.location.lng()) + ';' + String(depth);

    file.open("log.txt", O_CREAT | O_WRITE | O_EXCL);
    //file.write(',');
    file.println(dataString);
    file.close();

    myLCD.clearDisplay();
    myLCD.setCursor(0, 0);
    myLCD.println(dataString);
    myLCD.display(); 
    delay(1000);    
  }

  duration = pulseIn(pin, HIGH, 140000); //mks
  if (isStart && duration > 200 &&  duration < 8000) {
    if (i < 10) {
      durationSum += duration;
      i++;
    } else {
      depth = durationSum / 10 / 1257.5;
      durationSum = 0L;
      i = 0;
      isStart = false;
    }
  }
  if (duration > 6500 && duration < 6740) {
    isStart = true;
    durationSum = 0L;
    i = 0;
  }

}

