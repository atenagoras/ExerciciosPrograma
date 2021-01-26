#include<stdio.h>
#include<stdlib.h>
#define MAX 9

/* Programa : BalRec.c
   Autor    : Atenágoras Souza Silva (#USP: 5447262)
   Data     : 20-30/04/2018
   Descrição: Este programa calcula o balanceamento de recursos para dois jogadores em um mapa
              de jogo de RTS (Real Time Strategy), e diz qual o valor de exploração de ambos,
	      quem tem vantagem, ou se o mapa está balancado
   Fluxo do programa:
     - Leitura do mapa, posição da base dos jogadores, número de recursos, e posição deles no mapa
     - Cálculos:
       + Cálculo de células transponíveis P
       + Cálculo do Valor de Exploração E1 e E2 dos jogadores 1 e 2, respectivamente
         % Uso do algoritmo flood-fill entre a base dos jogadores e os recursos para cálculo da
	   cobertura do mapa Ejr (jr == jogador -> base) utilizado para o cálculo do valor de
	   exploração de acordo com a fórmula do enunciado do trabalho 3
       + Impressão dos Valores de Exploração E1 e E2
       + Comparação de Balanceamento e impressão da mensagem referente à vantagem de um dos
         jogadores, ou equilíbrio       
*/

// Calcula valor absoluto de um número do tipo double. Apenas não desejei usar fabs() em math.h
double ABS(double E){
  if (E < 0)
    E = -1*E;
  return E;
}

// ImprimeMapa() está comementada para uso livre dos monitores e professor. Descomente, se desejar usar.
/* void ImprimeMapa(int M[][MAX]){ */
/*   int i, j; */
/*  for (i = 0; i < MAX; i++){ */
/*     for (j = 0; j < MAX; j++) */
/*       printf("%d ", M[i][j]); */
/*     printf("\n"); */
/*  } */
/* } */

/* CopiaMatriz():  Copia matriz de origem para o destino
   Parâmetros:
    - O: Matriz de origem
    - D: Matriz de destino
    - L: #linhas
    - C: #colunas (constante)
    Usada para copiar a matriz do mapa
*/
void CopiaMatriz(int L, const int C, int O[][C], int D[][C]){
  int i, j;
  for (i = 0; i < L; i++)
    for (j = 0; j < C; j++)
      D[i][j] = O[i][j];
}

/* LeMatriz(): Função genérica para leitura de matriz do tipo inteiro
   Parâmetros:
   - L: #linhas da matriz
   - C: #colunas da matriz
   - M: Ponteiro de ponteiros para elementos da matriz (fazer casting, ou criar ponteiro para leitura)
*/
void LeMatriz(const int L, const int C, int **M){
  int i, j;
  for (i = 0; i < L; i++)
    for (j = 0; j < C; j++)
      scanf("%d", &M[i][j]);
}

// aloca matriz de L linhas e C colunas na memória Heap
int** aloca_matriz(int L, int C){
  int** m, i;
  m = malloc( L*sizeof(int*) ); //aloca espaço para L ponteiros/vetores de int (int*)
  for (i = 0; i < L; i++)
    m[i] = malloc( C*sizeof(int) ); // aloca espaço para C inteiros (int) em cada vetor m[i]. São L vetores
  return m;
}

// desaloca a memória utilizada pela matriz que teve memória alocada dinamicamente (heap)
void desaloca_matriz(int N, int **M){
  int i;
  for (i = 0; i < N; i++)
    free(M[i]);
  free(M);
}

// Lê vetor de N posições 
void LeVetor(int N, int v[]){
  int i;
  for (i = 0; i < N; i++)
    scanf("%d", &v[i]);
}

// Conta o número de zeros de uma matriz inteira (usada para calcular P)
int CountZero(const int L, const int C, int M[][C]){
  int i, j, contador = 0;
  for (i = 0; i < L; i++)
    for (j = 0; j < C; j++)
      if ( M[i][j] == 0 )
	contador++;
  return contador;
}

/* flood_fill():
  Algoritmo Flood Fill Modificado para ser interrompido quando o jogador chegar até o recurso
  Variáveis e argumentos:
   M      : matriz com o mapa Mapa;
   xj e yj: Posições x e y do jogador
   xr e yr: Posições x e y do recurso
   passos : Número de passos para chamar a função. Tal número será retornado a função a cada chamada
   *flag  : Flag para indicar a função para retornar sem executar nenhum processamento a não ser
            retornar, até que todas as chamadas recorrentes saima da pilha.
	    Desta maneira, em mapas mais abertos (casos 4, 6-10), a função não vai continuar o
	    algoritmo flood-fill nem fazer contagem de passos mesmo depois que o jogador encontrar
	    o recurso.
*/
int flood_fill(int M[][MAX], int xj, int yj, int xr, int yr, int passos, int* flag){
  if ( flag ){
      if (M[yj][xj] != 0) // Caso base 1. Se M[x][y] != 0, não faz nada
	return passos;
      M[yj][xj] = 2; // Substitui 0 por 2
      passos++;
      
      /* Caso base 2: Necessário interromper completamente o algoritmo e desempilhar todas as
	 chamadas da função */
      if ( (yj == yr) && (xj == xr) ){
	*flag = 1; /* Se *flag == 1, não haverá mais chamadas recorrentes, e todas as instâncias
		      sairão da pilha */
	return passos;
      }
      
      /* Controle das chamadas recorrentes: Não pode sair dos domínios do mapa, nem entrar
	 nas funções novamente quando *flag == 1
       */
      if ( (yj < MAX-1) && !(*flag) )
	passos = flood_fill(M, xj, yj+1, xr, yr, passos, flag); // Sul
      if ( (yj > 0) && !(*flag) )
	passos = flood_fill(M, xj, yj-1, xr, yr, passos, flag); // Norte
      if ( (xj > 0) && !(*flag) )
	passos = flood_fill(M, xj-1, yj, xr, yr, passos, flag); // Oeste
      if ( (xj < MAX-1) && !(*flag) )
	passos = flood_fill(M, xj+1, yj, xr, yr, passos, flag); // Leste
  }
  return passos;
}
/* Explora(): Calcula o Valor de Exploração
   Valores e argumentos:
    posj  : Vetor com a posição do jogador. posj[0] = xj, posj[1] = yj;
    nRec  : Número de recursos no mapa;
    posRec: Matriz com a posição dos recursos no mapa.
            posRec[0] == posição do primeiro recurso, posRec[nRec-1] == posição do nRec-ésimo
	    posRec[i][0] == xr_i, posRec[i][1] == yr_i
    map   : Matriz com o mapa
    P     : Número de Células Transponíveis (representadas por 0 no mapa)
*/
double Explora(int posj[], int nRec, int** posRec, int map[][MAX], int P){
  /* Ejr   == número de passos do jogador até um recurso (cobertura do mapa até encontrar o recurso)
     E     == Valor de Exploração
     copia == cópia do mapa
     flag  == flag que alerta a função flood_fill sobre a necessidade de retornar sem executar o algoritmo,
              caso o recurso seja encontrado
   */
  int i, Ejr = 0, copia[MAX][MAX], flag=0;
  CopiaMatriz(MAX, MAX, map, copia);
  double E = 0;
  for (i = 0; i < nRec; i++){
    Ejr = flood_fill(copia, posj[1], posj[0], posRec[i][1], posRec[i][0], Ejr, &flag);
    E += Ejr / (double) P; // Cálculo parcial do valor de exploração
    Ejr = 0;
    CopiaMatriz(MAX, MAX, map, copia);
    flag = 0;
  }
  // Cálculo final do Valor de Exploração
  E = E / (double) nRec; // N = nRec + 1 (base do jogador), logo N-1 = nRec
  return E;
}

/* Balanco(): Compara balanço entre jogadores
   Parâmetros:
   E1        : Valor de exploração do jogador 1
   E2        : Valor de exploração do jogador 2
 */
void Balanco(double E1, double E2){
  if ( ABS( E1 - E2) <= 0.001 )
    printf("O mapa eh balanceado\n");
  else if (E1 < E2)
    printf("O jogador 1 possui vantagem\n");
  else
    printf("O jogador 2 possui vantagem\n");
}

int main(){
  /* map   : Matriz que recebe o mapa inserido pelo usuário
     copia : Cópia do mapa para ser passada na função
     *pmap : Ponteiro para matriz map. Mais fácil para compartilhar mesma função com 
             matriz e ponteiro duplo
   */
  int map[MAX][MAX], copia[MAX][MAX], *pmap[9], i;
  // posição dos jogadores
  int pos1[2], pos2[2]; // posj[0] == yj, posj[1] == xj
  // Matriz com a posição dos recursos
  int** posRec, nRec; // posRec[][0] == yr, pos[][1] == xr
  int P;
  double E1, E2;
  // Armazenando os endereços das linhas de map em pmap, de modo a inserí-la na função de leitura da matriz
  for (i = 0; i < MAX; i++)
    pmap[i] = map[i];
  LeMatriz(MAX, MAX, pmap); // Lê Mapa
  P = CountZero(MAX, MAX, map); // Conta casas transponíveis
  CopiaMatriz(MAX, MAX, map, copia);
  // Leitura da posiçao dos jogadores
  LeVetor(2, pos1);
  LeVetor(2, pos2);
  // Leitura do número de recursos e posição dos mesmos
  scanf("%d",&nRec);
  posRec = aloca_matriz(nRec, 2);
  LeMatriz(nRec, 2, posRec);
  // Cálculo dos valores de Exploração
  E1 = Explora(pos1, nRec, posRec, copia, P); // Valor de Exploração para o Jogador 1
  CopiaMatriz(MAX, MAX, map, copia);
  E2 = Explora(pos2, nRec, posRec, copia, P); // Valor de Exploração para o Jogador 2
  // Impressão dos Valores de Exploração
  printf("%lf\n", E1);
  printf("%lf\n", E2);
  // Impressão do Balanço
  Balanco(E1, E2);
  free(posRec);
  return 0;
}
