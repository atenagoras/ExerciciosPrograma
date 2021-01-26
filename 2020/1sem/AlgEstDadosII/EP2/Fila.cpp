#include<iostream>
#include "Fila.h"

// template <class Item>
// No<Item>::No(): ant(NULL), prox(NULL) {}; // Construtuor

// template <class Item>
// No<Item>::No(Item *info){
//   item = info;
//   ant = NULL;
//   prox = NULL;
// }

// template <class Item>
// No<Item>::~No(){
//   delete item;
//   delete this;  
// }

// template <class Item>
// Fila<Item>::Fila(): ini(NULL), fim(NULL), tam(0) {};

// template <class Item>
// Fila<Item>::~Fila(){
//   No<Item> *p;
//   if ( !vazia() )
//     while( !vazia() ){
//       p = ini->prox;
//       delete ini;
//       ini = p;
//     }
//   ini = NULL;
//   fim = NULL;
//   tam = 0;
// }

// template<class Item>
// bool Fila<Item>:: vazia(){ // Estranho, mas compiloux...
//   if (ini == NULL && fim == NULL && tam == 0)
//     return true;
//   return false;
// }

// template<class Item>
// Fila<Item>:: void inserirINI(No<Item> *no){
//   if ( vazia() )
//     ini = fim = no;
//   else {
//     no->prox = ini;
//     ini->ant = no;
//     ini = no;
//   }
//   tam++;
// }

// template<class Item>
// Fila<Item>:: void inserirFIM(No<Item> *no){
//   if ( vazia() )
//     fim = ini = no;
//   else{
//     no->ant = fim;
//     fim->prox = no;
//     fim = no;
//   }
//   tam++;
// }

// template<class Item>
// /* inserirMeio(): Insere um nó no meio da lista, de acordo com a ordem. Esta função é auxiliar à inserirORD
//    Argumentos:
//    No *no   : Nó inserido
//       *cmp  : Nó de comparação
//    int ordem: Ordem de insersão - 0: antes, 1: depois */
// Fila<Item>:: void inserirMeio(No<Item> *no, No<Item> *cmp, int ordem){
//   switch(ordem){
//   case 0:
//     no->ant = cmp->ant;
//     no->prox = cmp;
//     cmp->ant = no;
//     break;
//   case 1:
//     no->ant = cmp;
//     no->prox = cmp->prox;
//     cmp->prox = no;
//   }
//   tam++;
// }
