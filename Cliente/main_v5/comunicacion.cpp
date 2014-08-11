
#include <Wire.h> 
#include "comunicacion.h"
#include "sonidos.h"
#include "utilidades.h"



extern int accion;
extern int opcion;
extern char estatus[9];

int casasAntes=0;
int camionesAntes=0;

int prepararJugada( int accion, int destinatario);

/* Inicializa la comunicacion por cable con el Master */
void initComunicacion(){
 Wire.begin(DIRECCION_CLIENTE); 
 Wire.onReceive(recibirStatus); //recibe la situación de inicio de jugada
 Wire.onRequest(mandarJugada); //cuando me lo pide el master le envío mi jugada
}

/* Manda la jugada al Maestro */
void mandarJugada()
{
  int input = prepararJugada(accion,opcion);
  uint8_t buffer[4];
  buffer[0] = input >> 8;
  buffer[1] = input & 0xff;
  Wire.write(buffer, 4);
  Serial.print("Jugada mandada ");
  Serial.print(prepararJugada(accion,opcion));
  Serial.println("");

}

/* Recibe el estado de tus recursos por parte del maestro */  
void recibirStatus (int howMany)
{
    while(Wire.available() > 0)
   {
     char c  = Wire.read();
     if(c=='i')
     {
       estatus[0]=Wire.read();
       estatus[1]=Wire.read();
       estatus[2]=Wire.read();
       estatus[3]=Wire.read();
       estatus[4]=Wire.read();
       estatus[5]=Wire.read();
       estatus[6]=Wire.read();
       estatus[7]=Wire.read();
       estatus[8]=Wire.read();
      }     
  }
  int casasAhora=letraAnumero(estatus[7]);
  int camionesAhora=letraAnumero(estatus[6]);
  
  if(casasAntes<casasAhora)
    sonido_ganar();
  if (camionesAntes>camionesAhora)
    sonido_perder();
    
  #ifdef DEBUG
    Serial.print("casas "); Serial.print(casasAntes);Serial.println(estatus[7]);
    Serial.print("camiones "); Serial.print(camionesAntes);Serial.println(estatus[6]);
  #endif  
 
   
  casasAntes=casasAhora;
  camionesAntes=camionesAhora;
}
  

/* Prepara la jugada a enviar al maestro con el formato de un numero de tres digitos donde:
el primero es la direccion del cliente,
el segundo es la accion a realizar, 
el tercero es la opcion a realizar, o el destinatario de la accion */
int prepararJugada( int accion, int destinatario)   
{                                                 
  return DIRECCION_CLIENTE*100+accion*10+destinatario;
}

