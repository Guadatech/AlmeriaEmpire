#include "Arduino.h"
#include "IRremote.h"
#include "ir.h"

int leerIR(IRrecv ir);
decode_results results;

IRrecv initIr(){
 
 IRrecv irrecv(PIN_IR); 
 irrecv.enableIRIn();//inicia IR
 
 return irrecv;
}


int leerIR(IRrecv irrecv)
{
    int lectura = 0;
    if (irrecv.decode(&results))
      {
       irrecv.resume(); // Receive the next value
      }

  if(results.value==BOTON_1)
     {
      lectura = 1;
       results.value=0;
     }

  if(results.value==BOTON_2)
     {
       lectura=2;
       results.value=0;
     }

  if(results.value==BOTON_3)
   {
       lectura=3;
       results.value=0;
   }

  if(results.value==BOTON_4)
     {
       lectura=4;
       results.value=0;
     }

  if(results.value==BOTON_5)
     {
       lectura=5;
       results.value=0;
     }

  if(results.value==BOTON_6)
     {
       lectura=6;
       results.value=0;
     }

  return lectura;
}

