#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Programa : knn - K Vizinhos mais Próximos
   Descrição: Este programa utiliza o algorítimos de K vizinhos mais próximos para classificar a espécie
              de plantas do gênero Iris. Depois, a classificação do algoritmo é comparada à classificação
	      de um especialista.
   Autor: Atenágoras Souza Silva NºUSP: 5447262
   Data : 1º-/09/2018
   Fluxo do Programa:
        1 - Ler Arquivo de treinamento
	2 - Ler Arquivo de flores de teste
	3 - Comparar todas as flores de treino com cada flor de teste por meio de distância entre vetores (distância de Euclides)
	4 - Ordenar em ordem crescente de raio
	5 - Somar a contagem de cada espécie entre as flores de treino comparadas para as k com menores distâncias
		+ Atribui à flor de teste a espécie que teve a contagem maior
		+ Em caso de empate, atribuir a espécie da flor de treino cuja distância para a flor de teste é menor (entre as empatadas)
	6 - Repetir os passos 3 a 4 para todas as demais flores de treino
	7 - Contar Taxa de Acerto ( (quantas flores classificadas por knn batem com a classificação do botânico) / Total de flores de teste )
	8 - Imprimir Espécie por knn ao lado da espécie do botânico (Ex: setosa setosa)
	9 - Imprimir Taxa de Acerto
*/

// Teste função por função na ordem em que precisam ser executadas

#define STAM 11 // Define o tamanho máximo da string para armazenar os nomes das espécies
// Estrutura para leitura dos dados da flor dos arquivos (tanto treino quanto teste)
typedef struct{
  float scomp; // Comprimento da Sépala
  float slarg; // Largura da Sépala
  float pcomp; // Comprimento da Pétala
  float plarg; // Largura da Pétala
  char especie[STAM]; // Nome da Espécie
}FlowerPower;

/* Armazena a distância entre uma flor treino e outra flor teste e a espécie da flor treino
   Estrutura específica para ser usada na função de comparação dos dados de treino e teste, respectivamente.
 */
typedef struct{
  float dist;
  char especie[STAM]; // Espécie, segundo o algoritmo knn
  //char espbot[STAM]; // Espécie, segundo o botânico
}ParcialKnn;

 // Esta estrutura para armazenar o resultado final do algoritmo para cada planta
typedef struct{
  char espknn[STAM];
  char espbot[STAM];
}Flor;

// potência de dois
float pot2(float x){
  return x*x;
}

/* Deuclides: Calcula a distância euclidiana entre uma flor de treino e uma de teste
   parâmetros: - flortreino: uma variável de tipo FlowerPower contendo uma flor de treino
               - florteste : uma variável de tipo FlowerPower contendo uma flor de teste
   retorno: (float) Distância euclidiana entre as duas flores */
float Deuclides(FlowerPower flortreino, FlowerPower florteste){
  // declara as diferenças quadráticas de cada elemento das flores treino e teste calculando-as
  float scomp_quaddiff = pot2(flortreino.scomp - florteste.scomp),
    slarg_quaddiff = pot2(flortreino.slarg - florteste.slarg),
    pcomp_quaddiff = pot2(flortreino.pcomp - florteste.pcomp),
    plarg_quaddiff = pot2(flortreino.plarg - florteste.plarg);
  float SQRT = sqrt(scomp_quaddiff + slarg_quaddiff + pcomp_quaddiff + plarg_quaddiff);
  return SQRT;
}

/* Troca: Troca um elemento ParcialKnn por outro no algoritmo para ordenação
          QuickSort 
   parâmetros: *e1, *e2: Elementos do vetor (ou variáveis) a serem trocados(as) */
void Troca(ParcialKnn *e1, ParcialKnn *e2){
  ParcialKnn aux;
  aux = *e1;
  *e1 = *e2;
  *e2 = aux;
}

/* Particiona: Função que particiona o vetor a ser ordenado por QuickSort.
   parâmetros: vetor : vetor a ser ordenado
               inicio: índice do vetor que define o começo da parte a ser ordenada
	       fim   : índice do vetor que define o fim da parte a ser ordenada
	       *i, *j: índices para definir novos inícios e fins nas chamadas
	               recursivas de Qsort */
void Particiona(ParcialKnn vetor[], int inicio, int fim, int *i, int *j){
  ParcialKnn pivo;
  *i = inicio;
  *j = fim-1;
  pivo = vetor[(inicio + fim) / 2]; /* chuta o elemento do meio como pivô.
				       Diminui a possibilidade de pegar o pior
				       caso do algoritmo, quando o vetor já está
				       ordenado, ou inversamento ordenado, caso
				       fosse selecionado o primeiro elemento
				       ou o último */
  
  /* Enquanto a chave para a posicão *i do vetor (elemento .dist) for menor que o pivô, incrementa o *i
     e enquanto ela for maior para a posição *j, decrementa *j.
     Se após isso, continuar *i <= *j, troca de os elementos *i e *j trocam de posição e terminam o particionamento,
     "devolvendo" os índices para a função Qsort()
   */
  while( *i <= *j){
    while (vetor[*i].dist < pivo.dist && *i < fim)
      (*i)++;
    while (vetor[*j].dist > pivo.dist && *j > inicio)
      (*j)--;
    if (*i <= *j){
      Troca(&vetor[*i], &vetor[*j]);
      (*i)++;
      (*j)--;
    }
  }
}
/* Qsort: Algoritmo Quicksort para ordenar o vetor.
          Utiliza algoritmo do tipo "Dividir e Conquistar"
   parâmetros: vetor: vetor a ser ordenado
               inicio: índice do vetor que define o começo da parte a ser ordenada
	       fim   : índice do vetor que define o fim da parte a ser ordenada */
void Qsort(ParcialKnn vetor[], int inicio, int fim){
  /* O QuickSort divide, a cada recursão o vetor no meio. */
  int i, j; // Índices
  Particiona(vetor, inicio, fim, &i, &j);
  if (j > inicio)
    Qsort(vetor, inicio, j+1);
  if (i < fim)
    Qsort(vetor, i, fim);
}

/* Ordena: Utiliza o algoritmo QuickSort para ordenar o vetor 
   parâmetros: vetor: vetor a ser ordenado
               N    : tamanho do vetor
*/
void Ordena(ParcialKnn vetor[], const int N){
  Qsort(vetor, 0, N);
}

/* ContaEspecies: Conta quantas flores de cada espécie foram encontradas entre as k primeiras flores 
                  em um vetor ordenado
   parâmetros: vetor  : vetor ordenado ORDENADO de distâncias entre flores treino e flor teste
               Ntreino: tamanho do vetor
	       *setosa, *versicolor, *virginica: número de elementos de cada espécie entre os k primeiros
	       k      : Número de vizinhos mais próximos (para definir os k primeiros elementos a serem
	                considerados*/
void ContaEspecies(ParcialKnn vetor[], const int Ntreino, int *setosa, int *versicolor, int *virginica, int k){
  *setosa = 0;
  *versicolor = 0;
  *virginica = 0;
  int i;
  for (i = 0; i < k; i++){
    if ( strcmp("setosa", vetor[i].especie) == 0 )
      (*setosa)++;
    else if ( strcmp("versicolor", vetor[i].especie) == 0 )
      (*versicolor)++;
    else if( strcmp("virginica", vetor[i].especie) == 0 )
      (*virginica)++;
  }
}

/* EspecieKnn: Define a espécie da flor de teste analisada com base na quantidade de flores de
               cada espécie encontrada entre as k primeiras e no critério de desempate
   parâmetros: primeirao: DEVE receber o primeiro elemento de um vetor ordenado
               setosa, versicolor e virginica: número de elementos encontrados em cada espécie 
	       entre os k primeiros
   retorno: string com a espécie da flor para o knn */
char *EspecieKnn(ParcialKnn primeirao, int setosa, int versicolor, int virginica){
  char *retorno;
  retorno = malloc(sizeof(char)*STAM);
  if (setosa > versicolor && setosa > virginica)
    sprintf(retorno, "setosa");
  else if (versicolor > setosa && versicolor > virginica)
    sprintf(retorno, "versicolor");
  else if (virginica > setosa && virginica > versicolor)
    sprintf(retorno, "virginica");
  else
    strcpy(retorno, primeirao.especie); /* Em caso de empate, o selecionado é o primeiro elemento do vetor do tipo ParcialKnn.
					   Por esta razão, a função foi chamada a partir de ComparaTreinoTeste() com o primeiro
					   elemento do vetor, pois ele será o vizinho mais próximo */
  return retorno;
}

/* ComparaTreinoTeste: Retorna o resultado da comparação de UMA ÚNICA flor teste com as flores presentes no vetor de flores 
                       de treino a partir da análise dos k vizinhos mais próximos. Basicamente, chama as principais 
		       funções do algoritmo knn
   parâmetros: *treino: ponteiro para flores de treino
               teste  : flor de teste corrente
	       Ntreino: tamanho do vetor de flores treino
	       k      : número de vizinhos para fazer comparação */
Flor ComparaTreinoTeste(FlowerPower *treino, FlowerPower teste, const int Ntreino, int k){
  ParcialKnn partial_res[Ntreino];
  int i;
  int setosa = 0, versicolor = 0, virginica = 0; // contador para cada espécie
  for (i = 0; i < Ntreino; i++){
    partial_res[i].dist = Deuclides(treino[i], teste);
    strcpy(partial_res[i].especie, treino[i].especie);
  }
  Ordena(partial_res, Ntreino);
  ContaEspecies(partial_res, Ntreino, &setosa, &versicolor, &virginica, k);
  Flor flor;
  char *especieknn;
  // Decisão do knn sobre a espécie com base na comparação por distância euclidiana, contagem e
  // critério de desempate (seleciona o vizinho mais próximo em caso de desempate)
  especieknn = EspecieKnn(partial_res[0], setosa, versicolor, virginica);
  // copia o resultado de EspecieKnn (que é uma string) para flor.espknn
  strcpy(flor.espknn, especieknn );
  strcpy(flor.espbot, teste.especie);
  free(especieknn); // libera a memória necessária para armazenar a string na heap
  return flor;
}

/* knn: Super função que retorna o resultado do knn para todos as flores teste
   retorno: ponteiro para uma estrutura Flor (ou seja, retorna um Flor* ). 
            Cada registro armazena a espécie atribuida à flor pelo algoritmo e a classificação do 
	    bontânico */
Flor *knn(FlowerPower *treino, FlowerPower *teste, const int Ntreino, int const Nteste, int k){
  int i;
  Flor *resultado;
  resultado = malloc( sizeof(Flor)*Nteste );
  for (i = 0; i < Nteste; i++){
    resultado[i] = ComparaTreinoTeste(treino, teste[i], Ntreino, k);
  }
  return resultado;
}

/* Learquivo: Lê arquivo de entrada e joga registros para ponteiro de estrutura FlowerPower
   parâmetros: *entrada: ponteiro para nome do arquivo de entrada
               *N      : tamanho do vetor de flores a ser calculado e "retornado" por ter sido passado por referência
   retorno: vetor de flores extraído do arquivo */
FlowerPower *Learquivo(char *entrada, int *N){
  FILE *in;
  in = fopen(entrada, "r");
  FlowerPower *flores = NULL;
  char linha1[128];
  fgets(linha1, 128, in);
  *N = 0;
  do{
    flores = (FlowerPower *) realloc(flores, ((*N)+1)*sizeof(FlowerPower) );
    // não fiz scanf(...) == EOF dentro dos parênteses do while porque o realloc criaria um espaço a mais
    // sem necessidade
    fscanf(in, "%f,%f,%f,%f,\"%s\n", &flores[(*N)].scomp, &flores[(*N)].slarg,
	   &flores[(*N)].pcomp, &flores[(*N)].plarg, flores[(*N)].especie  ); /* flores[i].especie já é um endereço de memória
										 pois especie é uma string */
    flores[(*N)].especie[ strlen(flores[(*N)].especie) -1 ] = '\0'; // Remove as aspas adicionais
    (*N)++;
  }while ( !feof(in) ); /* feof(fp) retorna 0 se não chegou ao fim e diferente de 0 se chegou ao fim do arquivo */
  //(*N)--; // N é incrementado mais uma vez sem necessidade no looping, retornando um tamanho maior do que o número de flores
  fclose(in);
  return flores;
}
// Imprime lado a lado tanto a flor "advinhada" pelo algoritmo knn quanto a classificação do botânico
void ImprimeResultado(Flor *resultado, const int N){
  int i;
  for (i = 0; i < N; i++)
    printf("%s %s\n", resultado[i].espknn, resultado[i].espbot);
}

/* Tacerto?: Apenas conta o número de acertos do algoritmo knn
   parâmetros: *resultado: vetor com a classificação das flores teste
               N         : tamanho do vetor
   retorno : taxa de acertos (acertos/Nteste ou acertos/Nflores de teste) */
float TaCerto(Flor* resultado, const int N){
  int i, count;
  //float tacerto; // taxa de acerto
  for (i = 0; i < N; i++)
    if (strcmp(resultado[i].espbot, resultado[i].espknn) == 0)
      count++;
  return (float) count / (float) N;
}

int main(int argc, char** argv){
  FlowerPower *treino, *teste; // Vetores que recebem os dados dos arquivos treino e teste, respectivamente
  int Ntreino, Nteste; // Armazena o tamanho dos vetores/número de flores nos vetor
  char arquivo_treino[256], arquivo_teste[256]; // caminho e nome do arquivo a ser lido
  int k; // Número de vizinhos mais próximos a serem considerados pelo algoritmo, dado pelo usuário
  scanf("%s %s %d", arquivo_treino, arquivo_teste, &k);
  // Armazena os dados das flores para treinamento
  treino = Learquivo(arquivo_treino, &Ntreino);
  teste  = Learquivo(arquivo_teste, &Nteste);
  if ( k > Ntreino ){ // Impede execução, caso número de vizinhos seja maior que Ntreino
    printf("k is invalid\n");
    return 0;
  }
  Flor *resultado;
  float tacerto; // taxa de acerto
  // Armazena o resultado do algoritmo para todas as flores, junto à avaliação do botânico
  resultado = knn(treino, teste, Ntreino, Nteste, k);
  tacerto = TaCerto(resultado, Nteste); // chama a função que calcula a taxa de acertos do algoritmo knn
  ImprimeResultado( resultado, Nteste);
  printf("%.4f\n", tacerto); // imprime a taxa de acertos na tela
  free(resultado);
  free(treino);
  free(teste);
  return 0;
}
