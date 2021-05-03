#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define DHTPIN 5
SimpleDHT11 dht;


// Replace with your SSID and Password
const char* ssid     = "sunnypawat";
const char* password = "sunny100";

// Replace with your unique IFTTT URL resource
const char* resource = "/trigger/bme280_readings/with/key/do2IksGPzWUGTxQ_vod5jS";

// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/bme280_readings/with/key/do2IksGPzWUGTxQ_vod5jS";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Time to sleep
uint64_t uS_TO_S_FACTOR = 1000000;  // Conversion factor for micro seconds to seconds
// sleep for 30 minutes = 1800 seconds
uint64_t TIME_TO_SLEEP = 8;

// Uncomment to use BME280 SPI
/*#include <SPI.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10*/

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

void setup() {
  Serial.begin(9600); 
  M5.begin();
  Wire.begin();
  delay(2000);

  // initialize BME280 sensor
  //bool status;
  //status = bme.begin(0x76);  
  //if (!status) {
    //Serial.println("Could not find a valid BME280 sensor, check wiring!");
    //while (1);
  //}

  initWifi();
  makeIFTTTRequest();
    
  #ifdef ESP32
    // enable timer deep sleep
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);    
    Serial.println("Going to sleep now");
    // start deep sleep for 5 seconds
    esp_deep_sleep_start();
  #else
    // Deep sleep mode for 5 seconds
    Serial.println("Going to sleep now");
    ESP.deepSleep(TIME_TO_SLEEP * uS_TO_S_FACTOR); 
  #endif
}

void loop() {
  // sleeping so wont get here 
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);

  // Temperature in Celsius
  //String jsonObject = String("{\"value1\":\"") + bme.readTemperature() + "\",\"value2\":\"" + (bme.readPressure()/100.0F)
                      //+ "\",\"value3\":\"" + bme.readHumidity() + "\"}";
  float temp, humid;
  int status = dht.read2(DHTPIN, &temp, &humid, NULL);
  String jsonObject = String("{\"value1\":\"") + temp + "\",\"value2\":\"" + 0 + "\",\"value3\":\"" + humid + "\"}";
  // Comment the previous line and uncomment the next line to publish temperature readings in Fahrenheit                    
  /*String jsonObject = String("{\"value1\":\"") + (1.8 * bme.readTemperature() + 32) + "\",\"value2\":\"" 
                      + (bme.readPressure()/100.0F) + "\",\"value3\":\"" + bme.readHumidity() + "\"}";*/
                      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}
