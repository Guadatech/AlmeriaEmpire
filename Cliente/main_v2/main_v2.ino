

#include <IRremote.h>
#include "ir.h"
#include <LedControl.h>
#include "matrizLeds.h"
#include "utilidades.h"
#include <Wire.h> 
#include "comunicacion.h"

#define DEBUG 1

char estatus [9] = "87644678"; //estado inicial de la partida 8 dígitos para los leds

int accion;
int opcion;

// Matriz de Leds
LedControl lc = initMatrizLeds();

void setup()
{
  Serial.begin(9600);
  initIR();
  initComunicacion();
  
}

void loop() {
  
  // ---
  // --- Periodo de recepcion de ordenes del master ---
  // ---
  
  
  // De esto se encarga internamente el modulo comunicacion con la funcion "Wire.onReceive(recibirStatus);"
  
  
  // ---
  // --- Periodo de reflexion del jugador donde se muestran los resultados en pantalla (15 seg)  (lo he puesto a 5 para hacerlo mas rapido para las pruebas)---
  // ---
  
  #ifdef DEBUG
       mostrarMatrizLeds(lc, estatus, 5000);
  #else
       mostrarMatrizLeds(lc, estatus, 15000);
  #endif
 
  
  // ---
  // --- Periodo de recepcion de jugadas por parte del IR del jugador (5 seg)   ---
  // ---
  
  if(obtenerJugadaIR()){
     // La matriz parpadea para mostrar que ha recibido la orden
      encenderTodo(lc);
      delay(100);
      apagarTodo(lc); 
  }
    
    
  // ---
  // --- Periodo de envio de la jugada del cliente al master ---
  // ---
 
  mandarJugada();
  delay(100);
  mostrarMatrizLeds(lc, estatus, 1000);
  delay(100);
  
}












