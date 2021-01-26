/* tso: Tabela de Símbolos Ordenada                                                                                       **
*   Este programa lê um texto grande a ser inserido pelo usuário, e gera uma tabela de símbolos a partir de suas palavras. *
*   Além disto, calcula a eficiência de cada estrutura de dados                                                            *
**  Autor: Atenágoras Souza Silva nºUSP: 5447262                                                                          */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "livro.h" // funções para leitura de arquivo e separação de palavras
#include "tempo.h" // Funções para realizar os testes

typedef struct{
  FILE *f; // Arquivo de entrada para armazenamento do texto
  char Ttso[4]; /* Tipo de Tabela de Símbolos Ordenada:                    **
		   VD : Vetor Desordenado                                   *
		   VO : Vetor Ordenado                                      *
		   LD : Lista Desordenada                                   *
		   LO : Lista Ordenada                                      *
		   AB : Árvore de Busca Binária gerada na ordem de entrada  *
		   TR : Treaps                                              *
		   A23: árvores 2-3                                         *
		   RN : árvores rubro-negras                                *
		   HS : Tabelas de Hashing		                   */
} entrada;

// Saída de erro padrão
int erroPadrao(){
  fprintf(stderr,"Erro de entrada!\n");
  fprintf(stderr,"Sintaxe:\ntso [arquivo de texto] TSO\nOnde:\n");
  fprintf(stderr,"TSO : tipo da Tabela de Símbolos Ordenada a ser utilizada\nVD  = Vetor Desordenado\nVO  = Vetor Ordenado\nLD  = Lista Desordenada\nAB  = Árvore de Busca Binária\nTR  = Treaps\nA23 = Árvores 2-3\nRN  = Árvores Rubro-Negras\nHS  = Tabelas de Hashing\n ");
  return 1;
}

/* analIN(): Analiza a entrada ao iniciar o programa
   Entrada:
   char *nome: Nome do arquivo a ser carregado
        *tso : Tipo da tabela de símbolos a armazenar as palavras do arquivo
   Retorno: estrutura do tipo entrada com o arquivo já aberto e o tipo da tabela de símbolos a ser utilizada
            NULL, se arquivo não abrir, não existir, ou tso for diferente dos tipos esperados                */
entrada *analIN(char *nome, char *tso){
  FILE *f;
  if (!(f = fopen(nome, "r")))
    return NULL;
  entrada *In;
  if (strcmp(tso, "VD") == 0 || strcmp(tso, "VO") == 0 || strcmp(tso, "LD") == 0 || strcmp(tso, "AB") == 0 || strcmp(tso, "VO") == 0 ||
      strcmp(tso, "LD") || strcmp(tso, "LO") || strcmp(tso, "TR") == 0 || strcmp(tso, "A23") == 0 || strcmp(tso, "RN") == 0 || strcmp(tso, "TS") == 0){
    In = (entrada*) malloc(sizeof(entrada));
    In->f = f;
    strcpy(In->Ttso, tso);
    return In;
  }
  return NULL;
}

int main(int argc, char** argv){
  // Processando entrada
  if (argc < 3)
    return erroPadrao();
  entrada *In = analIN(argv[1], argv[2]);
  if (!In)
    return erroPadrao();

  // Carregando livro na memória
  long n;
  palavra *livro = ExtraiPalavras(In->f, &n);
  fclose(In->f); // fechando arquivo
  
  tabTempo resultado; // para armazenar resultados dos testes
  /* Realiza os testes com a estrutura selecionada */
  resultado = TestesTSO(livro, n, In->Ttso);
  printTeste(resultado, argv[1], n);
  // Liberando memória
  free(In);
  Delpalavras(livro, n); // libera memória utilizada por array de palavras livro
  DoomDay(resultado);
  
  return 0;
}
