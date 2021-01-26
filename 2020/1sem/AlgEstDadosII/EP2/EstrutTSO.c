#include <string.h>
#include <stdlib.h>
#include "livro.h"
#include "EstrutTSO.h"

infoTSO *novaInfo(){ // cria infoTSO vazia
  infoTSO *info = (infoTSO *) malloc(sizeof(infoTSO));
  info->chave.String = NULL;
  info->pos = 0;
  info->freq = 0;
  return info;
}

bool vazia(infoTSO *info){
  if (!info->chave.String && !info->pos && !info->freq)
    return true;
  return false;
}

/* insereInfo(): Insere chave (uma palavra) na info contida em tabela de símbolos ordenada (TSO).
   Se a chave já existir, será inserida de novo. Espera-se da função inserir da estrutura selecionada como
   tabela de símbolos ordenada que perceba se a palavra já foi inserida antes. Quando a palavra já foi
   inserida, a nova inserção a insere com a posição corrente, e incrementa sua frequência
   - Parâmetros:
   Chave chave : Chave é outro nome para a estrutura palavra. Vem a ser a palavra a ser inserida
   long pos    : Posição da chave no texto de origem
   infoTSO info: variável onde a informação parte da TSO será inserida/alterada                           */
void insereInfo(Chave chave, long pos, infoTSO *info){
  if (!info->chave.String){ // Se chave já existir, não malloca de novo
    info->chave.String = (char *) malloc(sizeof(char) * (strlen(chave.String) + 1));
  }
  strcpy(info->chave.String, chave.String);
  info->pos = pos;
  info->freq++;
}

infoTSO *infoCopia(infoTSO *info){
  infoTSO *copia = (infoTSO *) malloc(sizeof(infoTSO));
  copia->chave.String = (char *) malloc(sizeof(char) * (strlen(info->chave.String) + 1));
  strcpy(copia->chave.String, info->chave.String);
  copia->pos = info->pos;
  copia->freq = info->freq;
  return copia;
}

void DelInfo(infoTSO *info){
  if (info){
  free(info->chave.String);
  info->chave.String = NULL;
  free(info);
  info = NULL;
  }
}
