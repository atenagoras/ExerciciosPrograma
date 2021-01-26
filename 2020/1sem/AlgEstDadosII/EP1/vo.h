#ifndef _VO
#define _VO
#include "EstrutTSO.h"
class VO{
private:
  infoTSO **info;
  long N; // tamanho do vetor
  /* antes(): Insere chave no vetor na posição posV, e desloca todos os elementos posteriores para frente, incluindo o antigo em posV
     Parâmetros:
     Chave chave: chave a ser inserida
     long posT  : posição em que a chave foi encontrada no texto de origem
     long posV  : Posição em que a chave vai ser inserida no vetor */
  void antes(Chave chave, long posT, long posV);
  // insere chave depois da posição posV e desloca todos os elementos posteriores para frente, menos posV
  void depois(Chave, long posT, long posV);
public:
  VO(){
    info = NULL;
    N = 0;
  }
  ~VO(){
    long i;
    for (i = 0; i < N; i++)
    DelInfo(info[i]);
    //free(info);
  }
  bool vazia();
  void insere(Chave *chave, long n);
  long bb(Chave chave); // busca binária
  long devolve(Chave chave); // devolve a frequência da chave no texto em que foi colhida
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
  long tam(){
    return N;
  }
};
#endif
