#ifndef _th
#define _th
#include <stdlib.h>
#include "EstrutTSO.h"
#include "livro.h"
// Classe de Tabela Hash
class TH{
public:
  TH(){}
  void insere(Chave *chave, long n);
  long devolve(Chave chave);
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
private:
  infoTSO **info;
  long N;
};
#endif
