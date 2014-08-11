#include "IRremote.h"
#include "ir.h"

extern int accion;
extern int opcion;

const int periodoRecepcionIR = 5000; // tiempo en ms para recibir jugadas del mando IR del jugador

IRrecv irrecv(PIN_IR); 

decode_results results;

int leerIR();
int comprobarIR();
int leerOpcion(long tiempoInicial);

void initIR(){
  irrecv.enableIRIn(); // Start the receiver
}


boolean obtenerJugadaIR(){
 
  long tiempoActual = millis();  // Obtiene el tiempo actual en milisegundos
  long tiempoInicial = tiempoActual;
  
  Serial.println("Introducir jugada por IR");
  
  while (tiempoActual < tiempoInicial + periodoRecepcionIR)
  {
   
    if (accion = leerOpcion(tiempoInicial)){
      Serial.println(opcion); 
      return true;       
    }else
      return false;
            
    switch(accion)
    {    
       case 1://construir casas           
            Serial.println("casas a costruir ?");
            if (opcion = leerOpcion(tiempoInicial)){
               Serial.println(opcion); 
               return true;       
            }else
              return false;
            break;
          
       case 2://mejorar los recursos                   
            Serial.println("que recurso quieres mejorar?");
            if (opcion = leerOpcion(tiempoInicial)){
               Serial.println(opcion); 
               return true;       
            }else
              return false;
           break;      
    
       case 3: // crear camiones
            Serial.println("cuantos camiones quieres crear ");
            if (opcion = leerOpcion(tiempoInicial)){
               Serial.println(opcion); 
               return true;       
            }else
              return false;
            break;
           
       case 4://atacar
            Serial.println("a quien atacas?");
            if (opcion = leerOpcion(tiempoInicial)){
               Serial.println(opcion); 
               return true;       
            }else
              return false;
           break;
           
       default:
          break;
    }
    
    tiempoActual = millis();
  }
   
}

int leerOpcion(long tiempoInicial){
 
 long tiempoActual;
 int laopcion=leerIR();
 
 while (opcion==0){ 
   laopcion=leerIR();             
   tiempoActual = millis();
   if(tiempoActual > tiempoInicial + periodoRecepcionIR)
    accion = 0;
    opcion = 0;
    Serial.println("Fin introduccion jugada IR");
    return 0; //No se ha recibido nada         
   } 
  return laopcion;
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


