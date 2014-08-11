#include "IRremote.h"
#include "ir.h"

IRrecv irrecv(PIN_IR); 

decode_results results;

void initIR(){
  irrecv.enableIRIn(); // Start the receiver
}


int leerIR()
{
  int lectura = 0;
  if (irrecv.decode(&results))
      {
       //Serial.println(results.value);
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


