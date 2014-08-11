
/*
*  I2C_Master
*  Send Serial data to the slave
*/

#include "comunicacion.h"
#include <Wire.h>


void enviarStatus(int address, char status[])
/* Envia el status del jugador de direccion address a ese jugador 
  El estatus sera un codigo de 8 digitos
  El primero sera el numero de tomates 
  El segundo el nivel de los tomates
  El tercero el numero de lechugas
  El cuarto el nivel de lechugas
  el quito el numero de marmol
  el sexto el nivel de marmol
  el septimo el numero de camiones
  y el octavo el numero de casas*/
{
  Wire.beginTransmission(address); 
  Wire.write('i');
  delay(10);
  Wire.write(status[0]);
  delay(10);
  Wire.write(status[1]);
  delay(10);
  Wire.write(status[2]);
  delay(10);
  Wire.write(status[3]);
  delay(10);
  Wire.write(status[4]);
  delay(10);
  Wire.write(status[5]);
  delay(10);
  Wire.write(status[6]);
  delay(10);
  Wire.write(status[7]);
  delay(10);
  Wire.endTransmission();
 
}


int recibeJugada(int direccion)
/* El Master manda al esclavo con direccion "direccion"  la peticion de la 
  jugada que va a realizar y retorna el codigo de jugada enviada 
  los codigos de jugada son numeros de tres digitos, 
  el primero es la direccion del jugador
  el segundo es la accion a realizar
  y el tercero es el destinatario */
{
  int receivedValue;
  // Request data from slave.
  Wire.beginTransmission(direccion);
  
  // Envia al cliente de direccion 4 la peticion y se queda a la espera de 
  // recibir un byte
  int available = Wire.requestFrom(direccion, 4); 
 
   if(available == 4)
    {
      receivedValue = Wire.read() << 8 | Wire.read();
    }
    else
    {
      Serial.print("Unexpected number of bytes received: ");
      Serial.println(available);
    }
    Wire.endTransmission();
    return receivedValue;
   
}

char numeroAletra(int num)
{

  char b[2];

  String str;

  str=String(num);

  str.toCharArray(b,2);
  
  return str.charAt(0);
}

void decodificar(int mensaje, int *cliente, int *accion, int *opcion)
{
  *cliente=(int) mensaje/100;
  *accion=(int) (mensaje-(*cliente*100))/10;
  *opcion=(int) (mensaje-(*cliente*100))-(*accion*10);
  
}

int letraAnumero(char letra)
{
   return letra - '0'; 
}


