

char *ItoaPadded(int val, char *str, uint8_t bytes, uint8_t decimalpos)  {
  // Val to convert
  // Return String
  // Length
  // Decimal position
  uint8_t neg = 0;
  if (val < 0) {
    neg = 1;
    val = -val;
  }

  str[bytes] = 0;
  for (;;) {
    if (bytes == decimalpos) {
      str[--bytes] = DECIMAL;
      decimalpos = 0;
    }
    str[--bytes] = '0' + (val % 10);
    val = val / 10;
    if (bytes == 0 || (decimalpos == 0 && val == 0))
      break;
  }

  if (neg && bytes > 0)
    str[--bytes] = '-';

  while (bytes != 0)
    str[--bytes] = ' ';
  return str;
}

char *ItoaUnPadded(int val, char *str, uint8_t bytes, uint8_t decimalpos)  {
  // Val to convert
  // Return String
  // Length
  // Decimal position
  uint8_t neg = 0;
  if (val < 0) {
    neg = 1;
    val = -val;
  }

  str[bytes] = 0;
  for (;;) {
    if (bytes == decimalpos) {
      str[--bytes] = DECIMAL;
      decimalpos = 0;
    }
    str[--bytes] = '0' + (val % 10);
    val = val / 10;
    if (bytes == 0 || (decimalpos == 0 && val == 0))
      break;
  }

  if (neg && bytes > 0)
    str[--bytes] = '-';

  while (bytes != 0)
    str[--bytes] = ' ';
  return str;
}

uint8_t FindNull(void)
{
  uint8_t xx;
  for (xx = 0; screenBuffer[xx] != 0; xx++)
    ;
  return xx;
}


uint16_t getPosition(uint16_t pos) {   
  return pos & POS_MASK;     
}

void displayAmperage(void)
{  
  uint16_t amperage = 8;
  ItoaPadded(amperage, screenBuffer, 5, 4);     // 999.9 ampere max!
  screenBuffer[5] = SYM_AMP;
  screenBuffer[6] = 0;
  MAX7456_WriteString(screenBuffer, getPosition(10));
}


void displayWatt(void) {
  uint16_t WhrPosition = 20;
  uint16_t watts = 123;
  ItoaPadded(watts, screenBuffer + 1 , 5, 5);
  screenBuffer[0] = SYM_BLANK;
  screenBuffer[5] = SYM_WATT;
  screenBuffer[6] = 0;
  MAX7456_WriteString(screenBuffer, WhrPosition);
}





