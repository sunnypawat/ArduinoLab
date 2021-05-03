#include <M5Stack.h>

extern unsigned char logo[];
int screen_width = 320;
int screen_height = 240;
int raket1_position, raket2_position;
long interval;
int ball_x;
int ball_y;
int ball_r;
int accel_x;
int accel_y;
//int score;
int scorea, scoreb;
int clear = false;

void start() {
  M5.Lcd.fillScreen(0x0000);
  interval = 60;
  ball_x = 160;
  ball_y = 120;
  ball_r = 6;
  accel_x = 5;
  accel_y = 5;
  //score = 0;
  M5.Lcd.drawBitmap(0, 0, screen_width, screen_height, (uint16_t *)logo);
  M5.Lcd.setTextSize(2);
  long previousMillis = 0;
  long interval = 500;
  int color = 0x0000;
  while(true)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      color = (color == 0x7bef) ? 0xffff : 0x7bef;
      M5.Lcd.setCursor(35, 200);
      M5.Lcd.setTextColor(color);
      M5.Lcd.print("press any key to play");
    }
    M5.update();
    if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) break;
  }
  M5.Lcd.fillScreen(0x0000);
  M5.Speaker.tone(800);
  delay(100);
  M5.Speaker.tone(1200);
  delay(100);
  M5.Speaker.mute();
  delay(500);
  M5.Lcd.fillScreen(0xffff);
}

void game() {
  M5.Lcd.fillCircle(ball_x, ball_y, ball_r, 0x7bef);
  long previousMillis = 0;
  while (true)
  {
    int voltage1 = analogRead(36) * 3400 / 4096;
    int percentage1 = voltage1 * 100 / 3400;
    int voltage2 = analogRead(35) * 3400 / 4096;
    int percentage2 = voltage2 * 100 / 3400;
    raket1_position = map(percentage1, 0, 100, 0, 5);
    raket2_position = map(percentage2, 0, 100, 5, 10);
    int raket_width = 20;
    int raket_height = 40;
    int raket_margin = 10;
    int x, y, color, raket1_x, raket1_y, raket2_x, raket2_y;
    for (int i = 0; i < 10; i++)
    {
      if (i < 5)
      {
        x = 0;
        y = i * (raket_height + raket_margin);
      }
      else
      {
        x = screen_width - raket_width;
        y = (9 - i) * (raket_height + raket_margin);
      }    
      color = (i == raket1_position || i == raket2_position) ? RED : WHITE;
      M5.Lcd.fillRect(x, y, raket_width, raket_height, color);
      if (i == raket1_position)
      {
        raket1_x = x;
        raket1_y = y;
      } else if (i == raket2_position)
      {
        raket2_x = x;
        raket2_y = y;
      }
    }
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      M5.Lcd.fillCircle(ball_x, ball_y, ball_r, WHITE);
      ball_x += accel_x;
      ball_y += accel_y;
      M5.Lcd.fillCircle(ball_x, ball_y, ball_r, 0x7bef);
      if (ball_y <= 0)
        accel_y *= -1;
      if (ball_y >= 240)
        accel_y *= -1;    
    
      if ((ball_x + ball_r >= raket2_x) && (ball_y + ball_r >= raket2_y) && (ball_y + ball_r <= raket2_y + raket_height))
      {
        accel_x *= -1;
        accel_y *= 1;
        repulse();
      }
      if ((ball_x - ball_r <= raket1_x + raket_width) && (ball_y + ball_r >= raket1_y) && (ball_y - ball_r <= raket1_y + raket_height)) 
      {
        accel_x *= -1;
        accel_y *= 1;
        repulse();
      }
       if ((ball_x < 0) || (ball_y < 0) || (ball_y > screen_height))
      {
        //BWIN
        scoreb++;
        gameover();
      }
      if((ball_x > screen_width))
      {
        //AWIN
        scorea++;
        gameover();
      }
      }
  }
}

void repulse() {
  M5.Speaker.tone(1800);
  delay(50);
  M5.Speaker.mute();
  interval -= (interval >= 25) ? 5 : 0;
}

void gameover() {
  M5.Speaker.tone(1200);
  delay(100);
  M5.Speaker.tone(1000);
  delay(100);
  M5.Speaker.tone(800);
  delay(100);
  M5.Speaker.tone(1100);
  delay(100);
  M5.Speaker.mute();
  ball_x=160; 
  ball_r = 6;
  ball_r = 6;
  interval = 60;
  accel_x = 5;
  accel_y = 5;
  ball_y=120;
  M5.Lcd.fillScreen(0xffff);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(120,3);
  M5.Lcd.setTextColor(0x0000);
  M5.Lcd.printf("SCORE: %02d/%02d",scorea,scoreb);
  M5.Lcd.setTextSize(2);
}

void setup(){
  M5.begin();
  pinMode(36, INPUT); // input 1
  pinMode(35, INPUT); // input 2
}

void loop() {
  start();
  game();
}
