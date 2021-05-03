#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <SimpleDHT.h>
#include <M5Stack.h>
#include <Wire.h>

String apiKey = "U5K2TL9V3EFJAW71";
const char *ssid = "sunnypawat";
const char *pass = "sunny100";
const char *server = "api.thingspeak.com";
WiFiClient client;

#define DHTPIN 5
SimpleDHT11 dht;

void setup() {
  ThingSpeak.begin(client);
  M5.begin();
  Wire.begin();
  
  Serial.begin(9600);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  float temp, humid;
  int status = dht.read2(DHTPIN, &temp, &humid, NULL);
  if ( status == SimpleDHTErrSuccess) {
    if(client.connect(server,80)) {
      String postStr = apiKey;
      postStr +="&field1=";
      postStr += String(temp);
      postStr += "&field2=";
      postStr += String(humid);
      postStr += "\r\n\r\n";

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
 
      Serial.print("Temperature: ");
      Serial.println(temp);
      Serial.print("Humidity: ");
      Serial.print(humid);
      Serial.println("");
                             
      Serial.println("%. Send to Thingspeak.");
    }
  }
  client.stop();
  Serial.println("Waiting...");
  delay(1000);
  M5.update();
}
