#include "SevSeg.h"

#define CUENTA_ATRAS 2000
SevSeg sevseg;

unsigned long timer;
int CentSec=CUENTA_ATRAS;
int turno=0;

void setup() {
  sevseg.Begin(1,2,3,4,5,6,7,8,9,10,11,12,13);
  sevseg.Brightness(90);
  timer=millis();
}

void loop() {
  if (cuenta_atras())
  {
    turno++;
  }
}

boolean cuenta_atras(){
  int numDisplay=0;turno*100;
  
  CentSec=CUENTA_ATRAS;
  while (true){
    sevseg.PrintOutput();
    unsigned long mils=millis();
  
    if (mils-timer>=10) {
      timer=mils;
      CentSec--;
      if (CentSec<=0) { 
        //CentSec=CUENTA_ATRAS;
        return true;
      }
      //si quieres contabilizar ronda y segundos en el mismo display
      //numDisplay=(turno*100)+(int)(CentSec/100);
      //sevseg.NewNum(numDisplay,(byte) 2);
      sevseg.NewNum(CentSec,(byte) 2);
    }
  }
}







