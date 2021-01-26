#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* Programa : spellcheck
   Descrição: Este programa gera um dicionário de palavras a partir de um livro e ordena-o; procura por
              palavras de um Tweet neste, e caso não as encontre, imprime-as separadas por um espaço.
	      Palavras de outro Tweet são impressas na linha posterior.
   Autor: Atenágoras Souza Silva NºUSP: 5447262
   Data : 21/09-02/10/2018
   Fluxo do Programa:
        1 - Ler Arquivo do livro
	2 - Extrair palavras do livro
	3 - Ordená-las
	4 - Ler arquivo de Tweets
	5 - Extrair Tweets e suas palavras
	6 - Fazer busca binária das palavras dos Tweets e Imprimí-las
	7 - Fechar arquivos e liberar memória
*/


typedef struct{
  char palavra[46]; // Tamanho suficiente para armazenar a maior palavra da língua inglesa
}Palavra;

typedef struct{
  int npal; // número de palavras de um tweet
  Palavra *tweetword; // Está acima porque aponta para endereço. Sempre coloco caracteres e strings por último
  char linha[281]; // linha para armazenar tamanho máximo do Tweet + o caractere nulo
}Tweet;

// Funções de impressão para debug
// Função para imprimir palavras de um tweet
void PrintTweetWords(Tweet t){
  int i;
  for(i = 0; i < t.npal; i++)
    printf("%d: %s\n", i, t.tweetword[i].palavra );
}

// Imprime os Tweets do arquivo, linha por linha
void PrintTweets(Tweet *t, int n){
  int i;
  for (i = 0; i < n; i++)
    printf("%d: %s\n", i, t[i].linha);
}
// Fim das funções de impresão para debug

/* retira o return ("\n") ou o carriage return ("\r\n") de uma string passada por teclado ou em arquivo DOS
   parâmetros: char *string -> string a ser manipulada */
void SohString(char *string){
  char *p;
  // procura Carriage Return
  p = strstr(string, "\r\n");
  if (p != NULL)
    *p = '\0';
  else{
    // procura só return
    p = strstr(string, "\n");
    if (p != NULL)
      *p = '\0';
  }
}

/* Libera a memória dos tweets para o sistema
   parâmetros: Tweet *t -> ponteiro para o vetor de tweets
               int n    -> Número de elementos no vetor de tweets */
void EsvaziaTweets(Tweet *t, int n){
  int i;
  for (i = 0; i < n; i++){
    free(t[i].tweetword);
  }
  free(t);
}

Tweet ExtraiTweet(char *p){
  int l; // apenas para debugar a leitura, eventualmente
  Tweet t;
  int tam, TAM, n = 0;
  char *p2;
  TAM = strlen(p); // tamanho da linha, já sem o carriage return ou return
  p2 = strstr(p, "\",\0");
  *p2 = '\0'; // Substitui por '\0' a última aspa da linha encontrada
  TAM = strlen(p);
  TAM += 0;
  strcpy(t.linha, p);
  t.tweetword = malloc(sizeof(Palavra));
  while ( p != NULL && ( (l = sscanf(p, "%[A-Za-z]", t.tweetword[n].palavra) != EOF) || l != 0) ){
    tam = strlen(t.tweetword[n].palavra);
    p += tam + 1;
    while ( (l = isalpha(*p) == 0) && *p != '\0')
      p++;
    n++;
    t.tweetword = realloc(t.tweetword, sizeof(Palavra)*(n+1) );
  }
  t.npal= n;
  return t;
}

/* Extrai todos os tweets do arquivo
   retorno: Ponteiro para todos os tweets do tipo Tweet. Só opera no ítem linha da estrutura Tweet */
Tweet *ExtraiTweets(FILE *fp, int *n){
  char *linha = NULL, *p = NULL; // p == auxiliar
  size_t taml = 0; // tamanho da linha (parâmetro para o getline)
  char *agulha = "\"text\": \""; // palavra a ser pesquisada na linha
  int tam_p; // tamanho da palavra procurada
  Tweet *tweet = NULL;
  int i = 0;
  // getline retorna -1 tanto para erro de leitura quanto para EOF
  while ( getline(&linha, &taml, fp) != -1 ){ // Lê nova linha no arquivo
    // p passa a apontar para o endereço em que a substring encontrada começa
    p = strstr(linha, agulha); // Procura por "text" : "
    if ( p != NULL ){ // Se encontrou a string, entra no if
      tam_p = strlen(agulha);
      p += tam_p; // aponta para o primeiro caractere depois da agulha (string procurada)
      // remove eventual carriage return ou return da linha
      SohString(p);
      tweet =  (Tweet *) realloc(tweet, sizeof(Tweet)*( (*n)+1 ) );
      i++;
      tweet[(*n)++] = ExtraiTweet(p);
      // PrintTweetWords(tweet[(*n-1)]);
    }
  }
  free(linha);
  if (*n == 0) tweet = NULL; // Se não houver nenhuma linha com o texto do tweet, retorna nulo
  return tweet;
}

/* ExtraiPalavras: Extrai palavras de um string separadas apenas por espaço até encontrar o caractere nulo
   parâmetros: FILE: *fp     -> ponteiro para o arquivo que contém o livro
               int : *n      -> ponteiro para variável a contar o número de palavras extraídas
   retorno: Ponteiro para as palavras extraídas da string */
Palavra *ExtraiPalavras(FILE *fp, long *n){
  Palavra *dicionario;
  dicionario = malloc( sizeof(Palavra) );
  *n = 0;
  // int L;
  
  /* %[A-Za-z] lê apenas strings de caracteres que sejam letras (caixas alta e baixa)
     %*[] lê, mas ignora (não joga em nenhum ponteiro) qualquer caractere entre []
     [^] lê qualquer caractere que NÃO esteja entre os colchetes
     %*[^A-Za-z] ignora qualquer ou string caractere que não sejam formados por letras */
  while ( fscanf(fp, "%[A-Za-z]", dicionario[*n].palavra) != EOF ){
    fscanf(fp, "%*[^A-Za-z]");
    //printf("%ld: %s\n", *n, dicionario[*n].palavra);
    (*n)++;
    dicionario = realloc(dicionario, sizeof(Palavra)*( (*n) + 1) );
  }
  return dicionario;
}

/* BuscaOrdena: Função guarda-chuva contendo funções de ordenação e de busca de vetor.
                A idéia é que as funções de ordenação (Qsort) e de busca (bb - busca binária)
		sejam tão genéricas quanto possíveis, permitindo que sejam usadas em outros programas.
		Apenas as funções guarda-chuva, de comparação e de troca terão de ser outras a cada novo
		programa, bem como o tipo dos vetores.
		TODO: funções de busca e ordenação que aceitem como parâmetros uma função de comparação
		      e de troca mais genéricas, além de vetores do tipo void para independer desta função
		      guarda-chuva.
   parâmetros : char  m         -> Modo de operação da função: 'b' para busca e 'o' para ordenação
                Palavra vetor[] -> Vetor a ser ordenado
                long ini         -> posição inicial do vetor a ser ordenado
		     fim         -> posição inicial do vetor a ser ordenado
		char *AGULHA     -> String a ser procurada no vetor, caso BuscaOrdena seja usada no modo de
		                   busca. Se o modo de uso for o de ordenação, ela poderá ser nula.
  AVISO EXTREMAMENTE IMPORTANTE: o vetor de parâmetro na função guarda-chuva será global para as funções
                                 ordenação e de busca */
int BuscaOrdena(char m, Palavra vetor[], long INI, long FIM, char *AGULHA){
  int retorno = 0;
  /* Troca: Troca um elemento Palavra por outro no algoritmo para ordenação QuickSort 
     parâmetros: *e1, *e2: Elementos do vetor (ou variáveis) a serem trocados(as) */
  void Troca(Palavra *e1, Palavra *e2){
    Palavra aux;
    aux = *e1;
    *e1 = *e2;
    *e2 = aux;
  }

  /* Particiona: Função que particiona o vetor a ser ordenado por QuickSort.
   parâmetros: vetor é VARIÁVEL GLOBAL para esta função, mas encapsulada em BuscaOrdena
                   int inicio: índice do vetor que define o começo da parte a ser ordenada
	           fim   : índice do vetor que define o fim da parte a ser ordenada
	           *i, *j: índices para definir novos inícios e fins nas chamadas recursivas de Qsort */
  void Particiona(int inicio, int fim, int *i, int *j){
    Palavra pivo;
    *i = inicio;
    *j = fim-1;
    pivo = vetor[(inicio + fim) / 2]; /* chuta o elemento do meio como pivô.
					 Diminui a possibilidade de pegar o pior
					 caso do algoritmo, quando o vetor já está
					 ordenado, ou inversamento ordenado, caso
					 fosse selecionado o primeiro elemento
					 ou o último */
    
    /* Enquanto a chave para a posicão *i do vetor (elemento.palavra) for menor que o pivô, incrementa o *i
       e enquanto ela for maior para a posição *j, decrementa *j.
       Se após isso, continuar *i <= *j, troca de os elementos *i e *j trocam de posição e terminam o 
       particionamento, "devolvendo" os índices para a função Qsort() */
    while( *i <= *j){ 
      while (strcasecmp(vetor[*i].palavra, pivo.palavra) < 0 && *i < fim)
	(*i)++;
      while (strcasecmp(vetor[*j].palavra, pivo.palavra) > 0 && *j > inicio)
	(*j)--;
      if (*i <= *j){
	Troca(&vetor[*i], &vetor[*j]);
	(*i)++;
	(*j)--;
      }
    }
  }
  /* Qsort: Algoritmo Quicksort para ordenar o vetor.
     parâmetros: vetor é VARIÁVEL GLOBAL para esta função (mas encapsulada dentro de BuscaOrdena)
                 int inicio: índice do vetor que define o começo da parte a ser ordenada
                 int fim   : índice do vetor que define o fim da parte a ser ordenada */
  void Qsort(int inicio, int fim){
    /* O QuickSort divide, a cada recursão o vetor no meio. */
    int i, j; // Índices
    Particiona(inicio, fim, &i, &j);
    if (j > inicio)
      Qsort(inicio, j+1);
    if (i < fim)
      Qsort( i, fim);
  }
  /* bb: Implementação iterativa da Busca Binária, influenciada por algoritmo similar da Wikipedia
     parâmetros: vetor é VARIÁVEL GLOBAL, porém encapsulada dentro de BuscaOrdena()
                 int      tam -> tamanho do vetor 
		 char *agulha -> palavra a ser encontrada (chave) no palheiro (o vetor)
  */
  int bb(int tam, char *agulha){
    int inf = 0;     // limite inferior
    int sup = tam-1; // limite superior
    int meio;
    while (inf <= sup)
      {
	meio = (inf + sup)/2;
	if (strcasecmp( agulha, vetor[meio].palavra) == 0 ) // verifica se encontrou
	  return meio;
	if (strcasecmp(agulha, vetor[meio].palavra) < 0 )
	  sup = meio-1; // se agulha 
	else
	  inf = meio+1;
      }
    return -1;   // não encontrado
  }
  if (m == 'o') Qsort(INI, FIM);
  else retorno = bb(FIM, AGULHA);
  // retorna 0 se bb() encontrou no início do vetor ou  BuscaOrdena for utilizada para ordenar.
  // retorna -1 se bb() não encontrou a chave (AGULHA)
  // retorna o índice do vetor em que a palavra foi encontrada
  return retorno;
}

/* NotFound: Procura por palavras dos Tweets no dicionário gerado a partir do livro e as imprime
   parâmetros: int Nt       -> Número de Tweets contidos no arquivo .json
	       long Ndic    -> Número de palavras no dicionário
	       Palavra *dic -> vetor de elementos com as palavras do dicionário
	       Tweet *t     -> tweets contidos no arquivo .json, incluídas as palavras de cada tweet */
void NotFound(Palavra *dic, long Ndic, Tweet *t, int Nt){
  int i, j, I; // I == índice retornado por BuscaOrdena caso encontre a palavra do tweet no dicionário
  for(i = 0; i < Nt; i++){
    for (j = 0; j < t[i].npal; j++){
      I = BuscaOrdena('b', dic, 0, Ndic, t[i].tweetword[j].palavra);
      if (I == -1){
	printf("%s ", t[i].tweetword[j].palavra);
      }
    }
    // Se no tweet i houver apenas palavras encontradas, após o looping em j, pula linha sem nada imprimir
    printf("\n");
  }
}

int main(int argc, char **argv){
  FILE *fp;
  char nome[256];
  // Pegando nome do arquivo que contém o livro
  fgets(nome, 256, stdin);
  SohString(nome);
  fp = fopen(nome, "r");
  // Criando o dicionário a partir do livro
  Palavra *dicionario;
  long Npalavras;
  dicionario = ExtraiPalavras(fp, &Npalavras);
  fclose(fp);
  // Ordenação do dicionário
  BuscaOrdena('o', dicionario, 0, Npalavras, NULL);
  // Pegando nome do arquivo que contem os tweets
  fgets(nome, 256, stdin);
  SohString(nome);
  fp = fopen(nome, "r");
  /* Fazer função para pegar os tweets 
     *tweet é para armazenar os tweets do arquivo (linha com o tweet e as palavas) */
  Tweet *tweet = NULL;
  int Ntweets = 0;
  // Extrai os Tweets. Cada elemento possui um Tweet e um vetor de palavras que estão dentro dele
  tweet = ExtraiTweets(fp, &Ntweets);
  if (tweet == NULL){
    printf("No tweets to check\n");
    return 0;
  }
  // Busca palavras dos tweets e armazena os não encontrados
  NotFound(dicionario, Npalavras, tweet, Ntweets);
  // PrintTweets(tweet, Ntweets);
  fclose(fp);
  free(dicionario);
  EsvaziaTweets(tweet, Ntweets);
  return 0;
}
