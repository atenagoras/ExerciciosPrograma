#include <stdio.h>
#include <string.h>
#include "experimento.h"
#include <stdlib.h>

void printMedidas(char *nome, medidas *M){
  strcpy(M->nomeArq, nome);
  char saida[] = "Medidas.csv";
  FILE *f = fopen(saida, "r");
  char cabeca[] = "Arquivo,Vértices,Arestas,Mesma Ordem de Grandeza,Densidade (A/V²),Média de Graus em um vértice\n";
  char dados[1024];
  sprintf(dados, "\"%s\",%d,%d,\"%s\",%f,%f\n", M->nomeArq, M->vertices, M->arestas, M->mesmaOrdGrandeza, M->den, M->mediaGraus);
  if (f){
    fclose(f);
    f = fopen(saida, "a");
    fprintf(f, "%s",dados);
  }
  else {
    f = fopen(saida, "w");
    fprintf(f, "%s", cabeca);
    fprintf(f, "%s", dados);
  }
  fclose(f);
}

medidas Medidas(FILE *fp, Grafo *g){
  medidas M;
  fprintf(fp, "Medidas\n");
  fprintf(fp, "Número de Vértices: %d\n", g->V);
  fprintf(fp, "Número de Arestas: %d\n", g->A);
  M.vertices = g->V;
  M.arestas = g->A;
  char Arestas[256], VerticeQuadrado[256];
  sprintf(Arestas, "%d", g->A);
  sprintf(VerticeQuadrado, "%d", g->V * g->V);
  int tamArestas = strlen(Arestas);
  int tamVquad = strlen(VerticeQuadrado);
  if (tamArestas == tamVquad){
    fprintf(fp, "Arestas e Vértices² possuem mesma ordem de grandeza.\n");
    strcpy(M.mesmaOrdGrandeza, "Sim");
  }
  else {
    fprintf(fp, "Arestas tem ordem de grandeza inferior a Vértices².\n");
    strcpy(M.mesmaOrdGrandeza, "Não");
  }
  float den = (float) g->A / (g->V * g->V);
  fprintf(fp, "Densidade (A/V²): %f\n", den);
  M.den = den;
  int somaGraus = 0;
  int v;
  for (v = 0; v < g->V; v++)
    somaGraus += g->adj[v].grau;
  float mediaGraus = (float) somaGraus / g->V;
  fprintf(fp, "Nº médio de graus por vértice: %f\n", mediaGraus);
  fprintf(fp,"\n");
  M.mediaGraus = mediaGraus;
  return M;
}

int Maior(int *v, int N){
  int maior, i;
  maior = v[0];
  for (i = 0; i < N; i++)
    if (v[i] > maior)
      maior = v[i];
  return maior;
}

int Menor(int *v, int N){
  int menor = v[0], i = 0;
  while (menor == 0 || i < N){
    menor = v[i];
    i++;
  }
  for (i = i; i < N; i++)
    if (v[i] !=0 &&  v[i] < menor)
      menor = v[i];
  return menor;
}

void printConexidade(char *nome, conexidade *C){
  strcpy(C->nomeArq, nome);
  char saida[] = "Conexidade.csv";
  FILE *f = fopen(saida, "r");
  char cabeca[] = "Arquivo,Componentes,Maior Componente,Menor Componente,Média de Componentes por vértice\n";
  char dados[1024];
  sprintf(dados, "\"%s\",%d,%d,%d,%f\n",C->nomeArq, C->componentes, C->maior, C->menor, C->mediaComp);
  if (f){
    fclose(f);
    f = fopen(saida, "a");
    fprintf(f, "%s", dados);
  }
  else {
    f = fopen(saida, "w");
    fprintf(f, "%s", cabeca);
    fprintf(f, "%s", dados);
  }
  fclose(f);
}

conexidade Conexidade(FILE *fp, Grafo *g){
  fprintf(fp, "Conexidade\n");
  int *tam = new int[g->V];
  int comp;
  conexidade C;
  comp = g->compConexas(tam);
  C.componentes = comp;
  if (comp == 0)
    fprintf(fp, "Grafo sem conexidade.\n");
  else
    if (comp == 1){
      fprintf(fp, "Grafo conexo, %d componente.\n", comp);
  }
  else
    fprintf(fp, "Grafo com %d componentes.\n", comp);
  int Nnaozero = 0, maior, menor, somaTam = 0, i;
  for (i = 0; i < g->V; i++)
    if (tam[i] != 0){
      somaTam += tam[i];
      Nnaozero++;
    }
  float Media = (float) somaTam / Nnaozero;
  C.mediaComp = Media;
  fprintf(fp, "Tamanho Médio das Componentes: %f\n", Media);
  maior = Maior(tam, g->V);
  C.maior = maior;
  menor = Menor(tam, g->V);
  C.menor = menor;
  fprintf(fp, "Maior tamanho de componente: %d\n", maior);
  fprintf(fp, "Menor tamanho de componente: %d\n", menor);
  delete [] tam;
  fprintf(fp, "\n");
  return C;
}

int sorteio(int div){
  int r = rand() % div;
  return r;
}

/* distancia2Palavras(): calcula a distância entre duas palavras (nº de palavras entre elas) */
int distancia2Palavras(Grafo *g, int v1, int v2){
  int *caminho = g->caminhoMaisCurto(v1), v = v2, i = 0;
  if (caminho[v] != -1)
    while (caminho[v] != v1){
      i++;
      v = caminho[v];
    }
  delete [] caminho;
  return i;
}

/* distanciaMediaEntreDuasPalavras(): Calcula a distância média entre duas palavras. Para tal, sorteia o Nº de Vértices / 2 duas palavras e calcula a distância mínima entre elas */
float distanciaMediaEntreDuasPalavras(Grafo *g){
  int N = g->V / 2;
  int i, dist = 0, soma = 0, cont = 0;
  int v1 = 0, v2 = 0;
  for (i = 0; i < N; i++){
    while(v1 == v2){
      v1 = sorteio(g->V);
      v2 = sorteio(g->V);
    }
    dist = distancia2Palavras(g, v1, v2);
    if (dist != -1){
      cont++;
      soma += dist;
    }
    v1 = v2 = 0;
  }
  float media = (float) soma / cont;
  return media;
}

void printcaminhosCiclos(char *nome, caminhosCiclos *Ca){
  strcpy(Ca->nomeArq, nome);
  char saida[] = "caminhosCiclos.csv";
  FILE *f = fopen(saida, "r");
  char cabeca[] = "Arquivo,Distância Média entre duas palavras\n";
  char dados[1024];
  sprintf(dados, "\"%s\",%f\n", Ca->nomeArq, Ca->distMedia);
  if (f){
    fclose(f);
    f = fopen(saida, "a");
    fprintf(f, "%s", dados);
  }
  else {
    f = fopen(saida, "w");
    fprintf(f, "%s", cabeca);
    fprintf(f, "%s", dados);
  }
  fclose(f);
}

caminhosCiclos CaminhosCiclos(FILE *fp, Grafo *g){
  fprintf(fp, "Caminhos e Ciclos\n");
  int s1 = sorteio(g->V), s2 = sorteio(g->V);
  fprintf(fp, "Palavras Sorteadas:\n");
  palavra p1 = g->devolve(s1), p2 = g->devolve(s2);
  fprintf(fp, "palavra 1: %s vértice %d\n", p1.String, s1);
  fprintf(fp, "palavra 2: %s vértice %d\n", p2.String, s2);
  int *v1 = g->caminhoMaisCurto(s1), *v2 = g->caminhoMaisCurto(s2);
  if (v1[s2] > -1)
    fprintf(fp, "Existe caminho da palavra 1 à palavra 2.\n");
  else
    fprintf(fp, "Não existe caminho da palavra 1 à palavra 2.\n");
  if (v2[s1] > -1)
    fprintf(fp, "Existe caminho da palavra 2 à palavra 1.\n");
  else
    fprintf(fp, "Não existe caminho da palavra 2 à palavra 1.\n");
  delete [] v1;
  delete [] v2;
  bool b1 = g->circuito(s1), b2 = g->circuito(s2);
  if (b1)
    fprintf(fp, "A palavra 1 inicia um circuito.\n");
  else
    fprintf(fp, "A palavra 1 não inicia um circuito.\n");
  if (b2)
    fprintf(fp, "A palavra 2 inicia um circuito.\n");
  else
    fprintf(fp, "A palavra 2 não inicia um circuito.\n");
  float distMedia = distanciaMediaEntreDuasPalavras(g);
  fprintf(fp, "A distância média entre duas palavras no grafo é %e.\n", distMedia);
  caminhosCiclos Ca;
  Ca.distMedia = distMedia;
  return Ca;
}

void Experimentos(char *nomeArq, AB *tso){
  char saida[256];
  strcpy(saida, nomeArq);
  strcat(saida, "-GrafoAnalise");
  FILE *Saida = fopen(saida, "w");
  // Grafo G = Grafo(tso);
  Grafo G(tso);
  G.vizinhas(); // Gera as arestas ao procurar palavras vizinhas
  medidas M = Medidas(Saida, &G);
  printMedidas(nomeArq, &M);
  conexidade C = Conexidade(Saida, &G);
  printConexidade(nomeArq, &C);
  caminhosCiclos Ca = CaminhosCiclos(Saida, &G);
  printcaminhosCiclos(nomeArq, &Ca);
  fclose(Saida);
}
