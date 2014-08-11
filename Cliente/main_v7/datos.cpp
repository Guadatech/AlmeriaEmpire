#include "datos.h"

char estatus [9] = "11111111"; //estado inicial de la partida 8 dígitos para los leds

int accion = ACCION_CONEXION;
int opcion = ACCION_CONEXION;

void guardarJugada(int laAccion, int laOpcion){
  
  accion = laAccion;
  opcion = laOpcion; 
}

int obtenerAccion(){
  return accion;
}

int obtenerOpcion(){
  return opcion;
}

void guardarStatus(char * elStatus){
  strcpy (estatus , elStatus);
}
char * verStatus(){
  return estatus; 
}
