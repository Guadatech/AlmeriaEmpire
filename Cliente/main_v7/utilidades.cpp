#include "utilidades.h"

/* Pasa un numero int a una letra char */
char numeroAletra(int num)
{

  char b[2];
  String str;
  str=String(num);
  str.toCharArray(b,2);
  
  return str.charAt(0);
}


/* Pasa una letra char a un numero int */
int letraAnumero(char letra)
{
   return letra - '0';
}


