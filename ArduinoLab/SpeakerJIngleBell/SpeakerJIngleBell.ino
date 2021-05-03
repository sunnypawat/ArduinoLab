#include <M5Stack.h>

#define B1 262
#define Cd1 277
#define D1 294
#define Dd1 311
#define E1 330
#define F1 349
#define Fd1 370
#define G1 392
#define Gd1 415
#define A1 440
#define Ad1 446
#define H1 494

int music[] =
{ E1,E1,E1,
  E1,E1,E1,
  E1,G1,Cd1,D1,E1,
  F1,F1,F1,F1,
  F1,E1,E1,
  E1,D1,D1,E1,D1,
  G1
};
int t=0;  
void setup() {
  // put your setup code here, to run once:
  M5.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(M5.BtnA.wasPressed()) {
    if(t==(sizeof(music)/sizeof(int))-1) {
      t=0;
    }
    M5.Speaker.tone(music[t]);
  }
  if(M5.BtnA.wasReleased()) {
    M5.Speaker.mute();
    t++;
  }
  M5.update();
}
