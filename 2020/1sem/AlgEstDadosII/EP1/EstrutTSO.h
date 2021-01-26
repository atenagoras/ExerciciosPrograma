#ifndef _TSO
#define _TSO
#include "livro.h"

typedef palavra Chave;

typedef struct{
  Chave chave;
  long freq; // frequência com que a chave é encontrada no texto de origem
  long pos; // posição da chave na última inserção a partir do texto
} infoTSO; // Estrutura com a informação de um nó de informação da TSO

infoTSO *novaInfo(); // cria nova informação TSO
bool vazia(infoTSO *info); // verifica se está vazia uma estrutura já criada e não deletada
void insereInfo(Chave chave, long pos, infoTSO *info);
infoTSO *infoCopia(infoTSO *info); // faz uma cópia da informação
void DelInfo(infoTSO *info); // Apaga informação TSO

#endif
