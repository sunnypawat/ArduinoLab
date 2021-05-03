#include <M5Stack.h>

const int nC4 =262;
const int nD4 =294;
const int nE4 =330;
const int nF4 =349;
const int nG4 =392;
const int nA4 =440;
const int nB4 =494;
const int nC5 =524;
const int nD5 =587;
const int nE5 =659;
const int nF5 =698;
const int nG5 =784;
const int nA5 =880;
const int nB5 =988;

int readData = 0;

void setup() {
  // put your setup code here, to run once:
 M5.begin();
 Serial.begin(9600);
 Serial.println("EXERCISE 3: Serial piano");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0) {
    readData = Serial.read();
    Serial.write(readData);
    Serial.println("");
    switch (readData) {
      case 'c' : 
      M5.Speaker.tone(nC4); 
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'd' : 
      M5.Speaker.tone(nD4);  
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'e' : 
      M5.Speaker.tone(nE4);
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'f' : 
      M5.Speaker.tone(nF4); 
      delay(1000);
      M5.Speaker.mute();
      delay(50); 
      break;
      case 'g' : 
      M5.Speaker.tone(nG4); 
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'a' : 
      M5.Speaker.tone(nA4);  
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'b' : 
      M5.Speaker.tone(nB4); 
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'C' : 
      M5.Speaker.tone(nC5);  
      delay(250);
      M5.Speaker.mute();
      break;
      case 'D' : 
      M5.Speaker.tone(nD5); 
      delay(1000);
      M5.Speaker.mute();
      delay(50); 
      break;
      case 'E' : 
      M5.Speaker.tone(nE5); 
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'F' : 
      M5.Speaker.tone(nF5);
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'G' :
      M5.Speaker.tone(nG5);
      delay(1000);
      M5.Speaker.mute();
      break;
      case 'A' : 
      M5.Speaker.tone(nA5); 
      delay(1000);
      M5.Speaker.mute(); 
      break;
      case 'B' : 
      M5.Speaker.tone(nB5);  
      delay(1000);
      M5.Speaker.mute();
      break;
      default : 
      M5.Speaker.tone(131); 
      delay(1000);
      M5.Speaker.mute();
      break;
    }
    menu();
    M5.update();
  }
}

void menu() {
  Serial.println("Please enter a key: ");
}
