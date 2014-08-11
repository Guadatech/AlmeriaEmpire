#ifndef HEADER_COMUNICACION         

  #define HEADER_COMUNICACION
  
  #include "Arduino.h"
  
  #define DIRECCION_CLIENTE 2
  
  
  void initComunicacion();
  void mandarJugada();
  void recibirStatus (int howMany);
  
#endif
