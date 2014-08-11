#include "IRremote.h"
#include "ir.h"

extern int accion;
extern int opcion;

const int periodoRecepcionIR = 5000; // tiempo en ms para recibir jugadas del mando IR del jugador

IRrecv irrecv(PIN_IR); 

decode_results results;

int leerIR();
int comprobarIR();

void initIR(){
  irrecv.enableIRIn(); // Start the receiver
}


boolean obtenerJugadaIR(){
 
  long tiempoActual = millis();  // Obtiene el tiempo actual en milisegundos
  long tiempoInicial = tiempoActual;
  
  while (tiempoActual < tiempoInicial + periodoRecepcionIR)
  {
    int recibidoIR = comprobarIR();
    
    if (recibidoIR != 0){
      opcion = recibidoIR;
      accion = recibidoIR;
      return true;  
    }
    tiempoActual = millis();
  }
  return false; //No se ha recibido nada
}

int comprobarIR()
{
  int recibidoIR = leerIR();
  if (recibidoIR != 0){
    #ifdef DEBUG
      Serial.println(recibidoIR);
      Serial.println(estatus);
    #endif
  }
  return recibidoIR;
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


