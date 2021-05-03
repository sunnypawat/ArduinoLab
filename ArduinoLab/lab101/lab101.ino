#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>


#define DHTPIN 5
SimpleDHT11 dht;
BlynkTimer timer;
int temperature, humidity;
int old_t = -1000;
int old_h = -1000;

char ssid[] = "sunnypawat";
char pass[] = "sunny100";

char auth[] = "FlzPmS8xOx_vhNxyTvDNI_aZkPdKq7JQ";

void sendSensor()
{
  float temp, humid;
  int status =dht.read2(DHTPIN, &temp, &humid, NULL);
  float h = humid;
  float t = temp;

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);

}

void setup() {
  M5.begin();
  Wire.begin();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);

}

void loop() {
  Blynk.run();
  timer.run();
}
