
#include <Wire.h> 
#include "comunicacion.h"

extern int accion;
extern int opcion;
extern char estatus[9];

int prepararJugada( int accion, int destinatario);

void initComunicacion(){
 Wire.begin(DIRECCION_CLIENTE); 
 Wire.onReceive(recibirStatus); //recibe la situación de inicio de jugada
 Wire.onRequest(mandarJugada); //cuando me lo pide el master le envío mi jugada
}


void mandarJugada()//Manda la jugada al Maestro
{
  int input = prepararJugada(accion,opcion);
//  Serial.print("Jugada Preparada: "); Para saber qué jugada estás mandando
//  Serial.println(input);              ACTIVAR MANDARJUGADA EN LOOP
  uint8_t buffer[4];
  buffer[0] = input >> 8;
  buffer[1] = input & 0xff;
  Wire.write(buffer, 4);
}


void recibirStatus (int howMany)//Recibe el estado de tus recursos para iniciar ronda
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
      }     
  }
}
  

//FUNCION AUXILIAR PREPRARAR JUGADA//

int prepararJugada( int accion, int destinatario)  //junta las órdenes del
{                                                //infrarrojo para mandarlas al maestro
  return DIRECCION_CLIENTE*100+accion*10+destinatario;
}

