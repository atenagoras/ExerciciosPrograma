#include<stdio.h>
#include<stdlib.h>
#include "itoa.h"
// Retorna o nº de dígitos de um número inteiro
int digitos(int n){
  int i, r = 1;
  for (i = 0; n/10 < 0; i++);
  r += i;
  return r;
}

// Converte inteiro para string (requer liberação manual da memória)
char* itoa(int n){
  int r = digitos(n);
  r += 1;
  char *strN = (char *) malloc(sizeof(char) * (r + 1) ) ;
  sprintf(strN, "%d", n);
  return strN;
}
