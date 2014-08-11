

#include <IRremote.h>
#include "ir.h"
#include <LedControl.h>
#include "matrizLeds.h"
#include "utilidades.h"
#include <Wire.h> 
#include "comunicacion.h"
#include "sonidos.h"


char estatus [9] = "00000000"; //estado inicial de la partida 8 dígitos para los leds

int accion;
int opcion;
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
  
 // if (!juegoEmpezado)
  //   sonido_inicio();
 
  while(!juegoEmpezado && strcmp(estatus, "START") != 0){   // Espera aqui hasta que el estatus que mande el master sea 88888888
 
   
    opcion = 6;
    accion = 6;
    mandarJugada();
    delay(200);
    recibirStatus(9);
    Serial.print(estatus);
  }
  juegoEmpezado = true;
 
   
  //Serial.println(estatus);
  // ---
  // --- Periodo de recepcion de ordenes del master ---
  // ---
  
  
  // De esto se encarga internamente el modulo comunicacion con la funcion "Wire.onReceive(recibirStatus);"
  // que actualiza el array estatus segun los datos mandados por el master
  
  
  // ---
  // --- Periodo de reflexion del jugador donde se muestran los resultados en pantalla (15 seg)  (lo he puesto a 5 para hacerlo mas rapido para las pruebas)---
  // ---
  
  #ifdef DEBUG
       mostrarMatrizLeds(lc, estatus, 5000);
  #else
       mostrarMatrizLeds(lc, estatus, 5000);
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














