#ifndef tempo
#define tempo
#include "livro.h"
#include "EstrutTSO.h"

// Estrutura para armazenar os resultados das medições
typedef struct{
  double Tinsere, Tdevolve, Tremove, Trank, Tseleciona, Ttotal;
  long Ttam; // tamanho da estrutura em número de palavras armazenadas
  char *nomeTSO;
} tabTempo;

// Cria Variável de medição de tempo dos testes da experiência para um tipo de TSO
tabTempo NovoTempo(char *nomeTSO, long Ttam, double Tinsere, double Tdevolve, double Tremove, double Trank, double Tseleciona);
// Imprime Testes em Arquivo
void printTeste(tabTempo t, char *nomearq, long n);
// Apaga variável do tipo TabTempo
void DoomDay(tabTempo var);
/*TestesTSO: */
tabTempo TestesTSO(palavra *livro, long n, char *nomeTSO);

/* Funções de teste de performancce para cada operação das TSO */
template <class TSO>
double insere(palavra *livro, long n, TSO *tso);
template <class TSO>
double devolve(Chave chave, TSO *tso);
template <class TSO>
double remove(Chave chave, TSO *tso);
template <class TSO>
double rank(Chave chave, TSO *tso);
template <class TSO>
double seleciona(TSO *tso);
template <class TSO>
long tam(TSO *tso);
#include "tempo.tcc"
#endif
