#ifndef HEADER_SONIDOS            // Truco

  #define HEADER_SONIDOS
  
  #include "Arduino.h"
  
  #define PIN_SONIDOS 3  //Pin a utilizar por el receptor IR
  
  void sonido_perder();
  void sonido_ganar();
  void sonido_inicio();
  void initSonidos();
#endif
