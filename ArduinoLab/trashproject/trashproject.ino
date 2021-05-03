//#define BLYNK_PRINT Serial
#include <Ultrasonic.h>
#include <M5Stack.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
int distance = 0;
Ultrasonic ultrasonic(16, 17);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8bHnSs4k1F1rwB_stgyBn58kzWxlj1fg";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "sunnypawat";
char pass[] = "sunny100";

BlynkTimer timer;

int thresh[3] = {25, 50, 75};


WidgetLED green(V1);
WidgetLED orange(V2);
WidgetLED red(V3);


void setup()
{
  // Debug console
  M5.begin();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  distance = ultrasonic.distanceRead();
  Serial.println(distance);
  Blynk.run();

  if(distance<thresh[0]){
    green.on();
   }
  else if(distance<thresh[1]){
    green.on();
    orange.on();
  }
  else if(distance<thresh[2]){
    green.on();
    orange.on();
    red.on();
  }
  else{
    green.off();
    orange.off();
    red.off();
  }
  delay(100);
  M5.update();
}
