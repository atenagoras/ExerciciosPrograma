#ifndef _VD
#define _VD
#include "EstrutTSO.h"

class VD{
private:
  // variável auxiliar para rank() e seleciona(). Liberar após o uso
  infoTSO **aux;
  infoTSO **info;
  long N; // tamanho do vetor
  // Funções auxiliares para o algoritmo Qsort()
  void Troca(infoTSO **info1, infoTSO ** info2);
  void Particiona(long ini, long fim, long *i, long *j);
  /* Qsort() será usada para ordenação DEPOIS que todas as palavras forem inseridas na em aux. Depente das funções Particiona() e Troca() */
  void Qsort(long ini, long fim);
  /* bb(): Busca binária
     Parâmetro:
     Chave chave: Palavra a ser procurada na tabela
     Retorno: posição da chave em info, -1 para não encontrado */
  long bb(Chave chave);
  void criaAux(){
    aux = (infoTSO **) malloc(sizeof(infoTSO *) * N);
    long i;
    for (i = 0; i < N; i++)
      aux[i] = info[i];
  }
  void destroiAux(){
    free(aux);
    aux = NULL;
  }
  
public:
  VD(){
    info = NULL;
    aux = NULL;
    N = 0;
  }
  ~VD(){
    long i;
    for (i = 0; i < N; i++){
      DelInfo(info[i]);
      // free(info[i]);
    }
    free(info);
  }
  
  bool vazia();
  //infoTSO *busca(Chave chave);
  /* busca(): busca linearmente para achar a chave. Para ajudar insere()
   Parâmetros:
   Chave chave: Palavra a buscar
   Retorno: Ponteiro para a infoTSO* encontrada, ou NULL em caso de fracasso                         */
  infoTSO /*VD::*/ *busca(Chave chave){
  long i;
  for (i = 0; i < N; i++)
    if (!strcmp(chave.String, info[i]->chave.String))
      return info[i];
  return NULL;
}
  
  /* Busca(): busca linearmente para achar a chave. Para ajudar remove() e devolve()
   Parâmetros:
   Chave chave: Palavra a buscar
   Retorno: (long) Posição da chave em info. -1 em caso de fracasso */
  long Busca(Chave chave);
  void insere(Chave *chave, long n);
  long devolve(Chave chave); // devolve a frequência da chave no texto em que foi colhida
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
  long tam(){
    return N;
  }
};
#endif
