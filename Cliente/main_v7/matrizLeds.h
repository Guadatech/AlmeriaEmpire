#ifndef HEADER_MATRIZLEDS              

  #define HEADER_MATRIXZLEDS
  
  #include "Arduino.h"
   
  
  #define NUM_MATRIX 1  //Numero de matrices a utilizar
  #define DIN 12        //Data in pin 12
  #define CLK 11        //Clock pin 11
  #define CS  10        //Chip Select pin 10
  
  void mostrarStatusEnMatrizLeds(LedControl lc , int pausa) ;
  LedControl  initMatrizLeds();
  void encenderTodo(LedControl lc);
  void apagarTodo(LedControl lc);
  void parpadea(LedControl lc,int veces);
  
#endif

