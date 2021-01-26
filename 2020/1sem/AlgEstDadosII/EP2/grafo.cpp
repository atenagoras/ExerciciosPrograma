#include <stdio.h>
#include <string.h>
#include "Fila.h"
#include "grafo.h"

Adjacencia:: Adjacencia(int i){
  v = i;
  prox = NULL;  
}

Vertice:: Vertice(){
  cab = NULL;
  grau = 0;
}

Vertice:: ~Vertice(){
  Delpalavra(&p);
  Adjacencia *i = cab;
  while(cab){
    i = i->prox;
    delete cab;
    cab = i;
  }  
}

Grafo:: Grafo(AB *tso){ // Cria um grafo a partir de uma tabela de símbolos ordenada
  V = (int) tso->tam();
  A = 0;
  adj = new Vertice [V];
  int i;
  for (i = 0; i < V; i++){
    adj[i].cab = NULL;
    adj[i].grau = 0;
    Copiapalavra(&adj[i].p, tso->seleciona(i));
  }
}

Grafo:: Grafo(int N, palavra *palavras){
  V = N;
  A = 0;
  adj = new Vertice [V];
  int i;
  for (i = 0; i < V; i++){
    adj[i].cab = NULL;
    adj[i].grau = 0;
    Copiapalavra(&adj[i].p, palavras[i]); // copia palavras[i] para o vértice i do grafo
  }
}

Grafo:: ~Grafo(){
  delete [] adj;
}

/* novaAresta(): Cria duas novas arestas (v1-v2 e v2-v1)
   Parâmetros:
   int v1: Vértice 1
   int v2: Vértice 2 */
void Grafo:: novaAresta(int v1, int v2){
  // Não cria vértices fora dos limites
  if (v1 < 0  || v1 >= V)
    return;
  if (v2 < 0  || v2 >= V)
    return;
  Adjacencia *novo = new Adjacencia(v2);
  novo->prox = adj[v1].cab;
  adj[v1].cab = novo;
  adj[v1].grau++;
  novo = new Adjacencia(v1);
  novo->prox = adj[v2].cab;
  adj[v2].cab = novo;
  adj[v2].grau++;
  A += 2;
}

/* dividePalavra(): Divide uma palavra original em duas partes
   Parâmetros:
   int
     tam: tamanho da string original
     pos: posição do vetor em que deve acontecer a divisão
   char
     *original: string original a ser dividida
     *parte1  : Retorna a parte 1 da string
     *parte2  : Retorna a parte 2 da string 
   Exemplo: original = atenagoras, pos 3: parte1 = aten, parte2 = agoras */
void dividePalavra(int tam, int pos, char *original, char *parte1, char *parte2){
  if (pos >= tam)
    return;
  int i;
  for (i = 0; i <= pos; i++){
    parte1[i] = original[i];
  }
  parte1[i] = '\0';
  parte2[0] = '\0';
  strcpy(parte2, &original[pos + 1]);
}

/* removeLetra(): Testa iterativamente se a remoção de uma letra na palavra do vértice v1 faz com que se torne igual a palavra no vértice v2
   Parâmetros:
   int
    v1: vértice v1
    v2: vértice v2
   Retorno: true se palavra em v1 == palavra em v2 depois de alguma remoção de letra */
bool Grafo:: removeLetra(int v1, int v2){
  char p1[256], p2[256], aux[256], aux1[256], aux2[256];
  strcpy(p1, adj[v1].p.String);
  strcpy(p2, adj[v2].p.String);
  int pos;
  int tam = strlen(p1);
  for (pos = 0; pos < tam; pos++){
    dividePalavra(strlen(p1), pos, p1, aux1, aux2);
    strcpy(aux,aux1);
    aux[pos] = '\0'; // remoção da letra
    strcat(aux, aux2);
    if (strcmp(aux, p2) == 0)
      return true;
  }
  return false;
}

/* dividePalavra2(): Divide uma palavra original em duas partes
   Parâmetros:
   int
     tam: tamanho da string original
     pos: posição do vetor em que deve acontecer a divisão
   char
     *original: string original a ser dividida
     *parte1  : Retorna a parte 1 da string
     *parte2  : Retorna a parte 2 da string 
   Exemplo: original = atenagoras, pos 3: parte1 = ate, parte2 = nagoras */
void dividePalavra2(int tam, int pos, char *original, char *parte1, char *parte2){
  if (pos >= tam)
    return;
  int i;
  parte1[0] = '\0';
  for (i = 0; i < pos; i++){
    parte1[i] = original[i];
  }
  parte1[i] = '\0';
  parte2[0] = '\0';
  strcpy(parte2, &original[pos]);
}

/*insereLetra(): Testa iterativamente se a inserção de uma letra na palavra do vértice v1 faz com que se torne igual a palavra no vértice v2
  Parâmetros:
  int
   v1: vértice v1
   v2: vértice v2
  Retorno: true se palavra em v1 == palavra em v2 depois de alguma remoção de letra */
bool Grafo:: insereLetra(int v1, int v2){
  const char *alfabeto= "abcdefghijklmnopqrstuvwxyz";
  char letra[2];
  letra[0] = '\0';
  letra[1] = '\0';
  char p1[256], p2[256], aux[256], aux1[256], aux2[256];
  strcpy(p1, adj[v1].p.String);
  strcpy(p2, adj[v2].p.String);
  int pos, i, tam = strlen(p1);
  for (i = 0; i < 26; i++){
    letra[0] = alfabeto[i];
    strcpy(aux, letra);
    for (pos = 0; pos < tam; pos++){
      dividePalavra2(tam, pos, p1, aux1, aux2);
      strcpy(aux, aux1);
      strcpy(aux, aux2);
      if (strcmp(aux, p2) == 0)
	return true;
    }
    // inserindo na última posição
    strcpy(aux, aux1);
    strcpy(aux, aux2);
    strcpy(aux, letra);
    if (strcmp(aux, p2) == 0)
      return true;
  }
  return false;
}

/* tl(): troca letra na posição pos1 com letra na posição pos2 na string
   Parâmetros:
   char
    *p: string a ter as letras trocadas
   int
    pos1: Posição da primeira letra a ser trocada
    pos2: Posição da segunda letra a ser trocada */
void tl(char *p, int pos1, int pos2){
  char aux = p[pos1];
  p[pos1] = p[pos2];
  p[pos2] = aux;
}

/* trocaLetras(): troca letras da palavra em v1 iterativamente, testa-a contra a palavra em v2 para ver se são iguais
   Parâmetros:
   int
    v1: Vértice v1
    v2: Vértice v2
   Retorno: true se a palavra em v1 == palavra em v2 após as trocas de letras */
bool Grafo:: trocaLetras(int v1, int v2){
  char p1[256], p2[256], aux[256];
  strcpy(p1, adj[v1].p.String);
  strcpy(p2, adj[v2].p.String);
  strcpy(aux, p1);
  int i, j, tam = strlen(p1);
  for (i = 0; i < tam - 1; i++){
    for (j = i + 1; j < tam; j++){
      tl(aux, i, j);
      if (strcmp(aux, p2) == 0)
	return true;
    }
    strcpy(aux, p1);
  }
  return false;
}

/* substituiLetra(): substitui letras iterativamente em todas as posições da palavra do vértice 1. Compara resultado com p2 para checar igualdade
   Parâmetros:
   int
    v1: Vértice v1
    v2: Vértice v2
   Retorno: true se depois das operações v1 == v2 */
bool Grafo:: substituiLetra(int v1, int v2){
  const char *alfabeto = "abcdefghijklmnopqrstuvwxyz";
  char p1[256], p2[256], aux[256];
  strcpy(p1, adj[v1].p.String);
  strcpy(p2, adj[v2].p.String);
  strcpy(aux, p1);
  int i, j, tam = strlen(p1);
  for (i = 0; i < 26; i++){
    for (j = 0; j < tam; j++)
      aux[j] = alfabeto[i];
    if (strcmp(aux, p2) == 0)
      return true;
    strcpy(aux, p1);
  }
  return false;
}

void Grafo:: vizinhas(){
  int v1, v2, dif;
  bool Arestas = false; // vê o resultado das funções para saber se uma aresta deve ser inserida
  for (v1 = 0; v1 < V; v1++)
    for (v2 = v1 + 1; v2 < V; v2++){
      Arestas = false;
      // Se a diferença de tamanho for maior que 1, não são vizinhas
      dif = strlen(adj[v1].p.String) - strlen(adj[v2].p.String);
      switch (dif){ 
      case 1:
	Arestas = removeLetra(v1,v2);
	break;
      case -1:
	Arestas = insereLetra(v1,v2);
	break;
      case 0:
	if (Arestas = trocaLetras(v1,v2) == false){
	  Arestas = substituiLetra(v1,v2);
	}
	break;
      }
      // Insere novas arestas se o resultados de uma das funções for verdadeiro
      if (Arestas)
	novaAresta(v1, v2);
    }
}

/* Faz a busca recursiva efetivamente. Imprime continuação do caminho */
void Grafo:: dfsR_imprime(int v, bool *marked){
  marked[v] = true;
  Adjacencia *p;
  int w;
  for (p = adj[v].cab; p != NULL; p = p->prox){
    w = p->v;
    // imprime vértices varridos em profundidade
    printf("%s(%d), ", adj[w].p.String, w);
    if (!marked[w])
      dfsR_imprime(w, marked);
  }
}
/* dfs_imprime(): Busca em profundidade do primeiro ao último vértice. Imprime o vértice inicial de cada caminho. Chama dfsR (recursivo) para fazer a busca em profundidade */
void Grafo:: dfs_imprime(){
  bool *marked = new bool [V];
  int v;
  for (v = 0; v < V; v++)
    marked[v] = false;
  printf("Palavra(vértice):\n");
  for (v = 0; v < V; v++){
    if (!marked[v]){
      // imprime vértice inicial v do caminho
      printf("%s(%d): ", adj[v].p.String, v);
      dfsR_imprime(v, marked);
      printf(".\n");
    }
  }
  // delete [] marked;
}

/* dfsR(): Faz a busca recursiva efetivamente. Retorna o tamanho do caminho 
   Parâmetros:
   int
    v: Vértice a ser varrido recursivamente
    *tamC: ponteiro para variável que armazena o tamanho do caminho
   bool
   *marked: Vetor com os vértices marcados como visitados
   Retorno: *tamC  */
int Grafo:: dfsR(int v, bool *marked, int *tamC){
  (*tamC)++;
  marked[v] = true;
  Adjacencia *p;
  int w;
  for (p = adj[v].cab; p != NULL; p = p->prox){
    w = p->v;
    if (!marked[w])
      dfsR(w, marked, tamC);
  }
  return *tamC;
}

/* dfs(): Busca em profundidade do primeiro ao último vértice. Chama dfsR (recursivo) para fazer a busca em profundidade */
void Grafo:: dfs(){
  bool *marked = new bool[V];
  int v;
  for (v = 0; v < V; v++)
    marked[v] = false;
  for (v = 0; v < V; v++){
    if (!marked[v]){
      dfsR(v, marked, NULL);
    }
  }
  delete [] marked;
}

/* dfsR_circuito(): Faz a busca recursivamente até que marked[vif] == true. Não marca o vértice procurado na primeira chamada. Para isto, flag = 0 na primeira chamada
   Parâmetros:
   int:
    vif: Vértice inicial e final procurado para termos um circuito
    v : vértice a ser marcado e ter suas adjacências marcadas recursivamente */
void Grafo:: dfsR_circuito(int vif, int v, int *flag, bool *marked){
  if (vif != v || *flag != 0)
    marked[v] = true;
  if (marked[vif] == true)
    return;
  Adjacencia *p;
  int w;
  for (p = adj[v].cab; p != NULL; p = p->prox){
    w = p->v;
    if (!marked[w])
      dfsR_circuito(vif, w, flag, marked);
  }
}

/* circuito(): Verifica se há um circuito para o qual o vértice v é o início e fim */
bool Grafo:: circuito(int v){
  bool *marked = new bool [V];
  int i, flag = 0;
  for (i = 0; i < V; i++)
    marked[i] = false;
  bool r;
  dfsR_circuito(v, v, &flag, marked);
  r = marked[v];
  delete [] marked;
  return r;
}

/* circuitos(): Procura por circuitos em todos os vértices
   Retorno: Vetor booleano com o resultado da busca de circuitos para cada vértice */
bool * Grafo:: circuitos(){
    bool *Circuitos = new bool [V];
    int v;
    for (v = 0; v < V; v++)
      Circuitos[v] = false;
    for (v = 0; v < V; v++)
      Circuitos[v] = circuito(v);
    return Circuitos;
  }

/* compConexas(): Computa o número de compomentes conexos do grafo. Espera a entrada de um vetor de tamanho V (nº de vértices do grafo). Retorna no vetor o tamanho de cada componente conexo 
   Parâmetros:
   int
    *tamCon: Vetor de tamanho N a ser passado para que se possa marcar o tamanho do caminho de cada componente
   Retorno: Nº de componentes conexas do grafo */
int Grafo:: compConexas(int *tamCon){
  bool *marked = new bool[V];
  int v, comp = 0, tamC = 0;
  for (v = 0; v < V; v++){
    marked[v] = false;
    tamCon[v] = 0;
  }
  for (v = 0; v < V; v++)
    if (!marked[v]){
      comp++;
      dfsR(v, marked, &tamC);
      tamCon[v] = tamC;
      tamC = 0;
    }
  delete [] marked;
  return comp;
}

/* caminhoMaisCurto(): Retorna o caminho mais curto para se chegar a qualquer vértice a partir de V
   Parâmetros:
   int
    v: Vértice inicial a partir do qual se desenvolve o caminho
   Retorno: Vetor com todos os vértices predessessores marcados.
   Exemplo: Seja um grafo de 10 posições com um único caminho possível (apenas para simplificar o exemplo): 4->2->1->7
    Se desejamos o caminho mais curto a partir do 4 (caminhoMaisCurto(4)), teremos o vetor:
    
   índice             : + 0+ 1+ 2+ 3+ 4+ 5+ 6+ 7+ 8+ 9+
   vértice predessesor: |-1| 2| 4|-1| 4|-1|-1| 1|-1|-1|
                        +--+--+--+--+--+--+--+--+--+--+
   E então reconstituir o caminho inverso, bastando inverter novamente a ordem para encontrar o caminho desejado.
   No exemplo, partindo do índice 7, encontramos o vértice 1; do índice 1, encontramos o vértice 2; do índice 2, encontramos o vértice 4; e do
   índice 4, encontramos o vértice 4 novamente, o que indica que acabou o caminho inverso.
   Temos assim o caminho inverso: 7->1->2->4 reconstituido 
   Podemos fazer uma função para soltar um vetor ou uma lista apenas com o caminho reconstituido, ou contar os vértices entre 1 e outro */
int * Grafo:: caminhoMaisCurto(int v){
  // Vetor de predessessores
  int *pred = new int[V];
  Fila<int> fila;
  int i, j, u, w;
  Adjacencia *p;
  // inicialização do vetor predessessor
  for (i = 0; i < V; i++)
    pred[i] = -1;
  pred[v] = v; // acabou o caminho inverso
  fila.insere(v);
  while (!fila.vazia()){
    u = fila.remove();
    for (p = adj[u].cab; p != NULL; p = p->prox){
      w = p->v;
      if (pred[w] == -1){
	pred[w] = u;
	fila.insere(w);
      }
    }
  }
  return pred;
}

palavra Grafo:: devolve(int v){
  return adj[v].p;
}
