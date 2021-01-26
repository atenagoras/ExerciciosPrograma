#include "EstrutTSO.h"
#include "livro.h"
#include "nolst.h"
#include "lo.h"
#include "ld.h"

LO:: LO(LD *l){
  if (l->vazia()){
    N = 0;
    ini = fim = NULL;
    return;
  }
  
  bool inseriu = false;
  infoTSO *info = novaInfo();
  Nolst *o = l->INI(); // ponteiro para LD (parâmetro de entrada)
  insereInfo(o->info->chave, o->info->pos, info);
  Nolst *no = new Nolst(info);
  ini = fim = no;
  N = 1;
  Nolst *p; // ponteiro para atual LO (retorno da função de criação)
  for (o = l->INI(); o != NULL; o = o->prox){
    inseriu = false;
    for (p = ini; p != NULL && inseriu == false; p = p->prox){
      if (menor(o->info->chave, p->info->chave)){
	antes(o->info->chave, o->info->pos, p);
	p->ant->info->freq = o->info->freq;
	inseriu = true;
      }
    }
    if (!inseriu){
      depois(o->info->chave, o->info->pos, fim);
      fim->info->freq = o->info->freq;
      inseriu = true;
    }
  }
}

// libera lista da memória
LO:: ~LO(){
  Nolst *p, *aux = ini->prox;
  for (p = ini; p; p = aux){
    aux = p->prox;
    delete p;
  }
  ini = fim = NULL;
  N = 0;
}

// cria novo nó e o insere antes de nó
void LO:: antes(Chave chave, long pos, Nolst *no){
  infoTSO *info = novaInfo();
  Nolst *novo;
  insereInfo(chave, pos, info);
  if (no){ // Se a lista não está vazia...
    novo = new Nolst(info, no->ant, no);
    if (no->ant)
      no->ant->prox = novo;
    no->ant = novo;
  }
  else{
    novo = new Nolst(info);
    ini = novo;
    fim = novo;
  }
  if (no == ini)
    ini = novo;
  N++;
}

void LO:: depois(Chave chave, long pos, Nolst *no){
  infoTSO *info = novaInfo();
  Nolst *novo;
  insereInfo(chave, pos, info);
  if (no){ // Se a lista não está vazia...
    novo = new Nolst(info, no, no->prox);
    if (no->prox)
      no->prox->ant = novo;
    no->prox = novo;
  }
  else {
    novo = new Nolst(info);
    ini = fim = novo;
  }
  N++;
  if (no == fim)
    fim = novo;
}

void LO:: insere(Chave *chave, long n){
  long i;
  bool inseriu = false;
  infoTSO *info = novaInfo();
  insereInfo(chave[0], 0, info);
  Nolst *no = new Nolst(info);
  ini = fim = no;
  N = 1;
  Nolst *p;

  for (i = 1; i < n; i++){
    inseriu = false;
    for (p = ini; p != NULL && inseriu == false; p = p->prox){
      if (menor(chave[i], p->info->chave)){
	antes(chave[i], i, p);
	inseriu = true;
      }
      else if (igual(chave[i], p->info->chave)){
	insereInfo(chave[i], i, p->info);
	inseriu = true;
      }
    }
    if (!inseriu){
      depois(chave[i], i, fim);
      inseriu = true;
    }
  }
}

long LO:: devolve(Chave chave){
  Nolst *p = loBusca(chave);
  if (p)
    return p->info->freq;
  return 0;
}

void LO:: remove(Chave chave){
  Nolst *p = loBusca(chave);
  if (!p)
    return;
  if (p->ant)
    p->ant->prox = p->prox;
  if (p->prox)
    p->prox->ant = p->ant;
  if (p == ini)
    ini = p->prox;
  if (p == fim)
    fim = fim->ant;
  delete p;
  N--;
}

long LO:: rank(Chave chave){
  Nolst *p;
  long i = 0;
  bool achou = false;
  for (p = ini; p && !achou; p = p->prox){
    if (igual(chave, p->info->chave))
      achou = true;
    i++;
  }
  if (i < N)
    return i;
  return -1;
}

Chave LO:: seleciona(long k){
  Nolst *p = ini;
  Chave nula;
  long i;
  nula.String = NULL;
  if (k >= N)
    return nula;
  for (i = 0; i < k; i++)
    p = p->prox;
  return p->info->chave;
}

long LO:: tam(){
  return N;
}

