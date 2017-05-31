
#define POS_MASK        0x01FF
#define PAL_MASK        0x0003
#define PAL_SHFT             9
#define DISPLAY_MASK    0xC000
#define DISPLAY_ALWAYS  0xC000
#define DISPLAY_NEVER   0x0000
#define DISPLAY_COND    0x4000
#define DISPLAY_MIN_OFF     0x8000

#define POS(pos, pal_off, disp)  (((pos)&POS_MASK)|((pal_off)<<PAL_SHFT)|(disp))
#if defined SHIFTDOWN
#define TOPSHIFT        LINE
#else
#define TOPSHIFT        0
#endif

#define MPH 1
#define KMH 0
#define METRIC 0
#define IMPERIAL 1

#define lo_speed_cycle  100
#define sync_speed_cycle  33

#define CALIBRATION_DELAY 10       // Calibration timeouts   
#define EEPROM_WRITE_DELAY 5       // Calibration timeouts



#define LINE      30
#define LINE01    0
#define LINE02    30
#define LINE03    60
#define LINE04    90
#define LINE05    120
#define LINE06    150
#define LINE07    180
#define LINE08    210
#define LINE09    240
#define LINE10    270
#define LINE11    300
#define LINE12    330
#define LINE13    360
#define LINE14    390
#define LINE15    420
#define LINE16    450



//General use variables
struct  __timer {
  uint8_t  tenthSec;
  uint8_t  halfSec;
  uint8_t  Blink2hz;                          // This is turing on and off at 2hz
  uint8_t  Blink10hz;                         // This is turing on and off at 10hz
  uint16_t lastCallSign;                      // Callsign_timer
  uint8_t  rssiTimer;
//  uint8_t accCalibrationTimer;
  uint8_t  magCalibrationTimer;
  uint32_t fwAltitudeTimer;
  uint32_t seconds;
  uint8_t  MSP_active;
  uint8_t  GPS_active;
  uint8_t  GUI_active;
  uint8_t  GPS_initdelay;
  uint16_t  loopcount;
  uint16_t  packetcount;
  uint16_t  serialrxrate;
  uint32_t alarms;                            // Alarm length timer
}
timer;

struct __flags {
  uint8_t ident;
  uint8_t box;
  uint8_t reset;
  uint8_t signaltype;
}
flags;

struct __cfg {
    uint8_t  fw_althold_dir;
    uint16_t fw_gps_maxcorr;                    // Degrees banking Allowed by GPS.
    int16_t  fw_gps_rudder;                     // Maximum input of Rudder Allowed by GPS.
    int16_t  fw_gps_maxclimb;                   // Degrees climbing . To much can stall the plane.
    int16_t  fw_gps_maxdive;                    // Degrees Diving . To much can overspeed the plane.
    uint16_t fw_climb_throttle;                 // Max allowed throttle in GPS modes.
    uint16_t fw_cruise_throttle;                // Throttle to set for cruisespeed.
    uint16_t fw_idle_throttle;                  // Lowest throttleValue during Descend
    uint16_t fw_scaler_throttle;                // Adjust to Match Power/Weight ratio of your model
    uint8_t  fw_roll_comp;                      // Adds Elevator Based on Roll Angle
    uint8_t  fw_rth_alt;                        // Min Altitude to keep during RTH. (Max 200m)
}
cfg;

struct __cfgpa {
  uint16_t rollPitchItermIgnoreRate;
  uint16_t yawItermIgnoreRate;
  uint16_t yaw_p_limit;
  uint8_t  t0;
  uint8_t  vbatPidCompensation;
  uint8_t  ptermSRateWeight;
  uint8_t  dtermSetpointWeight;
  uint8_t  t1;
  uint8_t  t2;
  uint8_t  itermThrottleGain;
  uint16_t rateAccelLimit;
  uint16_t yawRateAccelLimit;
}
cfgpa;




uint16_t debug[4];   // int32_t ?...
int8_t menudir;
unsigned int allSec=0;
unsigned int menuSec=0;
uint8_t armedtimer=30;
uint16_t debugerror;
uint16_t debugval=0;
uint16_t cell_data[6]={0,0,0,0,0,0};
uint16_t cycleTime;
uint16_t I2CError;
uint8_t oldROW=0;
uint8_t cells=0;
uint8_t rcswitch_ch=8;
int8_t PulseType = 0; //0 PWM 1 PPM
uint16_t pwmval1=0;
uint16_t pwmval2=0;
uint8_t debugtext=0;
uint8_t MSP_home_set=0;
#if defined CORRECT_MSP_BF1
  uint8_t bfconfig[25];
#endif


// Config status and cursor location
uint8_t screenlayout=0;
uint8_t oldscreenlayout=0;
uint8_t ROW=10;
uint8_t COL=3;
int8_t configPage=1;
int8_t previousconfigPage=1;
uint8_t configMode=0;
uint8_t fontMode = 0;
uint8_t fontData[54];
uint8_t nextCharToRequest;
uint8_t lastCharToRequest;
uint8_t retransmitQueue;

uint16_t eeaddress = 0;
uint8_t eedata = 0;
uint8_t settingsMode=0;
uint32_t MSP_OSD_timer=0;
uint16_t framerate = 0;
uint16_t packetrate = 0;
uint16_t serialrxrate = 0;




 
 



const char signaltext0[]  PROGMEM = "NTSC";
const char signaltext1[]  PROGMEM = "PAL";





