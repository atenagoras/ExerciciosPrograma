#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vd.h"
#include "vo.h"
#include "ld.h"
#include "lo.h"
#include "ab.h"
#include "tr.h"
#include "a23.h"
// Comentando cabeçalhos cujas classes estão sem implementação
/*
#include "rn.h"
#include "th.h"
*/

#include "tempo.h"


// Cria Variável de medição de tempo dos testes da experiência para um tipo de TSO
tabTempo NovoTempo(char *nomeTSO, long Ttam,double Tinsere, double Tdevolve, double Tremove, double Trank, double Tseleciona){
  char *nome = (char *) malloc(sizeof(char) * (strlen(nomeTSO) + 1));
  strcpy(nome, nomeTSO);
  tabTempo t;
  t.nomeTSO    = nome;
  t.Ttam       = Ttam;
  t.Tinsere    = Tinsere;
  t.Tdevolve   = Tdevolve;
  t.Tremove    = Tremove;
  t.Trank      = Trank;
  t.Tseleciona = Tseleciona;
  t.Ttotal     = Tinsere + Tdevolve + Tdevolve + Trank + Tseleciona;
  return t;
}

/* printTeste: Imprime Testes em Arquivo 
   Parâmetros:
   tabTempo t: Estrutura que armazena os tempos de execução para cada método em uma TSO
   long n    : Nº de palavras contidas no livro  */
void printTeste(tabTempo t, char *nomearq, long n){
  FILE *out = fopen(t.nomeTSO, "r");
  if (out == NULL){ // testa se o arquivo existe
    out = fopen(t.nomeTSO, "w");
    // Escrever linha abaixo no momento da criação do arquivo
    fprintf(out,"Nome do arquivo,TSO,Total de palavras no arquivo,Palavras armazenadas na TSO,Tempo insere(),Tempo devolve(),Tempo remove(),Tempo rank(),Tempo seleciona(),Tempo Total\n");
  } else
    out = fopen(t.nomeTSO, "a"); // abre arquivo já existente e escreve a próxima linha
  fprintf(out, "%s,%s,%d,%d,%.9e,%.9e,%.9e,%.9e,%.9e,%.9e\n", nomearq, t.nomeTSO, n, t.Ttam, t.Tinsere, t.Tdevolve, t.Tremove, t.Trank, t.Tseleciona, t.Ttotal);
  fclose(out);
}

// Apaga variável do tipo TabTempo
void DoomDay(tabTempo var){
  free(var.nomeTSO);
}

/* TestesTSO: Faz os testes de performance para todas as operações da TSO escolhida */
tabTempo TestesTSO(palavra *livro, long n, char *nomeTSO){
  double Tinsere, Tdevolve, Tremove, Trank, Tseleciona;
  long Ttam;
  // Chaves para serem usadas nos testes
  Chave *chdevolve = sorteiaPalavra(livro, n), *chremove = sorteiaPalavra(livro, n), *chrank = sorteiaPalavra(livro, n);
  if (!strcmp(nomeTSO, "VD")){
    VD *vd = new VD(), *p = vd; 
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    // free(chdevolve);
    // free(chremove);
    // free(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  }
  if (!strcmp(nomeTSO, "VO")){
    VO *vo = new VO(), *p = vo;
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  } 
  if (!strcmp(nomeTSO, "LD")){
    LD *ld = new LD(), *p = ld;
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  } 
  if (!strcmp(nomeTSO, "LO")){
    LO *lo = new LO(), *p = lo;
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  }
  
  if (!strcmp(nomeTSO, "AB")){
    AB *ab = new AB(), *p = ab;
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  }
  
  if (!strcmp(nomeTSO, "TR")){
    TR *tr = new TR(), *p = tr;
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  }
  
  if (!strcmp(nomeTSO, "A23")){
    A23 *a23 = new A23(), *p = a23;
    Tinsere    = insere(livro, n, p);
    // Tdevolve   = devolve(*chdevolve, p);
    // Tremove    = remove(*chremove, p);
    // Trank      = rank(*chrank, p);
    // Tseleciona = seleciona(p);
    // Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  }
  /* Comentário de classes cuja implementação ainda não existe
  if (!strcmp(nomeTSO, "RN")){
    RN *rn = new RN(), *p = rn;
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = Ttam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  }
  if (!strcmp(nomeTSO, "TH")){
    TH *th = new TH(), *p = th;
    Tinsere    = insere(livro, n, p);
    Tdevolve   = devolve(*chdevolve, p);
    Tremove    = remove(*chremove, p);
    Trank      = rank(*chrank, p);
    Tseleciona = seleciona(p);
    Ttam       = tam(p);
    delete p;
    Delpalavra(chdevolve);
    Delpalavra(chremove);
    Delpalavra(chrank);
    return NovoTempo(nomeTSO, Ttam, Tinsere, Tdevolve, Tremove, Trank, Tseleciona);
  }
  */
  tabTempo zero = NovoTempo(NULL, 0, 0, 0, 0, 0, 0);
  return zero ;
}
