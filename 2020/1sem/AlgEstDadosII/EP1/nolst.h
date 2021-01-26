#ifndef _nolst
#define _nolst
#include "EstrutTSO.h"
// Classe nó para as listas desordenada e ordenada
class Nolst{
public:
  infoTSO *info;
  Nolst *ant, *prox;
  Nolst(infoTSO *Info);
  Nolst(infoTSO *Info, Nolst *an, Nolst *pr);
  ~Nolst();
};

#endif
