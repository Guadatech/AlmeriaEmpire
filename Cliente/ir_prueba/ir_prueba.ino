

#include <IRremote.h>
#include "ir.h"
#include <LedControl.h>
#include "matrizLeds.h"
#include <Wire.h> 
#include "utilidades.h"

#define DEBUG 1

#define LONGITUDestatus 8
char estatus [9] = "87644678"; //estado inicial de la partida 8 dígitos para los leds
char estatusAnterior[]="00000000";

long tiempoActual = 0, tiempoInicial;
const int periodoRecepcionIR = 5000; // tiempo en ms para recibir jugadas del mando IR del jugador
static int recibidoIR;

const int address = 2; //dirección del arduino esclavo

int accion;
int opcion;

// Matriz de Leds
LedControl lc = initMatrizLeds();


void setup()
{
  Serial.begin(9600);
  initIR();
  //Wire.begin(address); 
//  Wire.onReceive(recibirestatus); //recibe la situación de inicio de jugada
//  Wire.onRequest(mandarJugada); //cuando me lo pide el master le envío mi jugada

}

void loop() {
  
  // ---
  // --- Periodo de recepcion de ordenes del master ---
  // ---
  
  
  
  // ---
  // --- Periodo de reflexion del jugador donde se muestran los resultados en pantalla (15 seg) ---
  // ---
  
  mostrarMatrizLeds(lc, estatus, 15000);
  
  // ---
  // --- Periodo de recepcion de jugadas por parte del IR del jugador (5 seg)   ---
  // ---
  
  tiempoActual = millis();  // Obtiene el tiempo actual en milisegundos
  tiempoInicial = tiempoActual;
  
  while (tiempoActual < tiempoInicial + periodoRecepcionIR)
  {
    recibidoIR = comprobarIR();
    
    if (recibidoIR != 0){
      actualizarMatriz(recibidoIR, 1000);
      encenderTodo(lc);
      delay(100);
      apagarTodo(lc);
    }
    tiempoActual = millis();

  }
  
  // ---
  // --- Periodo de envio de la jugada del cliente al master ---
  // ---
  
  mostrarMatrizLeds(lc, estatus, 1000);
  delay(100);
  
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





void actualizarMatriz(int recibido, int pausa)
{
  for (int i=0;i<LONGITUDestatus;i++)
        {
          estatus[i]= numeroAletra(recibido);
        }
}




