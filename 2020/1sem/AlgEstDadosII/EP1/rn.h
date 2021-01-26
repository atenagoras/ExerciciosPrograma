#ifndef _rn
#define _rn
#include <stdlib.h>
#include "EstrutTSO.h"
#include "livro.h"
#include "noArvore.h"
// Classe de Árvore Binária
class RN{
public:
  RN(){}
  void insere(Chave *chave, long n);
  long devolve(Chave chave);
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
private:
  noArv *raiz;
  long N; // nº nós
  long h; // altura da árvore
};
#endif
