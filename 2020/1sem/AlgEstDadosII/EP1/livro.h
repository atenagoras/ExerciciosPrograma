#ifndef LIVRO
#define LIVRO
#include <stdio.h>
typedef struct{
  char *String;
} palavra;

/* ExtraiPalavras: Extrai palavras de um livro até encontrar o caractere nulo
   parâmetros: FILE: *fp     -> ponteiro para o arquivo que contém o livro
               long : *n      -> ponteiro para variável a contar o número de palavras extraídas
   retorno: Ponteiro para as palavras extraídas da string */
palavra *ExtraiPalavras(FILE *fp, long *n);
palavra *sorteiaPalavra(palavra* palavras, long n);
void Delpalavra(palavra *p); // Apaga string dentro de palavra
void Delpalavras(palavra *p, long n); // Apaga array de palavras
// retorna 1 se p1 > p2
int maior(palavra p1, palavra p2);
// retorna 1 se p1 >= p2
int maiorigual(palavra p1, palavra p2);
// retorna 1 se p1 == p2
int igual(palavra p1, palavra p2);
// retorna 1 se p1 < p2
int menor(palavra p1, palavra p2);
// retorna 1 se p1 <= p2
int menorigual(palavra p1, palavra p2);
#endif
