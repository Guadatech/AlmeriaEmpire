/*
*  I2C_Slave
*  Enviar datos al maestro
*  Recibir datos desde el maestro
*/

#include <Wire.h> //cargamos la librería Wire para conectar los arduinos
char status [9] = "00000000"; //estado inicial de la partida 8 dígitos para los leds
const int address = 2; //dirección del arduino esclavo   


//MATRIZ DE LED//

// DEFINO los pines de entrada para la pantalla de Leds
#include "LedControl.h" //  cargamos la librería del LED
#define LONGITUDSTATUS 8
LedControl lc=LedControl(12,11,10,1);
// VCC -> 5 V
// GND -> GND
// DIN -> pin 12
// CLK -> pin 11
// CS  -> pin 10
// NO he usado: 1 as we are only using 1 MAX7219
char statusAnterior[]="00000000";


//INFRARROJOS//
#include <IRremote.h>
decode_results results;
int ir = 2; //PIN donde va conectado el IR
IRrecv irrecv(ir);

int accion;
int opcion;

int leerIR()
{
    int lectura = 0;
    if (irrecv.decode(&results))
      {
       irrecv.resume(); // Receive the next value
      }

  if(results.value==16582903)
     {
      lectura = 1;
       results.value=0;
     }

  if(results.value==16615543)
     {
       lectura=2;
       results.value=0;
     }

  if(results.value==16599223)
   {
       lectura=3;
       results.value=0;
   }

  if(results.value==16591063)
     {
       lectura=4;
       results.value=0;
     }

  if(results.value==16623703)
     {
       lectura=5;
       results.value=0;
     }

  if(results.value==16607383)
     {
       lectura=6;
       results.value=0;
     }

  return lectura;
}


// -------------------------- SETUP -----------------------------
void setup()
{
  Wire.begin(address); 
  Wire.onReceive(recibirStatus); //recibe la situación de inicio de jugada
  Wire.onRequest(mandarJugada); //cuando me lo pide el master le envío mi jugada
  Serial.begin(9600);
  
//MATRIZ DE LEDS//

// the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,1);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  
/////////IR////////
  irrecv.enableIRIn();//inicia IR
}



// ---------------------------- LOOP --------------------------------
void loop()
{ 
  String SstatusAnterior = statusAnterior;//Pasamos las cadenas a String 
  String Sstatus = status;                //para poder compararlas mas facilmente
  
  if (Sstatus.compareTo(SstatusAnterior)!=0) // Solo cambia la matriz de leds cuando
                                        // el Master mande un "status" distinto al anterior
    {   
       Serial.println(status);
       MatrizLeds();    // Llamar a la función de apagar y encender leds
       
      for (int i=0;i<LONGITUDSTATUS;i++)
        {
          statusAnterior[i]=status[i];
        }
    }
  acciones();
//  mandarJugada(); delay(1000); para saber si manda jugada sin MAESTRO
                               //ACTIVAR PRINT EN LA FUNCION MANDARJUGADA
}


//--------------------------FUNCIONES DE ACCIONES IR-----------------------------

void acciones()// que accion ha elegido el cliente
{    
  accion=leerIR();
  while (accion==0)// espero a que el jugador introduzca su accion
  {
    accion=leerIR();
   }
          
  switch(accion)
  {    
      case 1://construir casas           
          Serial.println("casas a costruir ?");
          opcion=leerIR();
          while (opcion==0){// espero a que el jugador introduzca el numero de casas a crear
            opcion=leerIR();
          }
           Serial.println(opcion);        
        break;
        
     case 2://mejorar los recursos                   
          Serial.println("que recurso quieres mejorar?");
          opcion=leerIR();
          while (opcion==0){
            opcion=leerIR();
          }
           Serial.println(opcion);
       break;      
  
     case 3: // crear camiones
          Serial.println("cuantos camiones quieres crear ");
          opcion=leerIR();
          while (opcion==0){
            opcion=leerIR();
          }
          Serial.println(opcion);
      break;
         
     case 4://atacar
          Serial.println("a quien atacas?");
          opcion=leerIR();
          while (opcion==0){
            opcion=leerIR();
          }
          Serial.println(opcion);
       break;
      default:
        break;
  }  
}


// ------------------------ FUNCIONES COMUNICACION--------------------------------

void mandarJugada()//Manda la jugada al Maestro
{
  int input = prepararJugada(address,accion,opcion);
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
       status[0]=Wire.read();
       status[1]=Wire.read();
       status[2]=Wire.read();
       status[3]=Wire.read();
       status[4]=Wire.read();
       status[5]=Wire.read();
       status[6]=Wire.read();
       status[7]=Wire.read();
      }     
  }
}
  

//FUNCION AUXILIAR PREPRARAR JUGADA//

int prepararJugada(int address, int accion, int destinatario)  //junta las órdenes del
{                                                //infrarrojo para mandarlas al maestro
  return address*100+accion*10+destinatario;
}


// FUNCION AUX. MATRIZ DE LEDS//

void MatrizLeds()    // FUNCIÓN FINAL QUE CONTROLA LA MATRIZ DE LEDS
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
      apagarContador(); // Apago la columna 0 = contadorTomate
      contador(0,tomate);      // Enciendo en la columna 0 el numero de tomates      que tengo pa' los gazpachoh
      contador(1,nivelTomate); // Enciendo en la columna 1 el numero de nivelTomate  que tengo
      contador(2,lechuga);     // Enciendo "   "    "    2 "    "     " lechugas      "    "
      contador(3,nivelLechuga);// Enciendo "   "    "    3 "    "     " nivelLechugas "    "  que me lah quitan de la manoh
      contador(4,marmol);      // Enciendo "   "    "    4 "    "     " marmoles      "    "  duros como ninguno!
      contador(5,nivelMarmol); // Enciendo "   "    "    5 "    "     " nivelMarmoles "    "
      contador(6,camion);      // Enciendo "   "    "    6 "    "     " fragonetas    "    "   pa' robah
      contador(7,cortijo);     // Enciendo "   "    "    7 "    "     " cortijos      "    "   pa' ser el mas riiico, ay papa!
  }
  
void apagarContador()   // apaga todos los leds del contador
  {
    for (int led=0; led<8; led++)
    {  
      for (int columna=0; columna<8; columna++)
      {
        lc.setLed(0,columna,led,false);
      }
    }
  }

int contador (int parametro, int unidad)  // enciende en el contador (columna) el numero de leds (niveles) de cada contador
  {
    for (int led=0; led<unidad; led++)
     { 
      lc.setLed(0,parametro,led,true);
     } 
  }
  
  
//FUNCION AUXILIAR DE NÚMERO A LETRA Y VICEVERSA//

char numeroAletra(int num)
{
  char b[2];
  String str;
  str=String(num);
  str.toCharArray(b,2);
  return str.charAt (0);
}

int letraAnumero(char letra)
{
  return letra - '0';
}
