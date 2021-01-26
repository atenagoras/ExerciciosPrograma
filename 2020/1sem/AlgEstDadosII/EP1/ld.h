#ifndef _LD
#define _LD
#include "EstrutTSO.h"
#include "livro.h"
#include "nolst.h"
// Lista Desordenada
class LD{
public:
  LD(){
    ini = NULL;
    fim = NULL;
    N = 0;
  }
  ~LD();
  bool vazia();
  void insere(Chave *chave, long n);
  long devolve(Chave chave); // devolve a frequência da palavra no texto
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
  long tam();
  Nolst /*LD::*/ *INI(){
    return ini;
  }

  Nolst /*LD::*/ *FIM(){
    return fim;
  }
  // Nolst *busca(Chave chave);
private:
  Nolst *ini, *fim;
  long N; // tamanho da TSO em palavras
  // void antes(Chave chave, long pos, Nolst *no);
  // void depois(Chave chave, long pos, Nolst *no);
  // auxílio às funções inserir(), devolve() e remove()
  Nolst /*LD::*/ *busca(Chave chave){
    Nolst *p;
    for (p = ini; p; p = p->prox){
      if (igual(chave, p->info->chave))
	return p;
    }
    return NULL;
  }

};

#endif
