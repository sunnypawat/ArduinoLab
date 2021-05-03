#include <M5Stack.h>
#define TFT_GREY 0x5AEB
int timeStopper = 0;
uint32_t targetTime = 0; // for next 1 second timeout
static uint8_t conv2d(const char* p);
uint8_t hh = 0, mm = 0;
uint8_t ss = 0, ms = 0; // Get H, M, S from compile time
byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;
void setup() {
Serial.begin(115200);
M5.begin();
// M5.Lcd.setRotation(1);
M5.Lcd.fillScreen(TFT_BLACK);
M5.Lcd.setTextSize(1);
M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
targetTime = millis() + 1000;
}
void drawTime() {
//Update digital time
int xpos = 0;
int ypos = 85; // Top left corner to clock text, about half way down
int ysecs = ypos + 24;
if (omm != mm) { // Redraw hours and minutes time every minute
omm = mm;
// Draw hours and minutes
// Add hours leading zero for 24 hr clock
if (hh < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 8);
xpos += M5.Lcd.drawNumber(hh, xpos, ypos, 8); // Draw hours
xcolon = xpos; // Save colon coord for later to flash on/off later
xpos += M5.Lcd.drawChar(':', xpos, ypos - 8, 8);
// Add minutes leading zero
if (mm < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 8);
xpos += M5.Lcd.drawNumber(mm, xpos, ypos, 8); // Draw minutes
xsecs = xpos; // Save seconds 'x' position for later display updates
}
if (oss != ss) { // Redraw seconds time every second
oss = ss;
xpos = xsecs;
if (ss % 2) { // Flash the colons on/off
// Set colour to grey to dim colon
M5.Lcd.setTextColor(0x39C4, TFT_BLACK);
M5.Lcd.drawChar(':', xcolon, ypos - 8, 8); // Hour:minute colon
xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
// Set colour back to yellow
M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
}
else {
M5.Lcd.drawChar(':', xcolon, ypos - 8, 8); // Hour:minute colon
xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
}
//Draw seconds
// Add leading zero
if (ss < 10) xpos += M5.Lcd.drawChar('0', xpos, ysecs, 6);
M5.Lcd.drawNumber(ss, xpos, ysecs, 6); // Draw seconds
}
}

void time(){
if (targetTime < millis()) {
// Set next update for 1 second later
targetTime = millis() + 10;
// Adjust the time values by adding 1 second
ss++; // Advance second
if (ss == 99) { // Check for roll-over
ss = 0; // Reset seconds to zero
omm = mm; // Save last minute time for display update
mm++; // Advance minute
if (mm > 59) { // Check for roll-over
mm = 0;
hh++; // Advance hour
if (hh > 59) { // Check for 24hr roll-over (could roll-over on13)
hh = 0; // 0 for 24 hour clock, set to 1 for 12 hour clock
}
}
}
}
}
void loop() {
if(M5.BtnA.wasPressed()){
timeStopper = 0;
}
if(M5.BtnB.wasPressed()){
timeStopper = 1;
}
if (M5.BtnC.wasPressed()){
hh = 0; ss = 0; mm = 0;
}

if(timeStopper == 0){
time();
}
else {

}
drawTime();
M5.update();
}
