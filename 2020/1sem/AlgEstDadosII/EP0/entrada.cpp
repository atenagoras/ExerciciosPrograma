//#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "saferealloc.h"
char** LeArq(const char *nomearq, int &linhas, char ***descricao){
  FILE *f = fopen(nomearq, "r");
  if (!f)
    return NULL;
  linhas = 0;
  char **M = NULL, **DESC = NULL, *col1 = (char *) malloc(sizeof(char) * 128),
    *col2 = (char *) malloc(sizeof(char) * 128);
  *descricao = NULL;
  int vars = 0;
  const int lTAM = 256;
  char *linha = (char *) malloc(sizeof(char) * lTAM);
  linha[0] = '\0';
  while( fgets(linha, lTAM, f) ){
    if(linha[0] != '#' && linha[0] != '\n'){
      M = (char **) safeRealloc(M, sizeof(char *) * linhas, (linhas+1) * sizeof(char *) );
      DESC = (char **) safeRealloc(DESC, sizeof(char *) * linhas, (linhas+1) * sizeof(char *) );
      vars = sscanf(linha, "\"%[^\",]\",\"%[^\"\n]\n", col1, col2);
      M[linhas] = strdup(col1);
      DESC[linhas] = strdup(col2);
      linhas++;
    }
  }
  *descricao = DESC;
  free(col1);
  free(col2);
  free(linha);
  fclose(f);
  return M;
}
