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

int playSpeed = 4;
const int note[] = {nC5,nG4,nG4,nA4,nG4,nG4,nB4,nC5};
const int duration[]= {1,2,2,1,1,1,1,1};


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    speed();
    for(int i=0;i<8;i++) {
    int wait = 4000/duration[i]/playSpeed;
    M5.Speaker.tone(note[i]);
    delay(wait);
    speed();
    M5.Speaker.mute();
    delay(50);
    speed();
  }
}

void speed() {
  if(M5.BtnA.isPressed() && playSpeed > 1) {
    playSpeed /= 2;
  } else if (M5.BtnB.isPressed() && playSpeed < 16) {
    playSpeed *= 2;
  } else if (M5.BtnC.isPressed()) {
    playSpeed = 4;
  }
}
