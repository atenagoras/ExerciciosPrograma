#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "livro.h"
#include "EstrutTSO.h"
#include "vd.h"

bool VD:: vazia(){
  if (!info && !N)
    return true;
  return false;
}


// Reescrevendo insere para permanecer desordenado
void VD:: insere(Chave *chave, long n){
    long i;
  info = NULL;
  // info  = (infoTSO **) malloc(sizeof(infoTSO *));
  // info[0] = novaInfo();
  infoTSO *resBusca = NULL;
  for (i = 0; i < n; i++)
    if (!(resBusca = busca(chave[i]))){ // Se não encontrar, malloca espaço para o vetor, e cria um novo ítem para a TSO
      info = (infoTSO **) realloc(info, sizeof(infoTSO *) * (++N));
      info[N-1] = novaInfo();
      insereInfo(chave[i], i, info[N-1]);
    }
    else
      insereInfo(chave[i], i, resBusca); // Se encontrar, escreve em cima e ph0d4s C
}

// Opera apenas no vetor aux, quando este existe
void VD:: Qsort(long ini, long fim){
  long i, j; // índices
  Particiona(ini, fim, &i, &j);
  if (j > ini)
    Qsort(ini, j + 1);
  if (i < fim)
    Qsort(i, fim);
}

// Opera apenas no vetor aux, quando este existe. Auxilia Qsort()
void VD:: Particiona(long ini, long fim, long *i, long *j){
  infoTSO *pivo;
  *i = ini;
  *j = fim - 1;
  pivo = aux[(ini + fim) / 2]; /* chuta o elemento do meio como pivo.
				   Diminui a possibilidade de pegar o
				   pior caso do algoritmo, quando o vetor,
				   já está ordenado (ou o inverso), caso
				   fosse selecionado o primeiro elemento
				   ou o último  */
  while(*i <= *j){
    while(menor(aux[*i]->chave, pivo->chave) && *i < fim)
      (*i)++;
    while(maior(aux[*j]->chave, pivo->chave) && *j > ini)
      (*j)--;
    if( *i <= *j){
      Troca(&aux[*i], &aux[*j]);
      (*i)++;
      (*j)--;
    }
  }
}

// Auxilia Particiona()
void VD:: Troca(infoTSO **info1, infoTSO **info2){
  infoTSO *AUX;
  AUX = *info1;
  *info1 = *info2;
  *info2 = AUX;
}

long VD:: bb(Chave chave){
  long inf = 0; // limite inferior
  long sup = N - 1; // limite superior
  long meio;
  while(inf <= sup){
    meio = (inf + sup) / 2;
    if (igual(chave, aux[meio]->chave));
    return meio;
    if(menor(chave, aux[meio]->chave))
      sup = meio - 1; // se chave
    else
      inf = meio + 1;
  }
  return -1; // não encontrado
}

// Retorna o 
long VD:: Busca(Chave chave){
  long i;
  for (i = 0; i < N; i++)
    if (!strcmp(chave.String, info[i]->chave.String))
      return i;
  return -1;
}

long VD:: devolve(Chave chave){
  long I = Busca(chave);
  if (I > 0)
    return info[I]->freq; // retorna a frequência da palavra
  return 0; // palavra não encontrada
}

void VD:: remove(Chave chave){
  long I = Busca(chave);
  long i;
  if (I > 0){
    DelInfo(info[I]); // apaga o elemento encontrado
    for (i = I; i < N - 1; i++) // desloca todos os elementos posteriores para frente
      info[i] = info[i + 1];
    N--; // diminui tamanho da TSO (vetor desordenado)
  }
}


long VD:: rank(Chave chave){
  criaAux();
  Qsort(0, N);
  long r = bb(chave);
  destroiAux();
  return r;
}

Chave VD:: seleciona(long k){
  criaAux();
  Qsort(0, N);
  Chave r = aux[k]->chave;
  destroiAux();
  return r;
}
