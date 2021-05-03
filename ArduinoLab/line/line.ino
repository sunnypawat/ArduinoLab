#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>
#include <WiFiClientSecure.h>

#define DHTPIN 5
SimpleDHT11 dht;

String LINE_TOKEN = "RHMAqVBbdNaz5gcKHmcINcS7OhGXROuwMAv5ZrXtpK0";

#include <M5Stack.h>
//#define buttonPin D1 // Define D1 as switch pin
//#define ledPin1 D3 // Define D1 as LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

const char* ssid     = "sunnypawat";   //Wifi Name
const char* password = "sunny100";   //Wifi Password

void setup() {

  M5.begin();
  //pinMode(ledPin1, OUTPUT); // Set pin as output
  //pinMode(buttonPin, INPUT); // set pin as input

  WiFi.begin(ssid, password);
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  M5.update();

}

void loop() {
  //int reading = digitalRead(buttonPin);
  // if the button state has changed:
  // only toggle the LED if the new button state is LOW
    if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed() ) {
      ledState = !ledState;
      float temp, humid;
      int status = dht.read2(DHTPIN, &temp, &humid, NULL);
      String sentToken = "temperature ";
      sentToken += temp;
      sentToken += " humidity ";
      sentToken += humid;
      Line_Notify(LINE_TOKEN, sentToken ); // Call funtion Line_Notify();
      delay(100);
    }
  // digitalWrite(ledPin1, ledState);  // set the LED:
  M5.update();
}

void Line_Notify(String LINE_Token, String message) {

  String msg = String("message=") + message;

  WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Authorization: Bearer " + String(LINE_Token) + "\r\n";
  req += "Content-Length: " + String(msg.length()) + "\r\n";
  req += "\r\n";
  req +=  msg;

  client.print(req);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}
