#include "ab.h"
#include "grafo.h"

typedef struct {
  char nomeArq[256];
  int vertices;
  int arestas;
  char mesmaOrdGrandeza[10]; // Mesma Ordem de grandeza? Sim ou Não
  float den; // Densidade
  float mediaGraus;
} medidas;
void printMedidas(char *nome, medidas *M);

typedef struct {
  char nomeArq[256];
  int componentes;
  int maior; // maior número de componentes
  int menor; // menor número de componentes
  float mediaComp; // média de compomentes
} conexidade;
void printConexidade(char *nome, conexidade *C);

typedef struct {
  char nomeArq[256];
  float distMedia; // distância média entre duas palavras
} caminhosCiclos;
void printcaminhosCiclos(char *nome, caminhosCiclos *Ca);

medidas Medidas(FILE *fp, Grafo *g);
conexidade Conexidade(FILE *fp, Grafo *g);
caminhosCiclos CaminhosCiclos(FILE *fp, Grafo *g);
void Experimentos(char *nomeArq, AB *tso);
