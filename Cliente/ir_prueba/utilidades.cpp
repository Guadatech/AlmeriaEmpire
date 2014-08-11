#include "utilidades.h"

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


