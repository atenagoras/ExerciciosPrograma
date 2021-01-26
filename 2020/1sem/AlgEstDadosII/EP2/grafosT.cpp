#include <stdio.h>
#include <string.h>
#include "livro.h"
#include "ab.h"
#include "experimento.h"

int analEnt(int argc, char **argv){
  if (argc != 2){
    printf("Número de argumentos inválido!\n");
    printf("Modo de uso:\n%s [arquivo de texto]\n", argv[0]);
    return 1;
  }
  FILE *fp = fopen(argv[1], "r");
  if (!fp){
    printf("Arquivo inválido, ou erro na leitura do arquivo!\n");
    return 2;
  }
  fclose(fp);
  return 0;
}

int main(int argc, char **argv){
  int r = analEnt(argc, argv);
  if (r != 0)
    return r;
  FILE *arqLivro = fopen(argv[1], "r");
  palavra *Livro;
  long tamLivro = 0;
  Livro = ExtraiPalavras(arqLivro, &tamLivro);
  fclose(arqLivro);
  AB tso;
  tso.insere(Livro, tamLivro);
  Experimentos(argv[1], &tso);
  return 0;
}
