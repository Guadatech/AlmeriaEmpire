

#include "sonidos.h"


int length1 = 3; // numero de notas
char notes1[] = "xba"; //notas
int beats1[] = {2,2,4}; //duracion de las notas

int length2 = 3; // numero de notas
char notes2[] = "AGF"; //notas
int beats2[] = {2,2,4}; //duracion de las notas


int length3 = 12; // numero de notas
char notes3[] = "C E G ABcfef" ;//notas
int beats3[] = {6,2,6,2,6,4,2,2,4,6,6,8}; //duracion de las notas

int tempo = 250; //tempo del tiempo de las notas

void initSonidos() 
{
  pinMode(PIN_SONIDOS, OUTPUT);  
}


void playTone(int tone, int duration) 
  { 
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
    { 
      digitalWrite(PIN_SONIDOS, HIGH); 
      delayMicroseconds(tone); 
      digitalWrite(PIN_SONIDOS, LOW); 
      delayMicroseconds(tone); 
    } 
  } 
  
void playNote(char note, int duration) 
  { 
    char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'x', 'y' }; 
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 834, 765, 593, 468, 346, 224, 655 , 715 }; 
    int SPEE = 5; // play the tone corresponding to the note name 
    for (int i = 0; i < 17; i++) 
      {   
        if (names[i] == note) 
          { 
            int newduration = duration/SPEE; 
            playTone(tones[i], newduration); 
          } 
       } 
   } 


void sonido_inicio()
{
for (int i = 0; i < length3; i++) 
       { if (notes3[i] == ' ') 
           { 
             delay(beats3[i] * tempo); // rest 
           } 
         else 
           { 
             playNote(notes3[i], beats3[i] * tempo); 
           } // pause between notes delay(tempo); 
        }
} 


void sonido_ganar()
{
for (int i = 0; i < length1; i++) 
       { if (notes1[i] == ' ') 
           { 
             delay(beats1[i] * tempo); // rest 
           } 
         else 
           { 
             playNote(notes1[i], beats1[i] * tempo); 
           } // pause between notes delay(tempo); 
        }
} 


void sonido_perder()
{
for (int i = 0; i < length2; i++) 
       { if (notes1[i] == ' ') 
           { 
             delay(beats2[i] * tempo); // rest 
           } 
         else 
           { 
             playNote(notes2[i], beats2[i] * tempo); 
           } // pause between notes delay(tempo); 
        }
} 







