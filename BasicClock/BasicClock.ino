#include <M5Stack.h>
#define TFT_GREY 0x5AEB
#define TFT_BLACK 0x0000
#define TFT_YELLOW 0xFFE0
uint32_t targetTime = 0;
static uint8_t conv2d(const char* p);

uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__+3);
uint8_t ss = conv2d(__TIME__ + 6);

byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);

  targetTime = millis() + 1000;
}

void loop() {
    if (targetTime < millis()) {
      targetTime = millis() + 1000;

    ss++;
    if (ss == 60) {    // Check for roll-over
      ss = 0;          // Reset seconds to zero
      omm = mm;        // Save last minute time for display update
      mm++;            // Advance minute
      if (mm > 59) {   // Check for roll-over
        mm = 0;
        hh++;          // Advance hour
        if (hh > 23) { // Check for 24hr roll-over (could roll-over on13)
          hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
    }


      int xpos = 0;
      int ypos = 85;
      int ysecs = ypos + 24;

      if (omm != mm) {
        omm = mm;
        if (hh < 10) xpos+= M5.Lcd.drawChar('0',xpos,ypos,8);
        xpos += M5.Lcd.drawNumber(hh,xpos,ypos,8);
        xcolon = xpos;
        xpos += M5.Lcd.drawChar(':',xpos,ypos-8,8);
        if (mm < 10) xpos += M5.Lcd.drawChar('0',xpos,ypos,8);
        xpos += M5.Lcd.drawNumber(mm,xpos,ypos,8);
        xsecs = xpos;
      }
      if (oss != ss) {
        oss = ss;
        xpos = xsecs;

        if (ss % 2) { 
        M5.Lcd.setTextColor(0x39C4, TFT_BLACK); 
        M5.Lcd.drawChar(':', xcolon, ypos - 8, 8);     
        xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6);
        M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);    
        } else {
        M5.Lcd.drawChar(':', xcolon, ypos - 8, 8);     
        xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); 
        }
      if (ss < 10) xpos += M5.Lcd.drawChar('0', xpos, ysecs, 6); 
      M5.Lcd.drawNumber(ss, xpos, ysecs, 6);       // Draw seconds
      }
    }
 }

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9') {
    v = *p - '0';
  }
  return 10 * v + *++p - '0';
 }
