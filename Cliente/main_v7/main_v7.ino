#include <IRremote.h>
#include "ir.h"
#include <LedControl.h>
#include "matrizLeds.h"
#include "utilidades.h"
#include <Wire.h> 
#include "comunicacion.h"
#include "sonidos.h"
#include "datos.h"


#define DEBUG 1


boolean juegoEmpezado = false;

// Matriz de Leds
LedControl lc = initMatrizLeds();

void setup()
{
  Serial.begin(9600);
  initIR();
  initComunicacion();
  initSonidos();
  
}

void loop() {
  
  //---
  //---  Periodo de inicio de la partida y de sincronizacion 
  //---  El master ira  mandando  el estatus de inicio "88888888" 
  //---  hasta que los clientes esten listos y le contesten con la orden "66"
  //---
  if (!juegoEmpezado)
     sonido_inicio();
 
  while(!juegoEmpezado && strcmp(verStatus(), "START") != 0){   // Espera aqui hasta que el estatus que mande el master sea 88888888
    guardarJugada(ACCION_CONEXION,ACCION_CONEXION);
    mandarJugada();
    delay(157);
    recibirStatus(9);
    Serial.print(verStatus());
  }
  
  juegoEmpezado = true;
  
  encenderTodo( lc);
  delay(200);
  apagarTodo(lc);
  
  // ---
  // --- Periodo de recepcion de ordenes del master ---
  // ---
  
  
  // De esto se encarga internamente el modulo comunicacion con la funcion "Wire.onReceive(recibirStatus);"
  // que actualiza el array estatus segun los datos mandados por el master
  
  
  // ---
  // --- Periodo de reflexion del jugador donde se muestran los resultados en pantalla (15 seg)  (lo he puesto a 5 para hacerlo mas rapido para las pruebas)---
  // ---
  
  #ifdef DEBUG
       mostrarStatusEnMatrizLeds(lc, 5000);
  #else
       mostrarStatusEnMatrizLeds(lc, 5000);
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
 
  guardarJugada(obtenerAccion(),obtenerOpcion());
  mandarJugada();
  delay(100);
  mostrarStatusEnMatrizLeds(lc,  1000);
  delay(100);
  
}














