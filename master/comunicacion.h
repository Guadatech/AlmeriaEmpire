#ifndef HEADER_COMUNICACION            

  #define HEADER_COMUNICACION

  #include "Arduino.h"

  #define DIR_CLIENTE1 1
  #define DIR_CLIENTE2 2  
  
  void enviarStatus(int address, char status[]);
  int recibeJugada(int direccion);
  char numeroAletra(int num);
  int letraAnumero(char letra);
  void decodificar(int mensaje, int *cliente, int *accion, int *opcion);
 
#endif
