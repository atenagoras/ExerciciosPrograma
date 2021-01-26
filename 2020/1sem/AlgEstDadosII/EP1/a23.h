#ifndef _a23
#define _a23
#include <stdlib.h>
#include "EstrutTSO.h"
#include "livro.h"

/* Árvores 2-3 podem ter 2 ou três nós, eventualmente e já são balanceadas por natureza
   - Quando têm 2 nós (esquerda e direita) possuem uma chave, e obedecem as regras de árvores binárias
   - Quando têm 3 nós, (esquerda, centro, direita) possui chaves esquerda e direita
     + As regras são semelhantes às das árvores binárias, mas os filhos esquerdos são menores que a chave direita;
     + O filho do centro está entre a chave esquerda e a chave direita;
     + O filho direito é maior que o a chave direta
   - As inclusões podem envolver tornar um nó binário em um ternário (com 3 filhos)
   - As remoções podem envolver um desmembramento, e um nó ternário torna-se binário (com 2 filhos) */

class No{
public:
  infoTSO *infoEsq, *infoDir; // armazenar chaves esquerda e direita, eventualmente
  int nchaves; // nº de chaves (determina se é um nó binário ou ternário)
  long N; // Total de nós na subárvore
  No *pai; // para tornar mais fácil o algoritmo de subida recursiva do nó a ser incluido
  No *esq, *centro, *dir;
  No(infoTSO *info, long n, No *pai);
  No(infoTSO *info, long n, No *Esq, No *Dir, No *Pai);
  No(No* no); // construtor de cópia
  ~No();
};

// Classe de Árvore Binária
class A23{
public:
  A23();
  ~A23();
  void insere(Chave *chave, long n);
  void insere(Chave chave, long pos);
  No *busca(No *no, Chave chave);
  long devolve(Chave chave);
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
  long tam();
private:
  No *raiz;
  long N; // nº nós
  // long h; // altura da árvore
  long tamSub(No *no);
  void insere(No *no, No* novo);
  No *buscaPaiDoNulo(No *no, Chave chave, No *pai);
  No *quebraNo(No *no, No* novo);
  void destroi(No *no);
};
#endif
