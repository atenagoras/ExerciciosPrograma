#ifndef FILA
#define FILA

template <class Item>
class No{
public:
  No<Item> *ant, *prox;
  Item item;
  No();
  No(Item info);
  ~No();
};

template <class Item>
class Fila{
public:
  Fila();
  ~Fila();
  bool vazia();
  bool inserirINI(No<Item> *no);
  bool inserirFIM(No<Item> *no);
  bool inserirMeio(No<Item> *no, No<Item> *cmp);
  bool insere(Item item);
  // Obs: As funções de remoção de Item não removem-no da memória, apenas os retiram da lista. a remoção deverá ser feita por outras funções do programa principal ou nas classes Pistas ou Pista
  Item removeINI();
  Item remove();
  Item removeFIM();
  Item remove(No<Item> *no); // sempre puxa o nó seguinte para o lugar do nó removido
  Item mostraMeio();
  Item mostraINI();
  Item mostraFIM();
  No<Item> *ini, *fim;
  int tam;
};

#include "Fila.tcc"
#endif // FILA
