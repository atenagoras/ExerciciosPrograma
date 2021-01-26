#include<stdio.h>
#include<math.h>
/*
  Programa : recomenda.c
  Autor    : Atenágoras Souza Silva (#USP: 5447262)
  Data     : 20-30/04/2018
  Descrição: Este programa prediz a nota que um usuário daria a um filme que ainda não assistiu
             Baseado na similaridade dos demais usuários caso estes tenham assistido ao filme
      Fluxo do programa:
        - Leitura de #usuários, #ítens e limiar t
	- Preencimento de matriz com as notas dos usuários
	- Cálculos
	  + Matriz Similaridade SIM
	  + Vetor Nmédias, com as médias dos filmes para cada usuário
	  + Matriz Variança S
	  + Notas preditas
*/

// Zera uma Matriz double
// Ex: Zera( (double *) M, Nlinhas, Ncolunas );
void Zera(double *M, int L, int C){
  int i, j;
  for (i=0;i<L;i++)
    for (j=0;j<C;j++)
      M[C*i+j] = 0;/* Em C, o compilador precisa saber o tamanho de cada linha ao receber a matriz.
		      Como o casting da Matriz está como ponteiro, para fazer o looping como se fosse
		      uma matriz, multipliquei a linha pelo número de colunas, pois cada linha é um bloco
		      contendo o número de colunas.
		      Isso foi feito para burlar a necessidade de passar o tamanho da linha explicitamente
		      à função.
		      Ex: */
  /*
    Seja L = 2, C = 2;
    M pode ser representado (abstratamente) na memória como:
        0   1
      +---+---+
    0 |   |   |
      +---+---+
    1 |   |   |
      +---+---+
      Entretanto, como M foi passado como ponteiro simples, temos de fazer contas para acessar os elementos
      da matriz:
      Assim, M[l][c] == M[C*l+c].
      No caso da matriz acima, para acessar o elemento M[1][0], com C e L iguais 2, l=1 e c=0, fazemos 
      M[2*1+0] = M[2], que corresponde ao terceiro elemento do 'vetor' M, com esperado.
   */
}

// Imprime notas preditas
// Ex: ImprimeNotas( (double *), M, Nusuarios, Nitens );
void ImprimeNotas(double* Np, int N, int I){
  int n, i, cont=0; // Se cont permanecer zero em uma linha, a função não retornará linha vazia
  for (n=0; n<N; n++){
    for (i = 0 ; i < I; i++)
      if (Np[ I*n +i] > 0){
	printf("%.2lf ", Np[ I*n +i]); // Ver explicação nos comentários para função Zera()
	cont = 1;
      }
      else if (Np[ I*n +i] < 0.00){
	printf("DI ");
	cont = 1;
      }
    if ( cont ){
      printf("\n"); // pula linha após imprimir todas as notas preditas em uma mesma linha
      cont = 0;
    }
  }
}

// Calcula cosseno, a similaridade conforme a definição do trabalho
// Ex: SIM[n][n+1] = COS( (int *) u , Nitens, n );
// retorna cos(u_n+1, u_n)
double COS(int *u, int I, int n, int m){
  double U=0, V=0, denominador, escalar=0, coss;/* coss = cosseno.
						   Para não confundir com cos(), definida na math.h  */
  int i;
  for (i=0; i<I; i++)
    // Cálculos para a posição da matriz atuando como vetor na função Zera()
    U = U + u[ I*n +i ]*u[ I*n +i ]; // U + u[n][i]*u[n][i]
  for ( i = 0; i < I; i++)
    V = V + u[ I*m +i ]*u[ I*m +i ]; // U + u[n+1][i]*u[n+1][i]
  U = sqrt(U);
  V = sqrt(V);
  denominador = U*V;
  if (denominador == 0) // A lógica do programa não considerará correlação se denominador = 0
    coss = 0;
  else{
    for( i=0; i<I; i++ )
      escalar = escalar + u[ I*n +i ]*u[ I*m +i ];
    coss = escalar/denominador;
  }
  return coss;
}

// Calcula a Similaridade entre os usuários do sistema de filmes
// Ex: Similaridade ( (double *) SIM, (int *) u, nItens, Nusuarios);
void Similaridade(double* SIM, int* u, int N, int I){
  int n, m;
  for ( n=0; n<N ; n++) // Diagonal principal é igual a 1, pois un.un/(|un|*|un|) = 1
    SIM[ N*n +n ] = 1; // SIM[n][n]
  for (n = 0; n<N; n++)
    for (m = n+1 ; m<N ; m++){
      SIM[ N*n+ m ] = COS( (int*) u, I, n, m);/* SIM[n][m]
						 O cast (int*) é para transformar a matriz em vetor de string
						 Isto é uma forma de não ter de passar o tamanho da matriz
						 diretamente
					      */
      SIM[ N*m +n ] = SIM[ N*n +m ]; /* SIM[m][n] = SIM[n][m]
					embora repetitivo, facilita as contas */
    }
}

// Lê a nota dos usuários para os filmes
// Ex: Le_u( (int *) u, Nusuarios, Nitens );
void Le_u(int * u, int N, int I){
  int n, i;
  for(n=0;n<N;n++)
    for(i=0;i<I;i++)
      scanf("%d", &u[I*n+i]); // Seria o mesmo que u[n][i]
}

// Calcula as Notas Médias de cada usuário para os filmes,
// Atribuindo-as ao primeiro vetor chamado no argumento da função
// Ex: CalcMedias(Medias, (int *) u, Nusuarios, Nitens )
void CalcMedias(double Nmedias[], int * u, int N, int I ){
  int cont=0;
  double Media=0;
  int n, i;
  for ( n = 0; n < N; n++){
    for ( i = 0; i < I; i++)
      if ( *(u +I*n +i) != 0 ){
	Media  = Media + *(u +I*n +i); // u[n][i]
	cont++;
      }
    if (cont !=0){ // Evita divisão por 0, no caso de todas as notas de um usuário for 0
      Nmedias[n] = Media / cont;
      cont = 0;
      Media = 0;
    }
    else
      Nmedias[n] = 0;
  }
}

/* Esta função calcula a variacão em sima de uma determinada nota
   Ex: CalcVariacao( (double *) S, VetorMedias, (int *) u, N, I )
   Manipula a matriz S[N][I] para que ela tenha as variações para todos os 
   usuários em todos os ítens */
void CalcVariacao(double* S, double Nmedias[], int* u, int N, int I){
  int n, i;
  for (n = 0; n < N; n++)
    for(i = 0; i < I; i++)
      if ( u[ I*n +i] != 0 )
	S[ I*n +i] = u[ I*n +i] - Nmedias[n];
      else
	S[ I*n +i] = -6; /* Flag para impedir que a nota de um usuário parecido e que também não tenha assistido 
			    atrapalhe os resultados da predição de nota
			    Será tratada nas funções que calculam a nota predita
			 */
}

/* AuxPrediz auxilia PredizNota
   Ela calcula, de fato, o termo media_notas(u_n) + Somatoria_u_m( SIM[n[m]*S[m][i] )/ Somatoria_u_m( |SIM[n][m]| )
   e retorna o valor para Np[n][i] (que é, na minha notação, Nota(u, i) )
 */
double AuxPrediz( double media, double* S, double* SIM, int i, int n, int N, int I, double t){
  int m;
  double aux = 0, denominador = 0;
  // Varre à esquerda da coluna n da linha n da matriz SIM, e soma os resultados parciais
  for (m = n-1; m > -1; m--) // Esperado que nem entre no looping, se n = 0
    if ( S[I*m +i] != -6 ) /* Impedindo que usário parecido, mas que também não assistiu ao filme 
			      seja contabilizado */
      if ( SIM[ N*n + m] >= t ){ /* Só faz a conta, se SIM[n][m] > t 
				    Se não entrar no looping nenhuma vez, varrendo à esquerda e à direita 
				    na linha (segundo looping, com incremento positivo de m), Np[n][i] = -1
				 */
	aux += SIM[ N*n +m]*S[I*m +i];
	denominador += SIM[ N*n +m];
      }
  
  // Varre à direita da coluna n da linha n da matriz SIM, e continua a somar os resultados parciais
  for (m = n+1; m < N; m++)
    if ( S[I*m +i] != -6 )
      if ( SIM[ N*n + m] >= t ){
	aux += SIM[ N*n +m]*S[I*m +i];
	denominador += fabs( SIM[ N*n +m]) ;
      }
  if ( denominador == 0 ) /* denominador == 0, se não houver nenhum usuário cuja Similaridade
			     com o usuáio para o qual deseja-se calcular a nota predita 
			     ultrapasse o limiar
			  */
    return -1;
  else
    return media + aux/denominador;
}

/*
  Esta função, com a ajuda de AuxPrediz, calcula a Nota Predita para cada usuário para cada filme
  não assistido
  Ex: PredizNota( (double *) MatrizNotaPredita, (double *) Variacao, Medias, (double *) NotasInseridasUsuario, Nusuarios, Nitens, limiarT)
  Esta matriz Manipula a MatrizNotaPredita para que ela tenha-a todas as notas preditas calculadas para cada usuário e ítem
*/
void PredizNota(double* Np, double* S, double * SIM, double Nmedias[], int* u, int N, int I, double t){
  int n, i;
  for (n = 0; n < N; n++)
    for(i = 0; i < I ; i++)
      if ( u[ I*n +i] == 0){
	Np[ I*n +i] = AuxPrediz(Nmedias[n], (double *) S, (double *) SIM, i, n, N, I, t) ;
      }
}

int main(int argc, char** argv){
  // 1) Declaração e atribuição das variáveis para começar o programa
  double t;
  int I, N; /* I: Número de filmes ( 4 <= N <= 15 )
	       N: Número de usuários ( 4 <= I <= 15 )
	       t: limiar de similaridade ( 0.5 <= t <= 1.0 ), ou seja, SIMu_i,u_j >= t
	    */

  // variáveis booleanas para testes lógicos. Facilita debugar expressões longas nos whiles ou ifs
  int bN = 1, bI = 1, bt = 1;
  
  // Leitura do número de usuários, ítens e similaridade t
  while( ( bN ) || ( bI ) || ( bt ) ){ // Impede que sejam lidos dados I, N e t inválidos
    scanf("%d %d %lf", &N, &I, &t);
    bN = (N<4) || (N>15);
    bI = (I<4) || (I>15);
    bt = (t<0.5) || (t>1.00);
  }
  
  int u[N][I]; // Matriz para inserção das notas dos usuários pelo usuário do programa
               // Linhas são os usuários, e as colunas são as notas dos filmes
  Le_u( (int *) u, N, I);
      
  /******************* 2) Processamento e suas variáveis **************************************************/
  
  double SIM[N][N]; /* Alguns elementos são desnecessários, mas facilita as contas.
		       SIM[N][N] é uma matriz quadrada.
		       Deste modo, SIM[0][1] é a similaridade entre o usuário 0 e 1, por exemplo.
		       Obviamente, SIM[1][0] = SIM[0][1], daí os elementos desnecessários, mas exatamente 
		       por isto, torna o uso mais simples.
		    */
  Similaridade( (double*) SIM, (int *) u, N, I); /* Calcula a matriz similaridade.
						    O cast (double *) é para passar SIM como um vetor 
						    de ponteiros, pois para passar vetores não é necessário
						    saber o tamanho  do vetor para passar para a função.
						    Demais matrizes serão passadas para funções deste modo.
						 */
  double Nmedias[N], S[N][I], Np[N][I]; /* Nmedias[] : Notas médias dos filmes para cada usuário.
					   S[N][I]   : Matriz de variação.
					   Np[N][I]  : Notas preditas. Serão inicializadas com 0
					   -1 Será flag para indicar DI (Dados Insuficientes) para determinada nota 
					   ao imprimí-la
					   0 Indica que nota não será impressa.
					*/
  CalcMedias(Nmedias, (int *) u, N, I);
  CalcVariacao( (double *) S, Nmedias, (int *) u, N, I);
  Zera( (double*) Np, N, I);
  PredizNota( (double *) Np, (double*) S, (double *) SIM, Nmedias, (int *) u, N, I, t);
  ImprimeNotas( (double *) Np, N, I );
  return 0;
}
