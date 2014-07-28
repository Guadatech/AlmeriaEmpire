//lcd-master con rondas y ganador

//librerias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);   //falta la funcion para obtener el numero de casas de los jugadores

int ronda = 0;
int numeroderonda = 0;

int numerodecasasj1 = 0; // casas del jugador 1
int numerodecasasj2 = 0; //casas del jugador 2
int arduinoganador = 0; // 0 es el arduino con mas casas

void setup()
{
  lcd.begin(16,2);  // inicia el lcd
  empire();
  puntos();
  
}

void loop()
{  
  if(numerodecasasj1 <= 8 && numerodecasasj2 <= 8 && numeroderonda <= 90) //si un jugador tiene menos de 8 casas
  {
  lcd.setCursor(0,0);  // comienza desde este punto
  lcd.print("Lider: "); //define el ganador
  lcd.print(arduinoganador);  // arduinoganador es el arduino no mayor numerodecasas
  pasarderonda();
  }
  else  // si no
  {
    lcd.setCursor(0,1);
    lcd.print("fin del juego");
    lcd.setCursor(13,1);
    lcd.print("    "); // quita AMERIA EMPIRE del lcd
    lcd.setCursor(9,0);
    lcd.print("       ");  
    lcd.setCursor(0,0);   // comienza desde este punto
    lcd.print("Ganador: "); //define el ganador
    lcd.print(arduinoganador);  // arduinoganador es el arduino no mayor numerodecasas
  }
 
}

void pasarderonda()
{
  lcd.setCursor(0,1);    // comienza a escrivir desde este punto
  lcd.print("Ronda: ");  //pinta el nº de ronda en el lcd
  numeroderonda++;
  lcd.print(numeroderonda);
  delay(20000);
}

void puntos()
{
  lcd.setCursor(0,0); 
  lcd.print("*");
  lcd.setCursor(0,1); //mostrara los puntos en la pantalla
  lcd.print("*");
  delay(300);
  
  lcd.setCursor(0,0);
  lcd.print("**");
  lcd.setCursor(0,1);
  lcd.print("**");  
  delay(300);

  lcd.setCursor(0,0);
  lcd.print("***");
  lcd.setCursor(0,1);
  lcd.print("***");  
  delay(300);

  lcd.setCursor(0,0);
  lcd.print("****");
  lcd.setCursor(0,1);
  lcd.print("****");
  delay(300);

  lcd.setCursor(0,0);
  lcd.print("*****");
  lcd.setCursor(0,1);
  lcd.print("*****");
  delay(300);
}

void empire()
 {
  lcd.setCursor(9,0); // escribe ALMERIA en el lcd
  lcd.print("ALMERIA");
  lcd.setCursor(10,1);// escribe EMPIRE en el lcd
  lcd.print("EMPIRE");
 }
 
 void casas()
 {
   if(numerodecasasj1 < numerodecasasj2)
   {
     arduinoganador = 2;
   }
   else
   {
     arduinoganador = 1;
   }
   if(numerodecasasj1 = numerodecasasj2)
   {
     arduinoganador = 0;
   }
 }
