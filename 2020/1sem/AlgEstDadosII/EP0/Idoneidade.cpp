#include <stdio.h>
#include <stdlib.h>
#include "voo.h"
#include "sorteio.h"

int main(int argc, char **argv){
  srand(atoi(argv[1]));
  int i, falso = 0, verdadeiro = 0;
  for (i = 0; i < 10000; i++){
    switch(sorteiaPr(atoi(argv[2]))){
    case true:
      verdadeiro++;
      break;
    default:
      falso++;
    }
  }
  printf("Idoneidade do sorteio de veirdadeiro ou falso:\n");
  printf("Verdadeiro: %.3f\%, Falso: %.3f\%\n", (float) verdadeiro / 100, (float) falso / 100);
  printf("Idoneidade do sorteio de 0 a %s:\n", argv[2]);
  int j, x = atoi(argv[2]);
  int *y = (int *) calloc(x + 1, sizeof(int));
  for(i = 0; i < 10000; i++){
    for (j = 0; j <= x; j++){
      y[sorteia(x)]++;
    }
  }
  for (i = 0; i <= x; i++)
    printf("%03d: %.3f\%\n", i, (float) 100 * y[i] / ((x + 1) * 10000));
  free(y);
  return 0;
}
