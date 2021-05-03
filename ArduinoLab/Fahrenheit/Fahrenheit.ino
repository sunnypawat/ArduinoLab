#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>

#define DHTPIN 5
SimpleDHT11 dht;
int temperature, humidity;
int old_t = -1000;
int old_h = 0;

int celsius = true;

void setup() {
  M5.begin();
  Wire.begin();
  M5.Lcd.setTextSize(10);
  M5.Lcd.fillScreen(0);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.print(0);
  M5.Lcd.println(" C");
  M5.Lcd.print(0);
  M5.Lcd.print(" %");
}

void loop() {
  float temp, humid;
  int status = dht.read2(DHTPIN, &temp, &humid, NULL);

  if (status == SimpleDHTErrSuccess) {
    temperature = temp;
    humidity = humid;
  }

  if(M5.BtnA.wasPressed() && celsius) {
    celsius = false;
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print((9/5*temperature)+32);
    M5.Lcd.println(" F");
    M5.Lcd.print(humidity);
    M5.Lcd.print(" %");
  } else if (M5.BtnA.wasPressed()) {
    celsius = true;
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(temperature);
    M5.Lcd.println(" C");
    M5.Lcd.print(humidity);
    M5.Lcd.print(" %");
  }

   if (temperature != old_t || humidity != old_h) {
    if (temp > 27) {
      M5.Lcd.setTextColor(0xe8e4);
    } else {
      M5.Lcd.setTextColor(0x2589);
    }
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    
    if(celsius == true) {
      M5.Lcd.print(temperature);
      M5.Lcd.println(" C");
    } else {
      M5.Lcd.print((9/5*temperature)+32);
      M5.Lcd.println(" F");
    }
    
    M5.Lcd.print(humidity);
    M5.Lcd.print(" %");
  }
  old_t = temperature;
  old_h = humidity;
  M5.update();

  
}
