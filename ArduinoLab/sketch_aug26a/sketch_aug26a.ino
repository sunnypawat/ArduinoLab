#include <M5Stack.h>

int ledPin = 21;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("TASK 4 : SERIAL READ TO LED");
  M5.update();
}

int readData = 0;

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available()>0) {
    Serial.println("Please put a number");
    readData = Serial.read();
      if (readData >= 48 && readData <= 59) {
         digitalWrite(ledPin, HIGH);
         delay(1000);
         digitalWrite(ledPin, LOW);
      } else {
        digitalWrite(ledPin, LOW);
      }
  }
  M5.update();
 }
