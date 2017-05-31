


//------------------------------------------------------------------------
#define MEMCHECK   // to enable memory checking.
#if 1
__asm volatile ("nop");
#endif
#ifdef MEMCHECK
extern uint8_t _end;  //end of program variables
extern uint8_t __stack; //start of stack (highest RAM address)

void PaintStack(void) __attribute__ ((naked)) __attribute__ ((section (".init1")));    //Make sure this is executed at the first time

void PaintStack(void)
{
  //using asm since compiller could not be trusted here
  __asm volatile ("    ldi r30,lo8(_end)\n"
                  "    ldi r31,hi8(_end)\n"
                  "    ldi r24,lo8(0xa5)\n" /* Paint color = 0xa5 */
                  "    ldi r25,hi8(__stack)\n"
                  "    rjmp .cmp\n"
                  ".loop:\n"
                  "    st Z+,r24\n"
                  ".cmp:\n"
                  "    cpi r30,lo8(__stack)\n"
                  "    cpc r31,r25\n"
                  "    brlo .loop\n"
                  "    breq .loop"::);
}

uint16_t UntouchedStack(void)
{
  const uint8_t *ptr = &_end;
  uint16_t       count = 0;

  while (*ptr == 0xa5 && ptr <= &__stack)
  {
    ptr++; count++;
  }

  return count;
}
#endif

// Frequently used expressions
#define PGMSTR(p) (char *)pgm_read_word(p)

//------------------------------------------------------------------------
#include <avr/pgmspace.h>
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))
#include <EEPROM.h>
#include <util/atomic.h> // For ATOMIC_BLOCK
#include "Config.h"
#include "Def.h"
#include "symbols.h"
#include "GlobalVariables.h"
#include "math.h"

char screen[480];          // Main screen ram for MAX7456
char screenBuffer[20];
unsigned long previous_millis_low = 0;
unsigned long previous_millis_high = 0;
unsigned long previous_millis_sync = 0;
unsigned long previous_millis_rssi = 0;


void setup() {
  MAX7456SETHARDWAREPORTS
  delay(1000);
  MAX7456Setup();
}


void loop() {
  MAX7456_DrawScreen();
  //MAX7456_ClearScreen();

}  // End of main loop












