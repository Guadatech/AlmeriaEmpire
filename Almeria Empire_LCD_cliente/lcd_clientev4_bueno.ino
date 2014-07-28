#include <LiquidCrystal_I2C.h>
#include <Wire.h>  

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  




#include <IRremote.h>

decode_results results;
int ir = 2;
IRrecv irrecv(ir);

int accion;
int opcion;
int numerodecasas;
int numeroderecursos;
int numerodecamiones;
int camionesdeataque;

int leerIR()
  {
    int lectura = 0;
    if (irrecv.decode(&results))
      {
        irrecv.resume(); // Receive the next value
     }


  if(results.value==16580863)

     {
       Serial.println("off");
       results.value=0;
     }

  if(results.value==16593103)

     {
       Serial.println("0");
       results.value=0;
     }

  if(results.value==16582903)

     {
      lectura = 1;
      
       Serial.println("lee un uno");
       results.value=0;
     }

  if(results.value==16615543)

     {
       lectura=2;
       Serial.println("lee un 2");
       results.value=0;
     }

  if(results.value==16599223)

   {
       lectura=3;
       Serial.println("lee un 3");
       results.value=0;
   }

  if(results.value==16591063)

     {
       lectura=4;
       Serial.println("lee un 4");
       results.value=0;
     }

  if(results.value==16623703)

     {
       lectura=5;
       Serial.println("5");
       results.value=0;
     }

  if(results.value==16607383)

     {
       lectura=6;
       Serial.println("6");
       results.value=0;
     }

  if(results.value==16586983)

     {
       lectura=7;
       Serial.println("7");
       results.value=0;
     }

  if(results.value==16619623)

     {
       lectura=8;
       Serial.println("8");
       results.value=0;
     }

  if(results.value==16603303)

     {
         lectura=9;
         Serial.println("9");
         results.value=0;
     }

  return lectura;
}

void setup()  
{
  Serial.begin(9600);  
  lcd.begin(16,2);  
 
  irrecv.enableIRIn();
}

void acciones()// que accion ha elegido el cliente

{  
 
  
  accion=leerIR();

  switch(accion)
  {
    
      case 1:// quiere construir casas
        
          lcd.print("1");
          lcd.setCursor(0,1);
          lcd.print("Cuantas casas");
         
          Serial.println("casas a costruir ?");
          numerodecasas=leerIR();
          while (numerodecasas==0){// espero a que el jugador introduzca el numero de casas a crear
            numerodecasas=leerIR();
          }
           Serial.println(numerodecasas);
           lcd.print(numerodecasas);
          
        break;
      case 2:// mejoras 
          lcd.print("2");
          lcd.setCursor(0,1);
          
          lcd.print("que recurso  ");
         
          Serial.println("que recurso quieres mejorar?");
          numeroderecursos=leerIR();
          while (numeroderecursos==0){
            numeroderecursos=leerIR();
          }
           Serial.println(numeroderecursos);
          lcd.print(numeroderecursos);
         break;
          
  
      case 3: // crear camiones
          lcd.print("3");
          lcd.setCursor(0,1);
          lcd.print("crear camiones ");
          Serial.println("cuantos camiones quieres crear ");
          numerodecamiones=leerIR();
          while (numerodecamiones==0){
            numerodecamiones=leerIR();
          }
          Serial.println(numerodecamiones);
          lcd.print(numerodecamiones);
          
        break;
         
       case 4://atacar
         lcd.print("4");
         lcd.setCursor(0,1);
         lcd.print("A quien atacas ");
         
          Serial.println("a quien atacas?");
          camionesdeataque=leerIR();
          while (camionesdeataque==0){
            camionesdeataque=leerIR();
          }
          Serial.println(camionesdeataque);
          lcd.print(camionesdeataque);
           break;
      default:
        break;
  }
}

void loop()  
{
  lcd.setCursor(0,0);
  lcd.print("PV ");
  lcd.print("0 ");
  lcd.print("Accion: ");
  acciones();


  
  

}
