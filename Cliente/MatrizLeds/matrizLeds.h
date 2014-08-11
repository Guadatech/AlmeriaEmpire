
#ifndef HEADER_MATRIZLEDS              // Truco

  #define HEADER_MATRIXZLEDS
  
  #define NUM_MATRIX 1  //Numero de matrices a utilizar
  #define DIN 12        //Data in pin 12
  #define CLK 11        //Clock pin 11
  #define CS  10        //Chip Select pin 10
  
  void MatrizLeds(LedControl lc , char *status) ;
  LedControl  initMatrizLeds();
  
#endif
