#include "livro.h"
#include "ab.h"
// #include "Fila.h"

class Adjacencia {
public:
  int v; // vértice de destino
  Adjacencia *prox;
  Adjacencia(int i);
};

class Vertice {
public:
  palavra p; // Informação do Vértice, no caso a palavra do dicionário
  int grau;
  Adjacencia *cab; // Cabeça da lista de adjacências
  Vertice();
  ~Vertice();
};

class Grafo {
private:
  bool removeLetra(int v1, int v2);
  bool insereLetra(int v1, int v2);
  bool trocaLetras(int v1, int v2);
  bool substituiLetra(int v1, int v2);
  void dfsR_imprime(int v, bool *marked);
  void dfsR_circuito(int vif, int v, int *flag, bool *marked);
  int dfsR(int v, bool *marked, int *tamC); // auxilia o dfs e algoritmos que dependem disso e informa o tamanho do caminho
public:
  int V; // Nº de Vértices
  int A; // Nº de Arestas
  Vertice *adj; // Adjacências do grafo (cada vértice e suas adjacências)

  Grafo(AB *tso);
  Grafo(int N, palavra *palavras); // Cria um gráfico com N vértices a partir de um livro de palavras
  ~Grafo();
  void novaAresta(int v1, int v2);
  void vizinhas(); // procura por palavras vizinhas. Quando encontradas, são produzidas arestas
  // Busca em profundidade: Visita todos os vértices em profundidade
  void dfs_imprime();
  void dfs();
  bool circuito(int v); // Verifica se há um circuito para o qual o vértice v é o início e fim
  bool *circuitos(); // Procura por circuitos em todos os vértices
  palavra devolve(int v); // devolve a palavra no vértice V
  
  
  // Conta quantas componentes conexas tem um grafo. Retorna o vetor tamCon com o tamanho das componentes
  int compConexas(int *tamCon);
  int *caminhoMaisCurto(int v);
};

