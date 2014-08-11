#ifndef HEADER_DATOS         
  #define HEADER_DATOS
  
  #include "Arduino.h"
  
  #define ACCION_CONEXION 6

  void guardarJugada(int laAccion, int laOpcion);
  int obtenerAccion();
  int obtenerOpcion();
  void guardarStatus(char * estatus);
  char * verStatus();
  
#endif
