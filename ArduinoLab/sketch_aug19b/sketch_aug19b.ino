#include <M5Stack.h>

int i = 0;
int j = 1;
int color[] = {
  0xfd79, 0xe8e4, 0xfbe4,
  0xff80, 0x2589, 0x51d,
  0x3a59, 0xa254, 0x7bef,
  0xffff
 };
 
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setBrightness(255);
  M5.Lcd.drawCircle(160,120,100,0xffff);
  M5.Lcd.fillCircleHelper(160,120,100,1,0,0xffff);
  M5.Lcd.fillCircle(110,120,50,0xffff);
  M5.Lcd.fillCircle(210,120,50,0x00);
  M5.Lcd.fillCircle(110,120,10,0x00);
  M5.Lcd.fillCircle(210,120,10,0xffff);
}

void loop() {

}
