#include <M5Stack.h>

int ledPin = 21;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  menu();
  M5.update();
}

int readData = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0) {
    readData = Serial.read();
    Serial.println("");
    switch (readData) {
      case '1' :
      // student1
      Serial.println("Pawat Songkhopanit 6338155521");
      digitalWrite(ledPin, HIGH);
      break;
      case '2' :
      // student2
      Serial.println("Songkhopanit Pawat 1255518336");
      digitalWrite(ledPin, HIGH);
      break;
      case '3' :
      // every student
      Serial.println("Pawat Songkhopanit 6338155521");
      Serial.println("Songkhopanit Pawat 1255518336");
      digitalWrite(ledPin, HIGH);
      break;
      default :
      // wrong input
      digitalWrite(ledPin, LOW);
      break;
     menu();
    }
  }
}

void menu() {
  Serial.println("EXERCISE 5 : MULTI-FUNCTION PROGRAM");
  Serial.println("\n Please enter your function");
  Serial.println(" 1 - First member ");
  Serial.println(" 2 - Second member ");
  Serial.println(" 3 - All member ");
  Serial.println("\n> ");
}
