#ifndef _tr
#define _tr
#include <stdlib.h>
#include "EstrutTSO.h"
#include "livro.h"
#include "noArvore.h"

// Classe de TREAPs
/* Treaps são Árvores binárias que utilizam um número de prioridade definido aleatoriamente em cada nó para reabalancear a árvore utilizando a propriedade de Max Heap
*/

class TR{
public:
  TR();
  ~TR();
  void insere(Chave *chave, long n);
  void insere(Chave chave, long pos);
  long devolve(Chave chave);
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
  long tamanhoSub();
  Chave min();
  long tam();
  void deleteMin();
  void Destroi();
private:
  // Dados
  noArv *raiz; 
  long N; // nº de nós
  // Funções auxiliares
  long tamanhoSub(noArv *no);
  long devolve(noArv *no, Chave chave);
  noArv *insere(noArv *no, Chave chave, long pos);
  noArv *seleciona(noArv *no, long k);
  long rank(Chave chave, noArv *no);
  noArv *min(noArv * no);
  noArv *deleteMin(noArv *no);
  noArv *remove(noArv *no, Chave chave);
  void destroi(noArv *no);
  noArv *rodaDir(noArv *no);
  noArv *rodaEsq(noArv *no);
};
#endif
