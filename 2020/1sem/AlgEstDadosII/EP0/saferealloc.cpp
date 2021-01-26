#include<stdlib.h>
#include "saferealloc.h"
#include "string.h"

/*safeRealloc(): Cria um novo vetor com um novo tamanho, realocando o antigo dentro dele
  Parâmetros:
  void *ptr: Vetor a ser realocado
  size_t
    Nold   : Tamanho antigo do vetor
    Nnew   : Tamanho novo do vetor
  Retorno: (void *) Ponteiro para vetor maior com conteúdo antigo já copiado */
void* safeRealloc(void *ptr, size_t Nold, size_t Nnew){
  if (Nold >= Nnew)
    return ptr;
  void *Nptr = (void *) malloc(Nnew);
  Nptr =  memcpy(Nptr, ptr, Nold);
  free(ptr);
  return Nptr;
}
