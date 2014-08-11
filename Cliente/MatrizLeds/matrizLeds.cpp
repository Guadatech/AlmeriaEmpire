
#include "Arduino.h"
#include "LedControl.h"
#include "matrizLeds.h"

void apagarContador(LedControl lc);
int contador (LedControl lc,int parametro, int unidad);

LedControl  initMatrizLeds(){

  LedControl lc = LedControl(DIN,CLK,CS,NUM_MATRIX);
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,1);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen 
  
  return lc;
}

// FUNCION AUX. MATRIZ DE LEDS//

void MatrizLeds(LedControl lc , char *status)    // FUNCIÓN FINAL QUE CONTROLA LA MATRIZ DE LEDS
  { 
      // Paso los valores que recibo del Master en char a int
      int tomate=(status[0]-'0');
      int nivelTomate=(status[1]-'0');
      int lechuga=(status[2]-'0');
      int nivelLechuga=(status[3]-'0');
      int marmol=(status[4]-'0');
      int nivelMarmol=(status[5]-'0');
      int camion=(status[6]-'0');
      int cortijo=(status[7]-'0');  
      
      // Ilumino la matriz de leds
      apagarContador(lc); // Apago la columna 0 = contadorTomate
      contador(lc,0,tomate);      // Enciendo en la columna 0 el numero de tomates      que tengo pa' los gazpachoh
      contador(lc,1,nivelTomate); // Enciendo en la columna 1 el numero de nivelTomate  que tengo
      contador(lc,2,lechuga);     // Enciendo "   "    "    2 "    "     " lechugas      "    "
      contador(lc,3,nivelLechuga);// Enciendo "   "    "    3 "    "     " nivelLechugas "    "  que me lah quitan de la manoh
      contador(lc,4,marmol);      // Enciendo "   "    "    4 "    "     " marmoles      "    "  duros como ninguno!
      contador(lc,5,nivelMarmol); // Enciendo "   "    "    5 "    "     " nivelMarmoles "    "
      contador(lc,6,camion);      // Enciendo "   "    "    6 "    "     " fragonetas    "    "   pa' robah
      contador(lc,7,cortijo);     // Enciendo "   "    "    7 "    "     " cortijos      "    "   pa' ser el mas riiico, ay papa!
  }
  
void apagarContador(LedControl lc)   // apaga todos los leds del contador
  {
    for (int led=0; led<8; led++)
    {  
      for (int columna=0; columna<8; columna++)
      {
        lc.setLed(0,columna,led,false);
      }
    }
  }

int contador (LedControl lc, int parametro, int unidad)  // enciende en el contador (columna) el numero de leds (niveles) de cada contador
  {
    for (int led=0; led<unidad; led++)
     { 
      lc.setLed(0,parametro,led,true);
     } 
  }
  
