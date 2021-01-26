#include <string.h>
#include <stdlib.h>
#include "tr.h"

// A classe TR não tem nenhum membro de dado adicional, então, na verdade ele apenas inicializa a árvore binária com a função de construção de AB
TR:: TR(){
  raiz = NULL;
  N = 0;  
}

TR:: ~TR(){
  Destroi();
}

void TR:: destroi(noArv *no){
  if (!no)
    return;
  destroi(no->esq);
  destroi(no->dir);
  delete no;
  no = NULL;
}

void TR:: Destroi(){
  destroi(raiz);
  N = 0;
  raiz = NULL;
}


// tamanho da subárvore
long TR:: tamanhoSub(){
  return tamanhoSub(raiz);
}

long TR:: tamanhoSub(noArv *no){
  if (no == NULL)
    return 0;
  else
    return no->N;
}

long TR:: devolve(Chave chave){
  long d = devolve(raiz, chave);
  return d;
}

long TR:: devolve(noArv *no, Chave chave){
  if (!no)
    return 0;

  if (maior(no->info->chave, chave))
    return devolve(no->esq, chave);
  else if (menor(no->info->chave, chave))
    return devolve(no->dir, chave);
  else return no->info->freq;
}


Chave TR:: seleciona(long k){
  return seleciona(raiz, k)->info->chave;
}

noArv * TR:: seleciona(noArv *no, long k){
  if (!no)
    return NULL;

  long t = tamanhoSub(no->esq);
  if (t > k) return seleciona(no->esq, k);
  else if (t < k) return seleciona(no->dir, k - t - 1);
  return no; // else
}

long TR:: rank(Chave chave){
  return rank(chave, raiz);
}

long TR:: rank(Chave chave, noArv *no){
  if (!no)
    return 0;
  if (maior(no->info->chave, chave))
    return rank(chave, no->esq);
  else if (menor(no->info->chave, chave))
    return 1 + tamanhoSub(no->esq) + rank(chave, no->dir);
  return tamanhoSub(no->esq);
}

Chave TR:: min(){
  return min(raiz)->info->chave;
}

noArv * TR:: min(noArv *no){
  if (!no->esq)
    return no;
  return min(no->esq);
}

void TR:: deleteMin(){
  raiz = deleteMin(raiz);
}

noArv * TR:: deleteMin(noArv *no){
  if (!no->esq)
    return no->dir;
  no->N = tamanhoSub(no->esq) + tamanhoSub(no->dir) + 1;
  return no;
}

void TR:: remove(Chave chave){
  raiz = remove(raiz, chave);
}

noArv * TR:: remove(noArv *no, Chave chave){
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
      N--;
      return aux;
    }
    else if (!no->dir){
      aux = no->esq;
      delete no;
      N--;
      return aux;
    }

    // Nó com dois filhos
    /* A idéia é jogar o no com a chave a ser removido cada vez mais para baixo, até se tornar um nó folha e ser removido */
    if (no->esq->prioridade < no->dir->prioridade){
      no = rodaEsq(no);
      no->esq = remove(no->esq, chave);
    }
    else {
      no = rodaDir(no);
      no->dir = remove(no->dir, chave);
    }
  }
  no->N = tamanhoSub(no->esq) + tamanhoSub(no->dir) + 1;
  return no;
}

// Retorna o tamanho da árvore, em nº de nós
long TR:: tam(){
  return N;
}

void TR:: insere(Chave *chave, long n){
  long i;
  for (i = 0; i < n; i++)
    insere(chave[i], i);
}

void TR:: insere(Chave chave, long pos){
  raiz = insere(raiz, chave, pos);
}

/* sorteio(): Sorteia entre 0 e 1000000 um número aleatório 
   Usado para gerar os números de prioridade aleatória */
long sorteio(){
  return (long) rand() % (1000000 + 1);
}

noArv * TR:: insere(noArv *no, Chave chave, long pos){
  infoTSO *Info;
  if (!no){ // caso base, Nó é nulo
    Info = novaInfo();
    insereInfo(chave, pos, Info);
    N++;
    return new noArv(Info, 1, sorteio());
  }
  
  if (maior(no->info->chave, chave)){
    no->esq = insere(no->esq, chave, pos);
    // Ajusta a árvore para conservar a propriedade Heap da árvore, se necessário
    if (no->esq->prioridade > no->prioridade)
      no = rodaDir(no);
  }
  else if (menor(no->info->chave, chave)){
    no->dir = insere(no->dir, chave, pos);
    // Ajusta a árvore para conservar a propriedade Heap da árvore, se necessário
    if (no->dir->prioridade > no->prioridade)
      no = rodaEsq(no);
  }
  else 
    insereInfo(chave, pos, no->info);
  no->N = tamanhoSub(no->esq) + tamanhoSub(no->dir) + 1;
  return no;
}

// Algoritmos de rotação inspirados em https://www.geeksforgeeks.org/treap-set-2-implementation-of-search-insert-and-delete/?ref=lbp
/*rodaEsq(): Rotaciona a subárvore à esquerda 
  noArv *velha: atual raíz da subárvore
  Retorno: Filho direito rotacionado à esquerda como nova raíz */
noArv * TR:: rodaEsq(noArv *velha){
  noArv *novaRaiz = velha->dir, *subArv = novaRaiz->esq;
  // Rotação
  novaRaiz->esq = velha;
  velha->dir = subArv;
  // Atualiza o tamanho da subárvore na velha raíz (na Nova Raiz, deve ser atualizada fora desta função)
  velha->N = 1 + tamanhoSub(velha->esq) + tamanhoSub(velha->dir);
  return novaRaiz; 
}

/* rodaDir(): Rotaciona a subárvore à direita 
   noArv *velha: atual raíz da subárvore
   Retorno: Filho esquerdo rotacionado à direita como nova raíz */
noArv * TR:: rodaDir(noArv *velha){
  noArv *novaRaiz = velha->esq, *subArv = novaRaiz->dir;
  // Rotação
  novaRaiz->dir = velha;
  velha->esq = subArv;
  // Atualiza o tamanho da subárvore na velha raíz (na Nova Raiz, deve ser atualizada fora desta função)
  velha->N = 1 + tamanhoSub(velha->esq) + tamanhoSub(velha->dir);
  return novaRaiz;
}
