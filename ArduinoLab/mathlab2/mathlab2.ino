#include <ThingSpeak.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <SimpleDHT.h>
#include <M5Stack.h>
#include <Wire.h>

char ssid[] = "sunnypawat";   // your network SSID (name) 
char pass[] = "sunny100";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;


#define DHTPIN 5
SimpleDHT11 dht;

unsigned long myChannelNumber = 1225870;
const char * myWriteAPIKey = "U5K2TL9V3EFJAW71";

String myStatus = "";

void setup() {
  Serial.begin(115200);  //Initialize serial
  M5.begin();
  Wire.begin();

  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(1000);     
    } 
    Serial.println("\nConnected.");
  }

  // set the fields with the values
  float temp, humid;
  int status = dht.read2(DHTPIN, &temp, &humid, NULL);
  if ( status == SimpleDHTErrSuccess) {
     ThingSpeak.setField(1, temp);
     ThingSpeak.setField(2, humid);
  }
 
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
 
  
  delay(1000); // Wait 20 seconds to update the channel again
}
