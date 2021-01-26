#ifndef _AB
#define _AB
#include <stdlib.h>
#include "EstrutTSO.h"
#include "livro.h"
#include "noArvore.h"
// Classe de Árvore Binária
class AB{
public:
  AB(){
    //h = 0;
    N = 0;
    raiz = NULL;    
  }
  ~AB();
  void insere(Chave *chave, long n);
  void insere(Chave chave, long pos);
  long devolve(Chave chave);
  void remove(Chave chave);
  long rank(Chave chave);
  long tam();
  Chave seleciona(long k);
  long tamanhoSub();
  Chave min();
  void deleteMin();
  void Destroi();
private:
  // dados
  noArv *raiz;
  long N; // nº nós
  // long h; // altura da árvore
  
  // funções auxiliares
  long tamanhoSub(noArv *no);
  long Devolve(noArv *no, Chave chave);
  noArv *Insere(noArv *no, Chave chave, long pos);
  noArv *Seleciona(noArv *no, long k);
  long rank(Chave chave, noArv *no);
  noArv *min(noArv * no);
  noArv *deleteMin(noArv *no);
  noArv *remove(noArv *no, Chave chave);
  void destroi(noArv *no);
};
#endif
