#include "EstrutTSO.h"
#include "nolst.h"
// Classe nó para as listas desordenada e ordenada

Nolst:: Nolst(infoTSO *Info){
  info = Info;
  ant = NULL;
  prox = NULL;
}
Nolst:: Nolst(infoTSO *Info, Nolst *an, Nolst *pr){
  info = Info;
  ant = an;
  prox = pr;
}
Nolst:: ~Nolst(){
  DelInfo(info);
  info = NULL;
  ant = NULL;
  prox = NULL;
}
