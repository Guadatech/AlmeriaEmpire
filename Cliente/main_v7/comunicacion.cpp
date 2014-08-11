
#include <Wire.h> 
#include "comunicacion.h"
#include "sonidos.h"
#include "utilidades.h"
#include "datos.h"

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
  int accion = obtenerAccion();
  int opcion = obtenerOpcion();
  int input = prepararJugada(accion,opcion);
  uint8_t buffer[4];
  buffer[0] = input >> 8;
  buffer[1] = input & 0xff;
  Wire.write(buffer, 4);
  #ifdef DEBUG
    Serial.print("Jugada mandada ");
    Serial.print(input);
    Serial.println("");
  #endif

}

/* Recibe el estado de tus recursos por parte del maestro */  
void recibirStatus (int howMany)
{
    static char estatus [9];
    
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
       guardarStatus(estatus);
      }     
  }
  if(casasAntes<letraAnumero(estatus[7]))
    sonido_ganar();
  if (camionesAntes>letraAnumero(estatus[6]))
    sonido_perder();
  
  casasAntes=estatus[7];
  camionesAntes=estatus[6];
}
  

/* Prepara la jugada a enviar al maestro con el formato de un numero de tres digitos donde:
el primero es la direccion del cliente,
el segundo es la accion a realizar, 
el tercero es la opcion a realizar, o el destinatario de la accion */
int prepararJugada( int accion, int destinatario)   
{                                                 
  return DIRECCION_CLIENTE*100+accion*10+destinatario;
}

