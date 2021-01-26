#include "ld.h"
#include "lo.h"

LD:: ~LD(){
  Nolst *p, *aux = ini->prox;
  for (p = ini; p; p = aux){
    aux = p->prox;
    delete p;
  }
  ini = fim = NULL;
  N = 0;
}

bool LD:: vazia(){
  if (!N && !ini && !fim)
    return true;
  return false;
}
void LD:: insere(Chave *chave, long n){
  long i;
  bool inseriu = false;
  infoTSO *info = novaInfo();
  insereInfo(chave[0], 0, info);
  Nolst *no = new Nolst(info);
  ini = fim = no;
  N = 1;
  Nolst *p;
  for (i = 1; i < n; i++){
    if (!(p = busca(chave[i]))){ // Se não encontrar a chave a ser inserida, sempre insere no fim
      info = novaInfo();
      insereInfo(chave[i], i, info);
      no = new Nolst(info);
      fim->prox = no;
      no->ant = fim;
      fim = no;
      no->prox = NULL;
      N++;
    }
    else
      insereInfo(chave[i], i, p->info); // Inserindo em cima do já existente
  }
}


// void LD:: depois(Chave chave, long pos, Nolst *no){
//   infoTSO *info = novaInfo();
//   Nolst *novo;
//   insereInfo(chave, pos, info);
//   if (no){ // Se a lista não está vazia...
//     novo = new Nolst(info, no, no->prox);
//     if (no->prox)
//       no->prox->ant = novo;
//     no->prox = novo;
//   }
//   else {
//     novo = new Nolst(info);
//     ini = fim = novo;
//   }
//   N++;
//   if (no == fim)
//     fim = novo;
// }

long LD:: devolve(Chave chave){
  Nolst *p = busca(chave);
  if (p)
    return p->info->freq;
  return 0;

}

void LD:: remove(Chave chave){
  Nolst *p = busca(chave);
  if (!p)
    return;
  if (p->ant)
    p->ant->prox = p->prox;
  if (p->prox)
    p->prox->ant = p->ant;
  if (p == ini)
    ini = p->prox;
  if (p == fim)
    fim = p->ant;
  delete p;
  N--;
}

long LD:: rank(Chave chave){
  LO *l = new LO(this);
  long r = l->rank(chave);
  delete l;
  return r;
}

Chave LD:: seleciona(long k){
  LO *l = new LO(this);
  Chave chave = l->seleciona(k);
  delete l;
  return chave;
}

long LD:: tam(){
  return N;
}
