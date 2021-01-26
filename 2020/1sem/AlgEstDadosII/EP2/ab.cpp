#include "noArvore.h"
#include "ab.h"
#include <stdio.h>
#include <string.h>

AB:: ~AB(){
  Destroi();
}

void AB:: destroi(noArv *no){
  if (!no)
    return;
  destroi(no->esq);
  destroi(no->dir);
  delete no;
  no = NULL;
}

void AB:: Destroi(){
  destroi(raiz);
  N = 0;
  raiz = NULL;
}

// tamanho da subárvore
long AB:: tamanhoSub(){
  return tamanhoSub(raiz);
}

long AB:: tamanhoSub(noArv *no){
  if (no == NULL)
    return 0;
  else
    return no->N;
}

void AB:: insere(Chave *chave, long n){
  long i;
  for (i = 0; i < n; i++)
    insere(chave[i], i);
}

void AB:: insere(Chave chave, long pos){
  raiz = Insere(raiz, chave, pos);
  if (raiz->N > N)
    N++;
}

noArv * AB:: Insere(noArv *no, Chave chave, long pos){
  infoTSO *Info;
  if (!no){ // caso base, Nó é nulo
    Info = novaInfo();
    insereInfo(chave, pos, Info);
    return new noArv(Info, 1);
  }
  
  if (maior(no->info->chave, chave))
    no->esq = Insere(no->esq, chave, pos);
  else if (menor(no->info->chave, chave))
    no->dir = Insere(no->dir, chave, pos);
  else 
    insereInfo(chave, pos, no->info);
  no->N = tamanhoSub(no->esq) + tamanhoSub(no->dir) + 1;
  return no;
}

long AB:: devolve(Chave chave){
  long d = Devolve(raiz, chave);
  return d;
}

long AB:: Devolve(noArv *no, Chave chave){
  if (!no)
    return 0;

  if (maior(no->info->chave, chave))
    return Devolve(no->esq, chave);
  else if (menor(no->info->chave, chave))
    return Devolve(no->dir, chave);
  else return no->info->freq;
}

Chave AB:: seleciona(long k){
  return Seleciona(raiz, k)->info->chave;
}

noArv * AB:: Seleciona(noArv *no, long k){
  if (!no)
    return NULL;

  long t = tamanhoSub(no->esq);
  if (t > k) return Seleciona(no->esq, k);
  else if (t < k) return Seleciona(no->dir, k - t - 1);
  return no; // else
}

long AB:: rank(Chave chave){
  return rank(chave, raiz);
}

long AB:: rank(Chave chave, noArv *no){
  if (!no)
    return 0;
  if (maior(no->info->chave, chave))
    return rank(chave, no->esq);
  else if (menor(no->info->chave, chave))
    return 1 + tamanhoSub(no->esq) + rank(chave, no->dir);
  return tamanhoSub(no->esq);
}

Chave AB:: min(){
  return min(raiz)->info->chave;
}

noArv * AB:: min(noArv *no){
  if (!no->esq)
    return no;
  return min(no->esq);
}

void AB:: deleteMin(){
  raiz = deleteMin(raiz);
  if (raiz->N < N)
    N--;
}

noArv * AB:: deleteMin(noArv *no){
  if (!no->esq)
    return no->dir;
  no->N = tamanhoSub(no->esq) + tamanhoSub(no->dir) + 1;
  return no;
}

void AB:: remove(Chave chave){
  raiz = remove(raiz, chave);
  if (raiz->N < N)
    N--;
}

noArv * AB:: remove(noArv *no, Chave chave){
  noArv *aux;
  if (!no) // Caso base
    return no;
  // Se a chave é menor que a chave no nó, então ela está na sub-árvore esquerda
  if (menor(chave, no->info->chave))
    no->esq = remove(no->esq, chave);
  else if (maior(chave, no->info->chave)) // Se a chave é maior que a chave no nó, então ela está na sub-árvore direita
    no->dir = remove(no->dir, chave);
  else { // Se a chave a ser removida e o nó da chave são iguais, então o nó é removido
    // nó com um filho ou sem filho
    if (!no->esq){
      aux = no->dir;
      delete no;
      no = NULL;
      return aux;
    }
    else if (!no->dir){
      aux = no->esq;
      delete no;
      return aux;
    }

    // Nó com dois filhos
    aux = min(no->dir); // Pega o sucessor em ordem (O menor na sub-árvore direita
    strcpy(no->info->chave.String,aux->info->chave.String); // Copia a chave do sucessor em Ordem no lugar da chave a ser removida
    no->info->freq = aux->info->freq;
    no->info->pos = aux->info->pos;
    no->dir = remove(no->dir, aux->info->chave); // Remove sucessor em ordem
  }
  no->N = tamanhoSub(no->esq) + tamanhoSub(no->dir) + 1;
  return no;
}

// Retorna o tamanho da árvore, em nº de nós
long AB:: tam(){
  return N;
}
