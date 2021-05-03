#define BLYNK_PRINT Serial
#include <Ultrasonic.h>

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "2LfujhI5S1ogu0f9RtJldDWVMWWjMRRz";
char ssid[] = "RoyalBS";
char pass[] = "1212312121";

BlynkTimer timer;
int distance = 0;
int bin_height = 0;
int thresh[3] = {25, 50, 75};
Ultrasonic ultrasonic(D6, D7);

WidgetLED green(V1);
WidgetLED orange(V2);
WidgetLED red(V3);

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  bin_height = ultrasonic.distanceRead();
}

BLYNK_WRITE(V5) {
  int pinValue = param.asInt();
  if(pinValue) {
    bin_height = ultrasonic.distanceRead();
  }
}

void loop()
{
  distance = ultrasonic.distanceRead();
  Serial.println(distance);
  delay(100);
  Blynk.run();
  
  if(distance<0.20*bin_height){
    green.on();
    orange.on();
    red.on();
    digitalWrite(D2, HIGH);
    digitalWrite(D1, HIGH);
    digitalWrite(D0, HIGH);
    }
  else if(distance<0.5*bin_height){
    green.on();
    orange.on();
    red.off();
    digitalWrite(D2, HIGH);
    digitalWrite(D1, HIGH);
    digitalWrite(D0, LOW);
  }
  else{
    green.on();
    orange.off();
    red.off();
    digitalWrite(D2, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D0, LOW);
  }
  int display = (1.0 - (double)distance/bin_height) * 100;
  Blynk.virtualWrite(V4,display);
  delay(100);
}
