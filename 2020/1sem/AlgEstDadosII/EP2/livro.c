#include <stdio.h>
#include <string.h>
#include "livro.h"
#include <stdlib.h>
#include <ctype.h>

/* ExtraiPalavras: Extrai palavras de um livro até encontrar o caractere nulo
   parâmetros: FILE: *fp     -> ponteiro para o arquivo que contém o livro
               int : *n      -> ponteiro para variável a contar o número de palavras extraídas
   retorno: Ponteiro para as palavras extraídas da string */
palavra *ExtraiPalavras(FILE *fp, long *n){
  palavra *livro;
  livro = (palavra *) malloc(sizeof(palavra));
  *n = 0;
  char word[256];
  int i;
  
  /* %[A-Za-z] lê apenas strings de caracteres que sejam letras (caixas alta e baixa)
     %*[] lê, mas ignora (não joga em nenhum ponteiro) qualquer caractere entre []
     [^] lê qualquer caractere que NÃO esteja entre os colchetes
     %*[^A-Za-z] ignora qualquer ou string caractere que não sejam formados por letras */
  while (fscanf(fp, "%[A-Za-z]", word) != EOF){
    for (i = 0; word[i] != '\0'; i++)
      word[i] = tolower(word[i]); // convertendo tudo para minúscula
    livro[*n].String = (char *) malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(livro[*n].String, word);
    fscanf(fp, "%*[^A-Za-z]");
    (*n)++;
    livro = (palavra *) realloc(livro, sizeof(palavra) * ((*n) + 1));
  }
  return livro;
}

void Copiapalavra(palavra *copia, palavra original){
  copia->String = (char *) malloc(sizeof(char) * (strlen(original.String) + 1));
  strcpy(copia->String, original.String);
}

palavra *sorteiaPalavra(palavra *palavras, long n){
  int s = rand() % n;
  palavra *r = &palavras[s];
  return r;
}

// Apaga string dentro de palavra
void Delpalavra(palavra *p){
  free(p->String);
}

/* Delpalavras(): Apaga array de palavras
   Parâmetros:
   palavra *p: array de palavras
   int n     : Tamanho do array           */
void Delpalavras(palavra *p, long n){
  int i;
  for (i = 0; i < n; i++)
    Delpalavra(&p[i]);
  free(p);
}

// retorna 1 se p1 > p2
int maior(palavra p1, palavra p2){
  if (strcasecmp(p1.String, p2.String) > 0)
    return 1;
  return 0;
}
// retorna 1 se p1 >= p2
int maiorigual(palavra p1, palavra p2){
  if (strcasecmp(p1.String, p2.String) >= 0)
    return 1;
  return 0;
}
// retorna 1 se p1 == p2
int igual(palavra p1, palavra p2){
  if (!strcasecmp(p1.String, p2.String))
    return 1;
  return 0;
}
// retorna 1 se p1 < p2
int menor(palavra p1, palavra p2){
  if (strcasecmp(p1.String, p2.String) < 0)
    return 1;
  return 0;
}
// retorna 1 se p1 <= p2
int menorigual(palavra p1, palavra p2){
  if (strcasecmp(p1.String, p2.String) <= 0)
    return 1;
  return 0;
}
