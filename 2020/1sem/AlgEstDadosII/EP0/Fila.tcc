#include<cstddef>
template <class Item>
No<Item>::No(): ant(NULL), prox(NULL) {}; // Construtuor

template <class Item>
No<Item>::No(Item *info){
  item = info;
  ant = NULL;
  prox = NULL;
}

template <class Item>
No<Item>::~No(){
  ant = prox;
  if (prox)
    prox->ant = ant;
  if (item)
    delete item;
  item = NULL;
  //delete this;
}

template <class Item>
Fila<Item>::Fila(): ini(NULL), fim(NULL), tam(0) {};

template <class Item>
Fila<Item>::~Fila(){
  if (vazia())
    return;
  No<Item> *p = ini;
    while(p || ini){
      p = ini->prox;
      if (ini)
        delete ini;
      ini = p;
    }
  ini = NULL;
  fim = NULL;
  tam = 0;
}

template<class Item>
bool Fila<Item>:: vazia(){ // Estranho, mas compiloux...
  if (ini == NULL && fim == NULL && tam == 0)
    return true;
  return false;
}

template<class Item>
bool Fila<Item>:: inserirINI(No<Item> *no){
  if ( vazia() ){
    ini = fim = no;
    tam++;
  }
  else if (no->item != ini->item){
    no->prox = ini;
    ini->ant = no;
    ini = no;
    tam++;
  }
  else
    return false;
  return true;
}

template<class Item>
bool Fila<Item>:: inserirFIM(No<Item> *no){
  if ( vazia() ){
    fim = ini = no;
    tam++;
  }
  else if (no->item != fim->item){
    no->ant = fim;
    fim->prox = no;
    fim = no;
    tam++;
  }
  else
    return false;
  return true;
}

template<class Item>
/* inserirMeio(): Insere um nó na lista antes do nó de comparação, ou insere no fim. Esta função é auxiliar à FilaOrd::inserirORD
   Argumentos:
   No *no   : Nó inserido
      *cmp  : Nó de comparação */
bool Fila<Item>:: inserirMeio(No<Item> *no, No<Item> *cmp){
  if (cmp == ini)
    return inserirINI(no);
  if (no->item != cmp->item){
    no->prox = cmp;
    no->ant  = cmp->ant;
    cmp->ant->prox = no;
    cmp->ant = no;
    tam++;
  }
  else
    return false;
  return true;
}

template<class Item>
Item* Fila<Item>::removeINI(){
  if (vazia())
    return NULL;
  No<Item> *p = ini;
  ini = ini->prox;
  if (ini)
    ini->ant = NULL;
  tam--;
  if (!tam)
    ini = fim = NULL;
  else if (tam == 1)
    fim = ini;
  return p->item;
}

template<class Item>
Item* Fila<Item>::removeFIM(){
  if (vazia())
    return NULL;
  No<Item> *p = fim;
  fim = fim->ant;
  if (fim)
    fim->prox = NULL;
  tam--;
  if (!tam)
    ini = fim = NULL;
  else if (tam == 1)
    ini = fim;
  return p->item;
}

template<class Item>
// remove(): Sempre que possível, remove o nó da fila e coloca o nó POSTERIOR no lugar do removido
// Retorno: Ponteiro para Item*
Item* Fila<Item>::remove(No<Item> *no){
  if (vazia())
    return NULL;
  if (no == ini)
    return removeINI();
  else if (no == fim)
    return removeFIM();
  else{ // Se chegou até aqui, é porque tem mais de um nó, e exitem no->ant e no->prox diferentes de NULL
    no->ant->prox = no->prox;
    no->prox->ant = no->ant;
  }
  no->ant = no->prox = NULL;
  tam--;
  return no->item;
}

template<class Item>
Item* Fila<Item>::mostraINI(){
  if (!vazia())
    return ini->item;
  return NULL;
}

template<class Item>
Item* Fila<Item>::mostraFIM(){
  if (!vazia())
    return fim->item;
  return NULL;
}
