
/*
*  I2C_Master
*  Send Serial data to the slave
*/

#include <Wire.h> 

void decodificar(int mensaje, int *cliente, int *accion, int *opcion)
{
  *cliente=(int) mensaje/100;
  *accion=(int) (mensaje-(*cliente*100))/10;
  *opcion=(int) (mensaje-(*cliente*100))-(*accion*10);
  
}


void setup()
{
    Serial.begin(9600);
    Wire.begin(); 
}


void loop()
{
  

  
  int receivedValue1 = recibeJugada(1);
  Serial.println(receivedValue1);
  
  int receivedValue2 = recibeJugada(2);
  Serial.println(receivedValue2);
  
  delay(3000);
  
  enviarStatus(1, "44444444"); // enviar estado de sus recursos al inicio de la jugada al jugador 4 
  enviarStatus(2, "22222222");//    "         "        "        "      "      "      "      3 
  int a=0;
  int b=0;
  int c=0;
  decodificar(123, &a, &b , &c);
  Serial.println("resultado");
  Serial.println(a);Serial.println(b);Serial.println(c);
}

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
/*El Master manda al esclavo con direccion "direccion"  la peticion la peticion de la 
  jugada que va a realizar y retorna el codigo de jugada enviada por el esclavo
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


int letraAnumero(char letra)
{
   return letra - '0'; 
}

