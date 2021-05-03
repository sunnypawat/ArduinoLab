#include <M5Stack.h>
#define TFT_GREY 0x5AEB
#define TFT_BLACK 0x0000
#define TFT_YELLOW 0xFFE0
uint32_t targetTime = 0;
static uint8_t conv2d(const char* p);

uint8_t hh = 0, mm = 0;
uint8_t ss = 0, ms = 0;

byte omm = 99;
byte oss = 99, oms = 99;
byte xcolon1 = 0,xcolon2 = 0, xsecs = 0;
unsigned int colour = 0;

int start = false;

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  draw();
  targetTime = millis() + 10;
}

void loop() {
  if(M5.BtnA.wasPressed()) {
    start = true;
  }
  if(M5.BtnB.wasPressed()) {
    start = false;
  }
  if(M5.BtnC.wasPressed()) {
    hh = 0;
    mm = 0;
    ss = 0;
    ms = 0;
    draw();
    start = false;// Draw seconds
  }

  time();
  M5.update();
}


void time() {
    if (targetTime < millis() && start) {
      targetTime = millis() + 10;

    ms++;
    if (ms == 100) {    // Check for roll-over
      ms = 0;          // Reset seconds to zero
      oss = ss;        // Save last minute time for display update
      ss++;            // Advance minute
      if (ss > 59) {   // Check for roll-over
        ss = 0;
        mm++;          // Advance hour
        if (mm > 59) { // Check for 24hr roll-over (could roll-over on13)
          mm = 0;
          hh++;
          if (hh > 59) {
            hh = 0;
          }
        }
      }
    } 
      draw();
    }
}   
void draw() {
      int xpos = 0;
      int ypos = 85;
      int ysecs = ypos + 16;

      if (oms != ms) {
        oss = ss;
        if (hh < 10) xpos+= M5.Lcd.drawChar('0',xpos,ypos,7);
        xpos += M5.Lcd.drawNumber(hh,xpos,ypos,7);
        xcolon1 = xpos;
        xpos += M5.Lcd.drawChar(':',xpos,ypos-7,7);
        if (mm < 10) xpos += M5.Lcd.drawChar('0',xpos,ypos,7);
        xpos += M5.Lcd.drawNumber(mm,xpos,ypos,7);
        xcolon2 = xpos;
        xpos += M5.Lcd.drawChar(':',xpos,ypos-7,7);
        if (ss < 10) xpos += M5.Lcd.drawChar('0',xpos,ypos,7);
        xpos += M5.Lcd.drawNumber(ss,xpos,ypos,7);
        xsecs = xpos;
        if (ms < 10) xpos += M5.Lcd.drawChar('0', xsecs, ypos, 7); 
        M5.Lcd.drawNumber(ms, xsecs, ypos, 7); 
      }
}
