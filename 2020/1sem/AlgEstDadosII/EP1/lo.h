#ifndef _LO
#define _LO
#include "EstrutTSO.h"
#include "livro.h"
#include "nolst.h"
#include "ld.h"
// Lista Desordenada
class LO{
public:
  LO(){
    ini = NULL;
    fim = NULL;
    N = 0;
  }
  // Cria lista ordenada a partir de lista desordenada
  LO(LD *l);
  ~LO();
  void insere(Chave *chave, long n);
  long devolve(Chave chave); // devolve a frequência da palavra no texto
  void remove(Chave chave);
  long rank(Chave chave);
  Chave seleciona(long k);
  long tam();
  Nolst /*LO::*/ *INI(){
    return ini;
  }
  
  Nolst /*LO::*/ *FIM(){
    return fim;
  }
  
  // Nolst *loBusca(Chave chave);
private:
  Nolst *ini, *fim;
  long N; // tamanho da TSO em palavras
  // Auxílio de inserir()
  void antes(Chave chave, long pos, Nolst *no);
  void depois(Chave chave, long pos, Nolst *no);
  // auxílio às funções devolve() e remove()
  Nolst /* LO:: */ *loBusca(Chave chave){
    Nolst *p;
    for (p = ini; p; p = p->prox){
      if (igual(chave, p->info->chave))
	return p;
    }
    return NULL;
  }
};

#endif
