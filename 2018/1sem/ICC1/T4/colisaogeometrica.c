#include <stdio.h>
#include <stdlib.h>
/* Programa : Colisão Geométrica (colisaogeometrica.c)
   Descrição: Este programa verifica a colisão entre dois planos, ou entre um plano e uma reta,
              verificando a existência de absurdo em uma das linhas do sistema (2 ou 3 linhas, 4 equações)
   Autor: Atenágoras Souza Silva (#USP: 5447262)
   Data : 08-19/06/2018
   Fluxo do Programa:
     - Leitura dos tipos geométricos (reta ou plano, seguido de plano)
     - Alocação de Matriz para o sistema, bem como armazenamento das equações nas linhas
     - Algoritmo de Escalonamento Recursivo
     - Verificação de Colisão por absurdo
     - Impressão de resultado
*/
typedef struct TimMaia{
  int num; // rumerador
  int den; // denominador
} racional;

racional** aloca_matriz(int L, int C){
  racional** m;
  int i;
  m = malloc( L*sizeof(racional*) ); //aloca espaço para L ponteiros/vetores de int (int*)
  for (i = 0; i < L; i++)
    // aloca espaço para C inteiros (int) em cada vetor m[i]. São L vetores
    m[i] = malloc( C*sizeof(racional) );
  return m;
}

/* Lê Matriz por partes.
   A ordem de leitura da Matriz é, primeiro, uma reta ou plano, depois um plano.
   Assim, a matriz com o sistema para detectar a colisão não será lido todo de uma vez
   Na primeira leitura de Matriz, obviamente, a linha inicial será zero, e as linhas finais
   serão, respectivamente, 0 para plano e 1 para reta.
   Na leitura do outro plano, a linha inicial é 2, e a final é 3 (4ª linha).
   Em todas as situações, o número de colunas lido é C, pois num sistema com 4 parâmetros,
   C = 4 (a ser lido do teclado) não vai variar.
   - Parâmetros:
     M : Matriz que recebe o sistema de planos ou reta e plano para verificar a colisão
     li: Linha inicial a ser lida (expicação acima)
     lf: Linha final a ser lida (de 0 a Ne-1, explicação acima. Obs: Ne = Nº equações, lido na main())
     C : Nº de colunas */
void LeMatriz(racional **M, int li, const int lf, const int C){
  int i, j;
  for (i = li; i <= lf; i++) // lê a linha lf também!
    for (j = 0; j < C; j++)
      scanf("%d %d ", &M[i][j].num, &M[i][j].den);
}

// desaloca a memória utilizada pela matriz que teve memória alocada dinamicamente (heap)
void desaloca_matriz(int N, racional **M){
  int i;
  for (i = 0; i < N; i++)
    free(M[i]);
  free(M);
}

// Imprime a Matriz
void ImprimeMatriz(racional **M, int Ne, int Nc){
  int i, j;
  for (i = 0; i < Ne; i++){
    for (j = 0; j < Nc; j++)
      if (M[i][j].den == 1)
	printf("%d\t", M[i][j].num);
      else
	printf("%d/%d\t", M[i][j].num, M[i][j].den);
    printf("\n");
  }
}

/* troca linha i por linha j na matriz M.
   Parâmentros:
   i : número da linha pivô a ser trocada
   j : número da linha a se tornar pivô pela troca
   ci: primeira coluna da matriz para fazer comparação
   Ne: número de linhas
   Nc: número de colunas por linha
*/
void TrocaLinha(racional **M, int i, int j, int ci, int Ne, int Nc){
  racional Vtroca[Nc];
  if ( (M[j][ci].num == 0) && (j < Ne) ){ // Se M[j][ci] == 0, tenta trocar linha i pela linha de baixo (j+1)
    j++;
    if ( M[j][ci].num == 0)
      return; // Se mesmo mesmo assim, M[j][ci] == 0, não é necessário fazer troca de linha
  }
  int k; // Índice para a coluna da matriz
  for (k = 0; k < Nc; k++)// Copia cada elemento racional k da linha i para o vetor de troca 
    Vtroca[k] = M[i][k];
  for (k = 0; k < Nc; k++){ 
    M[i][k] = M[j][k]; // Escreve a Linha j na Linha i
    M[j][k] = Vtroca[k]; // Escreve  Linha i, presente no Vtroca para a Linha j, completando a troca
  }
}

void CopiaVetor(racional* destino, racional* origem, int C){
  int i;
  for (i = 0; i < C; i++)
    destino[i] = origem[i];
}

// Calcula o MDC entre dois inteiros usando o algoritmo de euclides
int TuEsMDCdaMinhaVida(int a, int b){
  int divisor, dividendo, resto;
  if (a < 0)
    a *= -1;
  if (a < 0)
    b *= -1;
  if (a > b){
    divisor = a;
    dividendo = b;
  }
  else{
    divisor = b;
    dividendo = a;
  }
  resto = dividendo % divisor;
  while(resto){ // continua o looping se resto != 0
    dividendo = divisor;
    divisor = resto;
    resto = dividendo % divisor;
  }
  return divisor;
}

// Calcula o MMC entre a e b a partir do MDC usando a propriedade MMC(a,b) * MDC(a,b) = a*b
int MMC(int a, int b){
  // trabalha apenas com o módulo
  if (a < 0)
    a *= -1;
  if (b < 0)
    b *= -1;
  return a*b / TuEsMDCdaMinhaVida(a,b);
}

racional SIMPLIFICA(racional a){
  int mdc = TuEsMDCdaMinhaVida(a.num, a.den);
  racional r;
  r.num = a.num / mdc;
  r.den = a.den / mdc;
  if (r.den < 9)
    return r;
  else return a;
}

/* MenosRacional: Subtrai um número b de a (a - b)
   Parâmetros:
   a: minuendo, número a ser subtraido
   b: subtraendo, número a subtrair de a */
racional MenosRacional(racional a, racional b){
  /* DEN   : Denominador Comum para realizar a subtração entre racionais (obtido por MMC)
     a - b = (fatorA*a.num - fatorB*b.num) / DEN
     fatorA: fator que multiplica o numerador de a para fazer a subtração
     fatorB: fator qeu multiplica o numerador de b para fazer a subtração */
  int DEN, fatorA, fatorB;
  /* r : resultado
     rs: resultado simplificado, se rs.den < 9, exibí-lo */
  racional r, rs;
  DEN = MMC(a.den, b.den);
  fatorA = DEN / a.den;
  fatorB = DEN / b.den;
  r.num = fatorA*a.num - fatorB*b.num;
  r.den = DEN;
  rs = SIMPLIFICA(r);
  if (rs.den < 9) // Apenas retorna o resultado simplificado, caso o denominador não seja maior que 9
    return rs;
  else
    return r;
}

/* Zera a primeira coluna de cada linha abaixo da linha inicial utilizando esta como pivô.
   Antes, checa se é necessário ou possível fazê-lo.
   Parâmetros:
   pivo: Linha pivô
   Ne  : Número de equações (linhas)
   Nc  : Número de coeficientes (colunas)
   ci  : Coluna inicial  */
void ZeraColuna(racional** M, int pivo, int ci, int Ne, int Nc){
  /* Zerador: Matriz a ser pivotada
     fatzera: fator de multiplicação da matriz Zerador para usá-la como pivô para zerar as outras linhas
   */
  racional Zerador[Nc], fatzera; 
  CopiaVetor(Zerador, M[pivo], Nc);
  int numpivo, denpivo; // numerador e denominador da primeira coluna da linha pivô
  int i = 1, j;
  numpivo = Zerador[ci].num;
  denpivo = Zerador[ci].den;
  while ( pivo+i < Ne){
    if ( M[ pivo+i ][ci].num != 0 ){ // verifica se a 1ª coluna das linhas abaixo da pivô já é zero
      // calcula o fator para multiplicar a linha pivo (vetor Zerador)
      // isto é *pivo[ci] * (1/pivo[ci])
      fatzera.num = denpivo*M[ pivo+i ][ci].num;
      fatzera.den = numpivo*M[ pivo+i ][ci].den;
      // Altera linha Zerador (pivo) para que M[ pivo+i ] - Zerador, de fato, zere o 1º elemento de pivo+i
      for (j = 0; j < Nc - ci; j++ ){
	Zerador[ ci+j ].num *= fatzera.num;
	Zerador[ ci+j ].den *= fatzera.den;
      }
      // realiza o pivotamento para zerar o 1º elemento da linha pivo+i, abaixo da linha pivo
      for (j = 0; j < Nc - ci; j++ )
	M[ pivo+i ][ ci+j ] = MenosRacional(M[ pivo+i][ ci+j ], Zerador[ ci+j ]);
    }
    CopiaVetor(Zerador, M[pivo], Nc); // Zerador 
    i++;
  }
}

/* escalona(): escalona recursivamente
   A idéia é que a cada chamada recursiva, li e ci sejam incrementados, recortando a matriz
   Parâmetros:
   li: linha inicial da matriz
   ci: coluna inicial da matriz */
int escalona(racional** Matriz, int li, int ci, int Ne, int Nc, int flag){
  int i = 0;
  /* Caso base para retorno
     Se a matriz virar uma matriz linha, então retorna
     Ou, se o 1º elemento da matriz for um coeficiente c
   */
  if ( (li == Ne-1) || (ci == Nc - 2) ){
    flag = 1;
    return flag;
  }
  if ( Matriz[li][ci].num == 0 ){ // verifica necessidade de trocar linhas
    TrocaLinha(Matriz, li, li+i, ci, Ne, Nc);
  }
  ZeraColuna(Matriz, li, ci, Ne, Nc);
  escalona(Matriz, li+1, ci+1, Ne, Nc, flag);
  return flag;
}

/* TheClash(): Procura por absurdo em cada linha do sistema para detectar ou não colisão
   Não ocorre colisão se houver absurdo (0x + 0y +0z +d, d != 0).
   Se houver colisão, retorna 1, senão, retorna 0.
   Parâmetros:
   M : Matriz com o sistema
   Ne: Número de equações */
int TheClash(racional **M, int Ne){
  int i = 0, flag = 1;
  while ( flag && (i < Ne) ){
    if ( (M[i][0].num == 0) && (M[i][1].num == 0) && (M[i][2].num == 0) && (M[i][3].num != 0) )
      flag = 0;
    i++;
  }
  return flag;
}

int main(){
  char geotipo; // Leitura do tipo de objeto geométrico: 'r' para reta e 'p' para plano
  /* Ne: Número de equações (linhas da matriz) (2 ou 3)
     Nc: Número de coeficientes na equação (4, pois em todos os casos, é a equação geral do plano)
         Uma reta é intersecção de dois planos
     colisao: flag para apontar a colisão entre os elementos geométricos. 1 - colisão, 0 - não colisão
     li     : Linha inicial para chamar LeMatriz()
     lf     : Linha final para chamar LeMatriz()
     lip    : Linha inicial do plano a ser lido depois
     i,j    : Índices
   */
  int Ne, Nc, colisao, li = 0, lf, lip, i, j;
  scanf("%d %d ", &Ne, &Nc);
  scanf("%c ", &geotipo);
  racional** Planos; // Matriz que recebe as equações dos planos
  Planos = aloca_matriz(Ne, Nc);
  switch(geotipo){ // seta as variáveis que controlarão a leitura da matriz
  case 'r':
    lf = 1;
    break;
  case 'p': lf = 0;
    break;
  default: lf = 0;
  }
  LeMatriz(Planos, li, lf, Nc);
  scanf("%c ", &geotipo); // apesar da leitura, o geotipo nessa segunda leitura é sempre um plano
  lip = lf+1;
  LeMatriz(Planos, lip, lip, Nc); // quando é plano, li == lc, pois só uma linha é lida
  escalona(Planos, 0, 0, Ne, Nc, 0);
  colisao = TheClash(Planos, Ne);
  // imprimir sim ou não
  if (colisao)
    printf("sim\n");
  else
    printf("nao\n");
  for (i = 0; i < Ne; i++)
    for (j = 0; j < Nc; j++)
      Planos[i][j] = SIMPLIFICA(Planos[i][j]); // Modificado para simplificar apenas se denominador < 9
  // imprimir versão final da matriz do sistema
  ImprimeMatriz(Planos, Ne, Nc);
  desaloca_matriz(Ne, Planos);
  return 0;
}
