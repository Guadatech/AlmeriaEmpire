#include <LedControl.h>
#include "matrizLeds.h"
#include "utilidades.h"

int tomate=0;
int nivelTomate=0;
int lechuga=0;
int nivelLechuga=0;
int marmol=0;
int nivelMarmol=0;
int camion=0;
int cortijo=0; 

int led;
int columna;
      
void apagarContador(LedControl lc);
int contador (LedControl lc,int parametro, int unidad);

LedControl  initMatrizLeds(){

  LedControl lc = LedControl(DIN,CLK,CS,NUM_MATRIX);
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,1);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen 
  
  return lc;
}


//void mostrarMatrizLeds(LedControl lc , int estatus)    // FUNCIÓN FINAL QUE CONTROLA LA MATRIZ DE LEDS
//  { 
//   
//  
//      
//      // Ilumino la matriz de leds
//      lc.clearDisplay(0); // Apago la columna 0 = contadorTomate
//      lc.setLed(0,4,estatus,true);
//
//  }
//  
  
// FUNCION AUX. MATRIZ DE LEDS//
void mostrarMatrizLeds(LedControl lc , char *status, int pausa)    // FUNCIÓN FINAL QUE CONTROLA LA MATRIZ DE LEDS
  { 
   
      // Paso los valores que recibo del Master en char a int
      tomate=letraAnumero(status[0]);
      nivelTomate=letraAnumero(status[1]);
      lechuga=letraAnumero(status[2]);
      nivelLechuga=letraAnumero(status[3]);
      marmol=letraAnumero(status[4]);
      nivelMarmol=letraAnumero(status[5]);
      camion=letraAnumero(status[6]);
      cortijo=letraAnumero(status[7]);  
      
      // Ilumino la matriz de leds
      lc.clearDisplay(0); // Apago la columna 0 = contadorTomate
   
      contador(lc,0,tomate);      // Enciendo en la columna 0 el numero de tomates      que tengo pa' los gazpachoh
      contador(lc,1,nivelTomate); // Enciendo en la columna 1 el numero de nivelTomate  que tengo
      contador(lc,2,lechuga);     // Enciendo "   "    "    2 "    "     " lechugas      "    "
      contador(lc,3,nivelLechuga);// Enciendo "   "    "    3 "    "     " nivelLechugas "    "  que me lah quitan de la manoh
      contador(lc,4,marmol);      // Enciendo "   "    "    4 "    "     " marmoles      "    "  duros como ninguno!
      contador(lc,5,nivelMarmol); // Enciendo "   "    "    5 "    "     " nivelMarmoles "    "
      contador(lc,6,camion);      // Enciendo "   "    "    6 "    "     " fragonetas    "    "   pa' robah
      contador(lc,7,cortijo);     // Enciendo "   "    "    7 "    "     " cortijos      "    "   pa' ser el mas riiico, ay papa!
   
      delay(pausa);
      lc.clearDisplay(0); // Apago la columna 0 = contadorTomate

  }
  


int contador (LedControl lc, int parametro, int unidad)  // enciende en el contador (columna) el numero de leds (niveles) de cada contador
  {
    for ( led=0; led<unidad; led++)
     { 
      lc.setLed(0,parametro,led,true);
     } 
  }
  
void encenderTodo(LedControl lc){
  
  for ( led=0; led<8; led++)
    {  
      for ( columna=0; columna<8; columna++)
      {
        lc.setLed(0,columna,led,true);
      }
    }
}

void apagarTodo(LedControl lc){
  
  for ( led=0; led<8; led++)
    {  
      for ( columna=0; columna<8; columna++)
      {
        lc.setLed(0,columna,led,false);
      }
    }
  
}
  

