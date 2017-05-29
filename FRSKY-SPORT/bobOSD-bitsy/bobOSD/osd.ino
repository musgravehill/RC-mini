/**
   ___  _ __           ____  _______
  / _ )(_) /____ __ __/ __ \/ __/ _ \
  / _  / / __(_-</ // / /_/ /\ \/ // /
  /____/_/\__/___/\_, /\____/___/____/
               /___/

  OSD Functions

**/

/**
    (MessageAlert) Clear/adds an warn message on the screen
*/

void MessageAlert(boolean show, char* msg) {
  CustomMessageAlert(show, msg, LAYOUT_WARN_X, LAYOUT_WARN_Y, true);
}

void CustomMessageAlert(boolean show, char* msg, byte x, byte y, bool symbol) {

  // draw symbol
  osd.setPanel(vma(x, -1), y);
  osd.openPanel();
  if (show && symbol) {
    osd.write(SYMBOL_WARN0);
    osd.write(SYMBOL_WARN1);
  } else {
    osd.write(CHAR_CLEAR);
    osd.write(CHAR_CLEAR);
  }
  osd.closePanel();
  // draw text
  if (show) {
    osd.setPanel(vma(x, -1) - (sizeof msg / 2) - 1, y + (symbol ? 1 : 0));
  } else {
    osd.setPanel(vma(x, -1) - 5, y + (symbol ? 1 : 0));
  }
  osd.openPanel();
  if (show) {
    osd.writeupper(msg);
  } else {
    for (byte i = 0; i < 10; i++) {
      osd.write(CHAR_CLEAR);
    }
  }
  osd.closePanel();
}


/**
    (DrawStatus) Draws or clears a symbol
*/

void DrawStatus(byte x, byte y, boolean b, byte symbol) {
  osd.openSingle(x, y);
  osd.write(b ? symbol : CHAR_CLEAR);
}


/**
    (DrawThreeDigitValue) Draws a three digit value
*/

void DrawThreeDigitValue(byte x, byte y, int v, byte symbol) {
  // verify
  if (v < 0 || v > 999) return;

  // write
  byte fl = FONT_LARGE;
  osd.setPanel(x, y);
  osd.openPanel();
  osd.write(fl + (v / 100));
  osd.write(fl + ((v % 100) / 10));
  osd.write(fl + ((v % 100) % 10));

  // write symbol
  if (symbol != NO_SYMBOL) osd.write(symbol);
  osd.closePanel();
}


/**
    (DrawFourDigitValue)
*/

void DrawFourDigitValue(byte x, byte y, long v, byte bsymbol, byte asymbol, int fl) {
  // verify
  if (v < 0 || v > 9999) return;


  osd.setPanel(x, y);
  osd.openPanel();

  // write symbol
  if (bsymbol != NO_SYMBOL) osd.write(bsymbol);

  // write numbers
  osd.write(fl + (v / 1000));
  osd.write(fl + ((v % 1000) / 100));
  osd.write(fl + (((v % 1000) % 100) / 10));
  osd.write(fl + ((v % 100) % 10));

  // write symbol
  if (asymbol != NO_SYMBOL) osd.write(asymbol);
  osd.closePanel();
}


byte GetUnitSymbol() {
  return 0x66 ; //0x69;
}

byte GetUnitSpeedSymbol(float unit, boolean panel) {
  return panel ? 0x63 : NO_SYMBOL;
}

void DrawDistance(byte x, byte y, float value, byte symbol) {
  DrawFourDigitValue(x, y, fabs(value), symbol, GetUnitSymbol(), FONT_SMALL);
}


/**
    (DrawFancyHeading)
*/

void DrawFancyHeading(byte x, byte y, long d) {
  if (d >= 16 || d < 0) d = 0;
  osd.setPanel(x, y);
  osd.openPanel();
  osd.write(0x50 + d);
  osd.closePanel();
}


/* (DrawOneSmallValue) Draws a one value */
void DrawOneSmallValue(byte x, byte y, int n) {
  int fs = FONT_SMALL;
  osd.setPanel(x, y);
  osd.openPanel();
  osd.write(fs + n);
  osd.closePanel();
}


/* (DrawNumber) Draws a number on the screen with filler etc */
void DrawNumber(byte x, byte y, int v, int d, int mi, int ma, int font) {
  // prepare
  if (v < mi) v = mi; if (v > ma) v = ma;
  // open panel
  osd.setPanel(x, y);
  osd.openPanel();
  // calc
  int l = (int)log10(d);
  for (int i = 0; i < d; i++) {
    int j = pow(10, (d - i - 1));
    d = (int)v / j;
    osd.write(font + d);
    //v = v % jl;
  }
  osd.closePanel();
}

/* (DrawBattery) Draws the Battery Status */
void DrawBattery(byte x, byte y, float voltage, byte type, byte mode) {
  osd.setPanel(x, y);
  osd.openPanel();
  osd.writefloat(voltage, 1);
  osd.closePanel();
}



/**
    (DrawBox) Draws a box with simple elements
*/

void DrawBox(int x, int y, int w, int h) {

  for (int cy = 0; cy < h; cy++) { // top and bottom y
    // draw
    if (cy == 0 || cy == (h - 1)) {
      // draw lines
      for (int cx = 0; cx < w; cx++) {
        osd.writexy(x + cx, y + cy, (cy == 0) ? 0xea : 0xeb);
      }
    } else {
      osd.writexy(x, y + cy, 0xec);
      osd.writexy(x + (w - 1), y + cy, 0xed);
    }
  }

  // draw four corners
  osd.writexy(x, y, 0xfa);
  osd.writexy(x + (w - 1), y, 0xfb);
  osd.writexy(x, y + (h - 1), 0xfc);
  osd.writexy(x + (w - 1), y + (h - 1), 0xfd);
}

/**
    (DrawLabelBox) Draws a box but with labels
*/

void DrawLabelBox(byte x, byte y, byte w, byte h, byte ll, byte lr) {

  DrawBox(x, y, w, h);

  if (ll != NO_SYMBOL) osd.writexy(x, y + 1, ll);
  if (lr != NO_SYMBOL) osd.writexy(x + (w) - 1, y + 1, lr);

}

/**
    (DrawLogo) Draws the FPV Tools Logo
*/
void DrawLogo() {
  osd.setPanel(vma(9, -1), vma(8, 1));
  osd.openPanel();
  for (byte i = 0; i < 13; i++) {
    osd.write(0xb0 + i);
  }
  osd.closePanel();

  osd.setPanel(vma(12, -1), vma(6, 1));
  osd.openPanel();

  for (byte i = 0; i < 7; i++) {
    osd.write(0xc0 + i);
  }
  osd.closePanel();
}


/**
    (DrawCoordinates)
*/

void DrawCoordinates(byte x, byte y, float value, byte prec, byte symbol) {
  osd.setPanel(x, y);
  osd.openPanel();
  if (symbol != NO_SYMBOL) osd.write(symbol);

  float v = value < 0 ? -1 * value : value;

  if (value > 0) osd.write(CHAR_CLEAR);
  if (v < 100) osd.write(CHAR_CLEAR);
  if (v < 10)osd.write(CHAR_CLEAR);

  osd.writefloat(value, prec);
  osd.closePanel();
}

/**
    (vma) adjust based on video mode
*/

int vma(byte v, byte a) {
  return VIDEO_MODE == 0 ? v + a : v;
}


