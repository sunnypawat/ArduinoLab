#include <M5Stack.h>

int count = 0;

void setup() {
  M5.begin();
  Serial.begin(9600);
  Serial.println("EXERCISE 2 : CLICK WITH SERIAL WRITE");
  M5.update();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (M5.BtnA.wasPressed()) {
    count++;
    Serial.print("Click ");
    Serial.println(count);
  }
    M5.update();
}
