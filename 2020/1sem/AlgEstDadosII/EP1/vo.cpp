#include "vo.h"
#include "livro.h"
#include <string.h>
#include <stdlib.h>

bool VO:: vazia(){
  if (!info && !N)
    return true;
  return false;
}

void VO:: antes(Chave chave, long posT, long posV){
  info = (infoTSO **) realloc(info, sizeof(infoTSO *) * (++N));
  info[N-1] = novaInfo();
  infoTSO *Info = novaInfo();
  insereInfo(chave, posT, Info);
  long i;
  for (i = N - 1; i > posV; i--){
    *info[i] = *info[i-1];
  }
  info[posV] = Info;
}

void VO:: depois(Chave chave, long posT, long posV){
  info = (infoTSO **) realloc(info, sizeof(infoTSO *) * (++N));
  info[N-1] = novaInfo();
  infoTSO *Info = novaInfo();
  insereInfo(chave, posT, Info);
  long i;
  for (i = N - 1; i > posV + 1; i--){
    *info[i] = *info[i-1];
  }
  info[posV + 1] = Info;
}

void VO:: insere(Chave *chave, long n){
  long i = 0, j, flagInseriu;
  info = (infoTSO **) realloc(info, sizeof(infoTSO *) * (++N));
  info[0] = novaInfo();
  insereInfo(chave[i], i, info[0]);
  for(i = 1; i < n; i++){
    flagInseriu = 0;
    for(j = 0; j < N && flagInseriu == 0; j++){
      if (menor(chave[i], info[j]->chave)){
	antes(chave[i], i, j);
	flagInseriu = 1;
      }
      else if (igual(chave[i], info[j]->chave)){
	insereInfo(chave[i], i, info[j]);
	flagInseriu = 1;
      }
    }
    if (!flagInseriu){ // Neste ponto j = N
      depois(chave[i], i, N - 1);
      flagInseriu = 1;
    }
  }
}

long VO:: bb(Chave chave){
  long inf = 0; // limite inferior
  long sup = N - 1; // limite superior
  long meio;
  while(inf <= sup){
    meio = (inf + sup) / 2;
    if (igual(chave, info[meio]->chave))
      return meio;
    if(menor(chave, info[meio]->chave))
      sup = meio - 1; // se chave
    else
      inf = meio + 1;
  }
  return -1; // não encontrado
}

long VO:: devolve(Chave chave){
  long i = bb(chave);
  if (i > 0)
    return info[i]->freq;
  return 0; // palavra não encontrada
}

void VO:: remove(Chave chave){
  long i = bb(chave), N0 = N;
  if (i > 0){
    DelInfo(info[i]);
    N--;
  }
  if (N0 != N)
    while(i < N){
      info[i] = info[i + 1];
      i++;
    }
  info[N] = NULL;
}


long VO:: rank(Chave chave){
  long i;
  for (i = 0; i < N; i++)
    if (!strcmp(chave.String, info[i]->chave.String))
      return i;
  return -1;
}

Chave VO:: seleciona(long k){
  if (k < N)
    return info[k]->chave;
  Chave nula;
  nula.String = NULL;
  return nula;
}
