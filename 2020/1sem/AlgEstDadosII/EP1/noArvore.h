#ifndef _noArv
#define _noArv
#include <string.h>
#include "livro.h"
#include "EstrutTSO.h"

// A idéia dessa classe é ser um nó genérico que serve para todo o tipo de árvore Binária (ABB, RB, AVL, treap etc)
class noArv{
public:
  noArv *esq, *dir;
  infoTSO *info;
  char cor; // caso a árvore seja rubro-negra
  int b; // balanceamento da árvore, se necessário
  long prioridade; // Para Treaps. prioridade é um número aleatório utilizado para manter o balanceamonto, rotacionando a árvore para manter o Max Heap quando necessário
  long N; // nº de nós das subárvores que compoem o nó incluindo ele próprio
  // etc
  noArv(infoTSO *Info, long n = 1){ // Criação para árvore binária de Busca
    info = Info;
    cor = '\0';
    b = 0;
    esq = dir = NULL;
    N = n;
  }

  noArv(infoTSO *Info, long n, long Prioridade){
    info = Info;
    cor = '\0';
    b = 0;
    esq = dir = NULL;
    N = n;
    prioridade = Prioridade;
  }
  
  ~noArv(){
    DelInfo(info);
    info = NULL;
    N = 0;
    esq = dir = NULL;
    b = 0;
    cor = '\0';
    prioridade = 0;
  }
};
#endif
