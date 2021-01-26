#include <stdlib.h>
#include "voo.h"

// Sorteia um número de intervalo entre 0 a x;
int sorteia(int x){
  int r;
  return r = rand() % (x+1);
}

/* sorteiaP(): Sorteia verdadeiro com Probabilidade Pr
   Parâmetros:
   int Pr: Probabilidade (de 0 a 100)
   retorno:  true ou false */
bool sorteiaPr(int Pr){
  int s = sorteia(100);
  switch(s){
  case 0:
    if (!Pr)
      return false;
    else
      return true;
  case 100:
    if (Pr == 100)
      return true;
    else
      return false;
  default:
    if (s <= Pr)
      return true;
    else
      return false;
  }
}

/* criaVoo(): Sorteia vôo tendo como parâmetros máximo de combustível, máximo de tempo de vôo (variáveis definidas na linha de comando, na chamada do programa). Serão sorteados os membros da estrutura voo:
   - companhia aérea, aeroporto de origem ou destino, emergência (ou não), combustível ou tempo de vôo e número do vôo
   Parâmetros:
   char *cia   : Vetor com a lista de companhias para sortear
        *portos: Vetor com a lista de aeroportos para sortear
   int tcia    : tamanho do vetor de companhias aéras
       tportos : tamanho do vetor de aeroportos
       C       : Nº máximo de combustível a ser sorteado.(Recebe do usuário na linha de comando)
       V       : Nº máximo de tempo esperado de vôo a ser sorteado
       Pr      : Probabilidade de ser criado um vôo de emergência
  Retorno: *v: Ponteiro para estrutura vôo criada */
voo* criaVoo(char **cia, char **portos, int tcia, int tportos, int C, int V, int Pr = 0){
  int fuel = 0, tvoo = 0, Ctorre = sorteia(1), Scia, Sportos;
  if (!Ctorre)
    fuel = sorteia(C) + 1;
  else{
    tvoo = sorteia(V) + 1;
    fuel = 2 * tvoo; // por segurança
  }
  Scia = sorteia(tcia - 1);
  Sportos = sorteia(tportos -1);
  char *SortCIA = cia[Scia];
  char *Sortporto = portos[Sportos];
  int nroAVIAO = sorteia(999);
  bool EMERGENCIA = sorteiaPr(Pr);
  voo *v = new voo( SortCIA, Sortporto, nroAVIAO, fuel, tvoo, Ctorre, EMERGENCIA );
  return v;
}
