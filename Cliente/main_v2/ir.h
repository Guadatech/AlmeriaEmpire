#ifndef HEADER_IR             // Truco

  #define HEADER_IR
  
  #include "Arduino.h"
  
  #define PIN_IR 2  //Pin a utilizar por el receptor IR
  #define BOTON_1 16582903
  #define BOTON_2 16615543
  #define BOTON_3 16599223
  #define BOTON_4 16591063
  #define BOTON_5 16623703
  #define BOTON_6 16607383
  
  void initIR();
  boolean obtenerJugadaIR();
  
#endif
