#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>
static uint8_t conv2d(const char* p);
uint32_t targetTime = 0;

#define DHTPIN 5
SimpleDHT11 dht;
int temperature, humidity;
int old_t = -1000;
int old_h = 0;
int hha = 0;
int twelve = true;

int celsius = true;
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__+3);
uint8_t ss = conv2d(__TIME__ + 6);
byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;


void setup() {
  M5.begin();
  Wire.begin();
  M5.Lcd.setTextSize(10);
  M5.Lcd.fillScreen(0);
  targetTime = millis() + 1000;
  M5.Lcd.setCursor(0,0);
  M5.Lcd.print(0);
  M5.Lcd.println(" C");
  M5.Lcd.print(0);
  M5.Lcd.println(" %");
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
    M5.Lcd.println(" %");
    if(twelve) {
      if(hh > 12) {
        M5.Lcd.print(hh-12);
      } else {
        M5.Lcd.print(hh);
      }
      M5.Lcd.print(hh-12);
      M5.Lcd.print(":");
      if(mm < 10) {
        M5.Lcd.print("0");
      }
      M5.Lcd.print(mm);
      if(hh >= 12) {
        M5.Lcd.print("PM");
      } else {
        M5.Lcd.print("AM");
      }
    } else {
      M5.Lcd.print(hh);
      M5.Lcd.print(":");
      if(mm < 10) {
        M5.Lcd.print("0");
      }
      M5.Lcd.print(mm);
    }
  } else if (M5.BtnA.wasPressed()) {
    celsius = true;
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(temperature);
    M5.Lcd.println(" C");
    M5.Lcd.print(humidity);
    M5.Lcd.println(" %");
    if(twelve) {
      if(hh > 12) {
        M5.Lcd.print(hh-12);
      } else {
        M5.Lcd.print(hh);
      }
      M5.Lcd.print(hh-12);
      M5.Lcd.print(":");
      if(mm < 10) {
        M5.Lcd.print("0");
      }
      M5.Lcd.print(mm);
      if(hh >= 12) {
        M5.Lcd.print("PM");
      } else {
        M5.Lcd.print("AM");
      }
    } else {
      M5.Lcd.print(hh);
      M5.Lcd.print(":");
      if(mm < 10) {
        M5.Lcd.print("0");
      }
      M5.Lcd.print(mm);
    }
    
  }

  if(M5.BtnB.wasPressed() && twelve) {
    twelve = false;
    hha = 0;
  } else if (M5.BtnB.wasPressed()) {
    twelve = true;
    hha = 1;
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
    M5.Lcd.println(" %");
    if(twelve) {
      if(hh > 12) {
        M5.Lcd.print(hh-12);
      } else {
        M5.Lcd.print(hh);
      }
      M5.Lcd.print(hh-12);
      M5.Lcd.print(":");
      if(mm < 10) {
        M5.Lcd.print("0");
      }
      M5.Lcd.print(mm);
      if(hh >= 12) {
        M5.Lcd.print("PM");
      } else {
        M5.Lcd.print("AM");
      }
    } else {
      M5.Lcd.print(hh);
      M5.Lcd.print(":");
      if(mm < 10) {
        M5.Lcd.print("0");
      }
      M5.Lcd.print(mm);
    }
    
  }
  
  old_t = temperature;
  old_h = humidity;
  
  M5.update();
}

void time() {
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
          hh = hha;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
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
