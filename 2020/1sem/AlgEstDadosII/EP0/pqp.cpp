#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "Fila.h"
#include "FilaOrd.h"
#include "voo.h"
#include "Pistas.h"
#include "itoa.h"
#include "sorteio.h"
#include "saferealloc.h"
using namespace std;

/* Tpouso(): Estima o tempo para o avião pousar de acordo com sua posição na fila (útil para o cálculo mais preciso de quando um vôo deve ser desviado)
   Parâmetros:
   PISTAS P   : Pistas do aeroporto
   FilaOrd F  : Fila de aviões esperando para usar uma das Pistas
   No<voo> *no: Nó do tipo voo, com o avião para o qual se deve calcular o tempo
   int tmedio : Tempo médio de pouso (utilizado para ajudar a calcular o tempo estimado, se for o pior caso)
   Retorno: Tempo estimado para o avião poder usar a pista (Obs: Não considera que à frente podem estar vôos de emergência) */
int Tpouso(PISTAS &P, FilaOrd &F, No<voo> *no){
  int t1 = P.P1.Contador(), t2 = P.P2.Contador(), i = 0, t = 0;
  Fila<voo> *f;
  No<voo> *p;
  
  // Iniciar Busca pelo Nó na Fila Ordenada
  if (F.Emergencia.vazia() && F.Aterrizagem.vazia())
    return t1 < t2 ? t1:t2;
  else if (!F.Emergencia.vazia()){
    f = &F.Emergencia;
    for(p = f->ini, i = 0; p != NULL || p == no; i++, p = p->prox);
  }
  if (!p && !F.Aterrizagem.vazia()){ // Se não encontrou nó em Emergencia, continuar procurando em Aterrizagem
    f = &F.Aterrizagem;
    for(p = f->ini, i; p != NULL || p == no; i++, p = p->prox);
  }
  else if (!p && !i)
    return -1; // Não encontrou o nó em lugar algum

  // Efetivamente calcular o tempo
  if (t1 == t2)
    return t = t1 + 2*i + 1;
  if ( (t1 == 0 && t2 == 2) || (t1 == 2 && t2 == 0) )
    return t = (t1 < t2 ? t1:t2) + 2*i + 1;
  if ( (t1 == 0 && t2 == 1) || (t1 == 1 && t2 == 0) )
    return 0 + i + 1;
  if ( (t1 == 1 && t2 == 2) || (t1 == 2 && t2 == 1) )
    return 1 + i + 1;
  return -1; // Erro se chegar até aqui
}

// Imprime os aviões esperando para pousar ou decolar, e devolve a média de combustível dos que estão esperando para pousar no instante
float printEspera(FILE *f, FilaOrd &F){
  if (F.vazia()){
    fprintf(f, "\nNenhum avião esperando para pousar ou decolar neste tempo!\n");
    return 0;
  }
  int fuelsum = 0, i = 0;
  No<voo> *p = NULL;
  char *infoVoo = NULL;
  fprintf(f, "Aviões esperando para pousar:\n");
  if (!F.Emergencia.vazia()){
    p = F.Emergencia.ini;
    while (p){
      if (!p->item->Ctorre){
	infoVoo = p->item->printString();
	fprintf(f, "%s", infoVoo);
	free(infoVoo);
	infoVoo = NULL;
	fuelsum += p->item->combustivel;
	i++;
      }
      p = p->prox;
    }
  }
  if (!F.Aterrizagem.vazia()){
    p = F.Aterrizagem.ini;
    while (p){
      infoVoo = p->item->printString();
      fprintf(f, "%s", infoVoo);
      free(infoVoo);
      infoVoo = NULL;
      fuelsum += p->item->combustivel;
      i++;
      p = p->prox;
    }
  }
  float mfuel = i != 0 ? (float) fuelsum / i : 0;
  fprintf(f, "Média de combustível dos aviões esperando para pousar: %f\n", mfuel);
  
  fprintf(f, "Aviões esperando para decolar:\n");
  if (!F.Decolagem.vazia()){
    p = F.Decolagem.ini;
    while (p){
      infoVoo = p->item->printString();
      fprintf(f, "%s", infoVoo);
      free(infoVoo);
      infoVoo = NULL;
      p = p->prox;
    }
  }
  return mfuel;
}

// Retorna Média de Combustível dos aviões que pousaram no instante
float MCpousados(PISTAS &P){
  int n = 0;
  float fuel = 0;
  int t1 = P.P1.Contador(), t2 = P.P2.Contador(), tD = P.D.Contador(), t[3] = {t1, t2, tD};
  voo *v1 = P.P1.V, *v2 = P.P2.V, *vD = P.D.V, *v[3] = {v1, v2, vD};
  int i;
  for (i = 0; i < 3; i++){
    if (t[i] == 2)
      if (!v[i]->Ctorre){ // inclui emergências que pousaram, só para a média de combustível
	n++;
	fuel += v[i]->combustivel;
      }
  }
  v1 = v2 = vD = NULL;
  return n != 0 ? fuel /= n : 0; // fuel = fuel / n
}
//  Retorna Nº de pousos no instante
int Npousados(PISTAS &P){
 int n = 0;
 int t1 = P.P1.Contador(), t2 = P.P2.Contador(), tD = P.D.Contador(), t[3] = {t1, t2, tD};
 voo *v1 = P.P1.V, *v2 = P.P2.V, *vD = P.D.V, *v[3] = {v1, v2, vD};
 int i;
 for (i = 0; i < 3; i++){
   if (t[i] == 2)
     if (!v[i]->Ctorre && !v[i]->emergencia)
       n++;
 }
 v1 = v2 = vD = NULL;
 return  n;
}
// Retorna Nº de decolagens no instante
int Ndecolados(PISTAS &P){
  int n = 0;
  int t1 = P.P1.Contador(), t2 = P.P2.Contador(), tD = P.D.Contador(), t[3] = {t1, t2, tD};
  voo *v1 = P.P1.V, *v2 = P.P2.V, *vD = P.D.V, *v[3] = {v1, v2, vD};
  int i;
  for (i = 0; i < 3; i++){
    if (t[i] == 2)
      if (v[i]->Ctorre && !v[i]->emergencia)
	n++;
  }
  v1 = v2 = vD = NULL;
  return n;
}
/* qEmergencia(): Retorna o nº de vôos usando a pista como emergência
   Parâmetros:
   PISTAS &P: PISTAS do aeroporto em que se deseja verificar o vôo que está pousando
   int &npe: N° de emergências POUSANDO calculado e devolvido à variável de referência
   Retorno: n° de vôos usando a pista como emergência
 */
int qEmergencia(PISTAS &P, int &npe){
  int n = 0;
  int t1 = P.P1.Contador(), t2 = P.P2.Contador(), tD = P.D.Contador(), t[3] = {t1, t2, tD};
  voo *v1 = P.P1.V, *v2 = P.P2.V, *vD = P.D.V, *v[3] = {v1, v2, vD};
  npe = 0;
  int i;
  for (i = 0; i < 3; i++){
    if (t[i] == 2)
      if (v[i]->emergencia){
	n++;
	if (!v[i]->Ctorre)
	  npe++;
      }
  }
  return n;
}

void estatisticas(int t, FILE *f, FilaOrd &F, PISTAS &P, float &tmPouso, float &tmDecolagem, float &mcPousados, float &mcPousar, float mcsPousados, int &totalPousados, int &totalDecolagens, int &totalEmergencia, int &Qemergencia, int &nDecolagens, int &nPousados, int &tnpe){
 // implementacao
  // início da estatísticas
  int npe = 0; // nº de pousos de emergência (nesta iteração e total, respectivamente)
  fprintf(f, "\nDados e estatísticas no tempo %d da simulação:\n", t);
  
  mcPousar    = printEspera(f, F);
  // fprintf(f, "Média de Combustível dos aviões esperando para pousar: %f\n", mcPousar);
  mcPousados  = MCpousados(P);
  nPousados   = Npousados(P);
  nDecolagens = Ndecolados(P);
  Qemergencia = qEmergencia(P, npe);
  fprintf(f, "Média de Combustível dos aviões que pousaram no tempo atual: %f\n", mcPousados);
  fprintf(f, "Nº de pousos no tempo atual: %d\n", nPousados);
  fprintf(f, "Nº de decolagens no tempo atual: %d\n", nDecolagens);
  fprintf(f, "Nº de vôos de emergência usando as Pistas no tempo atual: %d\n", Qemergencia);
  
  totalPousados   += nPousados;
  tnpe            += npe;
  totalDecolagens += nDecolagens;
  totalEmergencia += Qemergencia;
  mcsPousados     += mcPousados;
  fprintf(f, "Média de Combustível dos voôs que pousaram na simulação até aqui: %f\n", mcsPousados != 0 ? mcsPousados / (totalPousados + tnpe) : 0 );
  fprintf(f, "Total de Pousos: %d\n", totalPousados);
  fprintf(f, "Total de Decolagens: %d\n", totalDecolagens);
  fprintf(f, "Total de vôos de emergência que usaram a pista: %d\n", totalEmergencia);
  fprintf(f, "Total de vôos de emergência que pousaram: %d\n", tnpe);
  if (totalPousados)
    tmPouso = t / totalPousados;
  if (totalDecolagens)
    tmDecolagem = t / totalDecolagens;
  fprintf(f, "Tempo Médio para: Pouso: %f , Decolagem: %f\n", tmPouso);
}

/* FDP(): Direciona os vôos que não tem chance de pousar no PQP para aeroporto FDP (Aeroporto Internacional Familícia Do Presidente) 
   Parâmetro:
   voo *v         : Vôo redirecionado
   Fila<voo> &fdp : Fila de vôos que foram redirecionados para FDP
   Retorno: ponteiro para string de mensagem de redirecionamento para FDP */
char* FDP(voo* v, Fila<voo> &fdp){
  char titulo[100];
  sprintf(titulo, "\nVôo redirecionado para o Aeroporto Internacional Familícia Do Presidente (FDP)\n");
  char *infoVoo = v->printString();
  fdp.inserirFIM(new No<voo>(v));
  int tam = strlen(titulo) + strlen(infoVoo) + 2; // espaço para armazenar também a quebra de linha e o fim de string (\0)
  char *retorno = (char *) malloc(sizeof(char) * tam);
  sprintf(retorno, "%s%s", titulo, infoVoo);
  free(infoVoo);
  infoVoo = NULL;
  return retorno;
}

/* TheCrash(): Checa se vôo sem combustível em nó da Fila vai conseguir pousar, ou não
   Parâmetros
   PISTAS &P   : Pistas do Aeroporto para checar se o vôo irá cair
   No<voo> no  : Nó a ser analisado
   Fila<voo>
     &F        : Fila proprietária do nó a ser analisado
     &fThecrash: Fila de vôos que cairam
   Retorno: NULL (se não caiu nenhum vôo), string com o vôo que caiu */
char* TheCrash(PISTAS &P, No<voo> *no, Fila<voo> &F, Fila<voo> &fThecrash){
  if (P.livreEmergencia() || no->item->combustivel)
    return NULL;
  const char *thecrash = "Caiu o vôo:\n";
  char *infoVoo = no->item->printString();
  char *retorno = (char *) malloc(sizeof(char) * (strlen(thecrash)) + strlen(infoVoo) + 2); // espaço para pulo de linha e fim-de-string
  sprintf(retorno, "%s%s", thecrash, infoVoo);
  free(infoVoo);
  infoVoo = NULL;
  fThecrash.inserirINI(new No<voo>(no->item));
  if (no)
    delete F.remove(no);
  no = NULL;
  return retorno;
}

/* analFila(): Analiza Fila para atualizá-la e/ou tomar deciões a respeito dos vôos
   Parâmetros
   PISTAS P    : Pistas do Aeroporto
   FilaOrd *F  : Fila a ser analisada
   int tmPouso : Tempo Médio de Pouso
   int how     : Como a função será usada (0 - calcula Tpouso e chama FDP(), se necessário; 1 - Verifica que aviões irão cair
   Fila<voo>
     &fFDP     : Fila para armazenar vôos redirecionados para FDP
     $fThecrash: Fila para armazenar vôos que cairam
   Retorno: String com relatório do que foi feito nesta função */
char *analFila(PISTAS &P, FilaOrd *F, int tmPouso, int how, Fila<voo> &fFDP, Fila<voo> &fThecrash){
  No<voo> *p;
  int t = 0, tp, analTAM = 1024;
  char *fdp = NULL, // recebe log de FDP()
    *ANAL = (char *) malloc(analTAM * sizeof(char)); // armazena informações de analFila() para devolver à função chamadora
  char *CHp = NULL;
  ANAL[0] = '\0';
  int currAnalTAM = strlen(ANAL) + 1;
  Fila<voo> *f[2] = {&F->Emergencia, &F->Aterrizagem};
  int i;
  int c = 0; // contador de vôos redirecionados
  char *crash = NULL;

  if (!how){
    // Procurando aviões que precisarão redirecionar vôo
      // Procurando na Emergência: Indesejado, mas em nome da segurança...
    int cc1 = 0; // Conta vôos com combustível C = 1; se cc1 >=4, começa a redirecionar todos os vôos nessa situação que irão pousar em PQP
    if (!F->Emergencia.vazia()){
      p = F->Emergencia.ini;
      while(p && !p->item->Ctorre){
	cc1 = p->item->combustivel == 1 ? cc1++:cc1;
	t  = Tpouso(P, *F, p);
	tp = t > tmPouso ? t:tmPouso;
	if (p->item->combustivel < tp || (cc1 > 3 && p->item->combustivel == 1)){ // Testa se precisa remanajar o vôo
	  fdp = FDP(F->Emergencia.remove(p), fFDP);
	  c++;
	  currAnalTAM += strlen(fdp) +1;
	  if (currAnalTAM > analTAM){ // testa se precisa realocar memória para ANAL
	    analTAM += currAnalTAM;
	    CHp = (char *) realloc(ANAL, analTAM * sizeof(char));
	    if (CHp)
	      ANAL = CHp;
	  }
	  
	  strcat(ANAL, fdp);
	  free(fdp);
	  fdp = NULL;
	}
	p = p->prox;
      }
    }
    
    // Procurando na Aterrizagem
    if (!F->Aterrizagem.vazia()){
      p = F->Aterrizagem.ini;
      while(p){
	cc1 = p->item->combustivel == 1 ? cc1++:cc1;
	t = Tpouso(P, *F, p);
	tp = t > tmPouso ? t:tmPouso;
	if (p->item->combustivel < tp || (cc1 > 3 && p->item->combustivel)){ // Testa se precisa remanajar o vôo
	  fdp = FDP(F->Aterrizagem.remove(p), fFDP);
	  c++;
	  currAnalTAM += strlen(fdp) +1;
	  if (currAnalTAM > analTAM){ // testa se precisa realocar memória para ANAL
	    analTAM += currAnalTAM;
	    CHp = (char *) realloc(ANAL, analTAM * sizeof(char));
	    if (CHp)
	      ANAL = CHp;
	  }
	  strcat(ANAL, fdp);
	  free(fdp);
	  fdp = NULL;
	}
	p = p->prox;
      }
    }
    char totalFDP[100];
    sprintf(totalFDP, "Total de vôos redirecionados para FDP: %d\n", c);
    if (strlen(ANAL) + strlen(totalFDP) + 1 > analTAM){
      analTAM += strlen(totalFDP) + 1;
      CHp = (char *) realloc(ANAL, analTAM * sizeof(char));
      if (CHp)
	ANAL = CHp;
    }
    strcat(ANAL, totalFDP);
  }
  else {
  // Verificando se aviões cairão
  for (i = 0; i < 2; i++)
    for (p = f[i]->ini; p; p = p->prox){
      crash = TheCrash(P, p, *f[i], fThecrash);
      if (crash){
	currAnalTAM += strlen(crash) + 1;
	if (currAnalTAM > analTAM){ // testa se precisa realocar memória para ANAL
	  analTAM += currAnalTAM;
	  CHp = (char *) realloc(ANAL, analTAM * sizeof(char));
	  if (CHp)
	    ANAL = CHp;
	strcat(ANAL, crash);
	free(crash);
	crash = NULL;
	}
      }
    }
  }
  
  char *ANALstring = strdup(ANAL);
  free(ANAL);
  ANAL = NULL;
  return ANALstring;
}

/* SIMULACAO(): Realiza a simulação de controle de tŕafego
   Parâmetros:
   FILE &*f  : Arquivo de log com todas as informações de cada um dos instantes da simulação
   char
     **porto: Aeroportos disponíveis para sorteio
     **cia   : Companhias Aéreas disponíveis para sorteio
   int
     Np      : Número de Aeroportos disponíveis
     Ncia    : Número de Companhias disponíveis
     K       : Número máximo de Vôos sorteados
     C       : Máximo de Combustível sorteado para cada avião, em unidades de tempo
     T       : Tempo da simulação
     V       : Número máximo de Tempo Estimado de Vôo para cada avião a decolar
     PrV     : Probabilidade de um vôo ser sorteado
     PrE     : Probabilidade de um vôo de emergência ser sorteado */
void SIMULACAO(FILE *f, char **porto, int Np, char **cia, int Ncia, int K, int C, int T, int V, int PrV, int PrE){
  /* tmPouso    : tempo médio de espera para pousar
     tmDecolagem: tempo médio de espera para decolcar
     mcPousados : Média de Combustível dos aviões que pousaram
     mcPousar   : Média de Combustível dos aviões a pousar
     Qemergencia: Quantidade de vôos pousando ou decolando em condições de emergência */
  float tmPouso = 0, tmDecolagem = 0, mcPousados = 0, mcPousar = 0;
  int nPousados = 0, nDecolagens = 0, Qemergencia = 0;
  // Total de vôos que USARAM PQP (Pistas do aeroporto)
  int totalPousados = 0, totalDecolagens = 0, totalEmergencia = 0;
  float mcsPousados = 0; // média de combustível dos vôos que pousaram na simulação inteira
  
  // Para iniciar a Simulação
  int t; // tempo da simulação
  char *stats = NULL; // armazena as estatísticas para imprimir em arquivo
  char *analLOG = NULL; // armazena as informações de analFila();
  char *infoPistas = NULL; // armazena as informações de uso das Pistas a cada iteração
  //char *infoVoo; // armazena as informações de vôo criados
  FilaOrd F;
  PISTAS PQP, *p = NULL;
  voo* v = NULL;
  No<voo> *no = NULL;
  int Nvs = 0; // número de vôos sorteados
  int tNvs = 0; // Total de vôos sorteados ao longo da simulação
  // Tipos de vôos sorteados a cada tempo
  int Nps = 0, Nds = 0, Nes = 0;
  int tnpe = 0; // total pousos de emergência
  // Total de vôos sorteados ao longo da simualação por tipo de vôo
  int tNps = 0, tNds = 0, tNes;
  int j;
  bool insflag = false; // Flag para checar se o nó foi inserido, e tomar as devidas providências (útil para corrigir bugs estranhos de novos vôos sendo criados no mesmo endereço que antigos que já foram para a fila)
  char *infoVoo = NULL;
  Fila<voo> fFDP, fThecrash;
  fprintf(f, "\nInício da Simulação:\n");
  
  // Início da Simulação
  for (t = 0; t < T; t++){
    fprintf(f, "\n@@@@#* Tempo %d (%dª iteração de %d) *#@@@@\n\n", t, t+1, T);
    fprintf(f,"Situação das Pistas antes de atualizá-las com novos vôos, ou diminuição de seus tempos de travamento:\n");
    PQP.Contadores(f);
    
    // Atualiza a situação da fila e das Pistas antes de sortear e inserir novos vôos, e Gera Estatísticas
    if (!F.vazia() || (!PQP.livreDecolar() || PQP.livrePousar() == NULL) ){
      estatisticas(t, f, F, PQP, tmPouso, tmDecolagem, mcPousados, mcPousar, mcsPousados, totalPousados, totalDecolagens, totalEmergencia, Qemergencia, nDecolagens, nPousados, tnpe); 
      F.atualiza();
      // chance de delete (debug)
      PQP.Decrementa(); // decrementa o tempo de travamento das pistas
      fprintf(f, "\nAtualização das Pistas de PQP antes da comunicação dos novos vôos\n");
      PQP.Contadores(f);
    }
    fprintf(f, "Comunicação de novos vôos com a torre.\n");
    if ( sorteiaPr(PrV) ) // Sorteia se sorteará vôo
      if ( Nvs = sorteia(K) ){ // sorteia número de vôos (se 0, continua não sorteando vôo algum)
	for (j = 0; j < Nvs; j++){ // itera até serem criados todos os vôos
	  v = NULL;
	  v = criaVoo(cia, porto, Ncia, Np, C, V, PrE);
	  if (v->emergencia) // Conta o tipo de vôo sorteado
	    Nes++;
	  else if(!v->Ctorre)
	    Nps++;
	  else
	    Nds++;
	  // Checa se as pistas e as filas estão livres e se dá para pousar os aviões antes de o inserir nelas
	  if (PQP.livrePousar() || PQP.livreDecolar()){ // Se pistas estiverem livres...
	    // testando se dá para botar na pista vôo de emergência
	    if (v->emergencia){
	      if (F.vazia())
		PQP.emergencia(v);
	    }
	    else if (PQP.livrePousar() && !v->Ctorre)
	      PQP.pousar(v);
	    else if (PQP.livreDecolar() && v->Ctorre)
	      PQP.decolar(v);
	    else if (v->Ctorre && F.vazia() && PQP.livrePousar()) // Decola o avião na pista de pouso se a fila estiver vazia e PQP.D ocupada
	      PQP.pousar(v);
	    if (PQP.mensagem != NULL){
	      infoPistas = PQP.mensagem;
	      fprintf(f, "%s\n", infoPistas);
	      free(infoPistas);
	      infoPistas = PQP.mensagem = NULL;
	      v = NULL;
	    }
	  }
	  if (v){ // Não conseguiu botar vôo criado nas pistas
	    no = new No<voo>(v); // new (debug)
	    insflag = F.inserirORD(no);
	    if (insflag == false){ // monitorar. chance de ser necessário um delete?
	      j--; // Se vôo não inserido, inserir outro vôo sem prejudicar a contagem
	      infoVoo = v->printString();
	      fprintf(f, "Vôo no endereço de memória %x já inserido na fila ordenada.\n%s\n", v, infoVoo);
	      free(infoVoo);
	      infoVoo = NULL;
	    }
	  }
	}
	fprintf(f, "Vôos sorteados nesta iteração: %d\n", Nvs);
	fprintf(f, "Por tipo de vôo:\nEmergência: %d, Pousos, %d, Decolagens %d\n", Nes, Nds, Nps);
	tNvs += Nvs;
	tNes += Nes;
	tNds += Nds;
	tNps += Nps;
	fprintf(f, "\nTotal de vôos sorteados ao longo da simulação: %d\n", tNvs);
	fprintf(f, "Por tipo de vôo:\nEmergência %d, Pousos %d, Decolagens %d\n", tNes, tNds, tNps);
	Nes = Nds = Nps = 0;
      }
    
    // Tentar colocar vôos da fila nas Pistas
    if (!F.vazia()){ // Detectado looping infinito, se não conseguir usar as pistas
      // Verificando se aviões cairão
      analLOG = analFila(PQP, &F, (int) tmPouso, 1, fFDP, fThecrash);
      fprintf(f, "%s\n", analLOG);
      free(analLOG);
      analLOG = NULL;
      // Verificando se há vôos que precisam ser redirecionados
      analLOG = analFila(PQP, &F, (int) tmPouso, 0, fFDP, fThecrash);  
      fprintf(f, "%s\n", analLOG);
      free(analLOG);
      analLOG = NULL;
      v = NULL;
      while ((PQP.livreDecolar() || PQP.livrePousar()) && v != F.mostraINI() && !F.vazia()){ // Tenta usar as pistas
	if ((PQP.livrePousar() && !F.mostraINI()->Ctorre) && F.mostraINI()->emergencia){
	  PQP.decidePistaUsada(F.removeOrd());
	}
	else if ((PQP.livreDecolar() || PQP.livrePousar()) && F.mostraINI()->Ctorre){
	  PQP.decidePistaUsada(F.removeOrd());
	}
	if (PQP.mensagem != NULL){
	  infoPistas = PQP.mensagem;
	  fprintf(f, "%s\n", infoPistas);
	  free(infoPistas);
	  infoPistas = PQP.mensagem = NULL;
	}
	v = F.mostraINI();
      }
      fprintf(f, "\nTamanho da fila de espera para PQP (usar as pistas do aeroporto): %d\n", F.tam());
    }
  }
  // Calculando estatísticas
  fprintf(f, "\n@@@#* Estatísticas finais da simulação: *#@@@\n\n");
  estatisticas(t, f, F, PQP, tmPouso, tmDecolagem, mcPousados, mcPousar, mcsPousados, totalPousados, totalDecolagens, totalEmergencia, Qemergencia, nDecolagens, nPousados, tnpe);
  fprintf(f, "Fração de vôos de emergência que usaram as pistas: %f\%\n", tNvs == 0 ? 0 : (float) 100 * totalEmergencia / tNvs );
  fprintf(f, "Fração de vôos que pousaram: %f\%\n", tNvs == 0 ? 0 : (float) 100 * totalPousados / tNvs );
  fprintf(f, "Fração de vôos que decolaram: %f\%\n", tNvs == 0 ? 0 : (float) 100 * totalDecolagens / tNvs);
  fprintf(f, "\nFração de vôos de emergência sorteados: %f\%\n", tNvs == 0 ? 0 : (float) 100 * tNes / tNvs );
  fprintf(f, "Fração de pousos sorteados: %f\%\n", tNvs == 0 ? 0 : (float) 100 * tNps / tNvs );
  fprintf(f, "Fração de decolagens sorteadas: %f\%\n", tNvs == 0 ? 0 : (float) 100 * tNds / tNvs );
  fprintf(f, "Fração de vôos ainda na fila que não pousaram: %f\%\n", tNvs == 0 ? 0 : (float) 100 * F.tam() / tNvs);
  fprintf(f, "Fração de vôos desviados: %f\%\n", tNvs == 0 ? 0 : (float) 100 * fFDP.tam / tNvs);
  fprintf(f, "Fração de vôos que cairam: %f%\n", tNvs == 0 ? 0 : (float) 100 * fThecrash.tam / tNvs);
  fprintf(f, "Situação das Pistas de PQP após a simulação:\n");
  PQP.Contadores(f);
  fprintf(f, "\n@@@@#* Fim da Simulação! *#@@@@");
  // esvaziando eventual uso de memória e fechando os arquivos
  // delete F;
  // delete PQP;
  // if (no)
  //   delete no;
  // no = NULL;
  // if (v)
  //   delete v;
  // v = NULL;
  fclose(f);
}

// Imprime Sintaxe do programa em caso de entrada errada
void printSintaxe(char **argv){
  printf("%s aeroportos companhias K C T V PrV PrEmergencia\n", argv[0]);
  printf("Onde:\n");
  printf("K            = Máximo número de vôos a serem sorteados em cada instante de tempo\n");
  printf("C            = Número máximo de combustível sorteado para cada vôo na simulação, em unidades de tempo\n");
  printf("T            = Tempo de duração da simulação\n");
  printf("V            = Horas de vôo sorteada para um avião a decolar\n");
  printf("PrV          = Probabilidade de ser sorteado um vôo (inteiro, de 0 a 100)\n");
  printf("PrEmergencia = Probabilidade de ser sorteado um vôo de emergência (inteiro, de 0 a 100)\n");
}

// Analisa erro de entrada
int anal(int argc, char **argv){
  if(argc != 9){
    cout << "Número de argumentos inválido!" << endl;
    return 1;
  }
  if (!fopen(argv[1], "r")){
    cout << "Erro ao abrir arquivo de aeroportos!" << endl;
    return 2;
  }
  if (!fopen(argv[2], "r")){
    cout << "Erro ao abrir arquivo de companhias aéreas!" << endl;
    return 3;
  }
  if ( (atoi(argv[7]) > 100 || atoi(argv[8]) > 100) || (atoi(argv[7]) < 0 || atoi(argv[8]) < 0) ){
    cout << "Probabilidades não devem superar 100 nem podem ser negativas!" << endl;
    return 4;
  }
  if ( atoi(argv[3]) < 0 || atoi(argv[4]) < 0 || atoi(argv[5]) < 0 || atoi(argv[6]) < 0){
    cout << "Erro: um ou mais dos argumentos é menor que zero!" << endl;
    return 5;
  } 
  return 0; // Sem erros
}

int main(int argc, char **argv){
  if (anal(argc, argv)){
    printSintaxe(argv);
    return 1;
  }
  
  // Leitura dos argumentos
  int K = atoi(argv[3]), C = atoi(argv[4]), T = atoi(argv[5]),
    V = atoi(argv[6]), PrV = atoi(argv[7]), PrE = atoi(argv[8]);
  // Para a leitura dos parâmetros dos arquivos
  char *fportos = argv[1], *fcias = argv[2];
  int ncias, nportos;
  char **cias, **Desccia, **portos, **Descportos;

  // Carregamento dos Aeroportos e Companhias
  portos = LeArq(fportos, nportos, &Descportos);
  cias = LeArq(fcias, ncias, &Desccia);
  int i;
  cout << "Companhias Operando no Aeroporto" << endl;
  for(i = 0; i < ncias; i++)
    cout << cias[i] << ": " << Desccia[i] << endl;
  cout << "Aeroportos de Origem/Destino das Companhias" << endl;
  for(i = 0; i < nportos; i++)
    cout << portos[i] << ": " << Descportos[i] << endl;

  // Arquivo de Armazenamento de Log da simulação
  char fsaida[256];
  sprintf(fsaida, "logK%03dC%03dT%03dV%03dPrV%03dPrE%03d", K, C, T, V, PrV, PrE);
  FILE *log = fopen(fsaida, "w");
  fprintf(log, "---- Simulação de controle de tráfego do aeroporto internacional Pátria Que Progride (PQP) ----\n");
  fprintf(log, "K %d, C %d, T %d, V %d, PrV %d PrE %d\n", K, C, T, V, PrV, PrE);
  cout << "\nSimulação de controle de tráfego do aeroporto internacional Pátria Que Progride (PQP)" << endl;
  cout << "Estatística e dados escritos no arquivo de log:\n" << fsaida  << endl;

  srand(1917);// semente para os sorteios
  // Chama a Simulação. Arquivo log será fechado dentro do programa
  SIMULACAO(log, portos, nportos, cias, ncias, K, C, T, V, PrV, PrE);

  // liberação de memória
  for(i = 0; i < ncias; i++){
    free(cias[i]);
    free(Desccia[i]);
    cias[i]    = NULL;
    Desccia[i] = NULL;
  }
  free(cias);
  free(Desccia);
  cias = NULL;
  Desccia = NULL;
  for (i = 0; i < nportos; i++){
    free(portos[i]);
    free(Descportos[i]);
    portos[i]     = NULL;
    Descportos[i] = NULL;
  }
  free(portos);
  free(Descportos);
  portos     = NULL;
  Descportos = NULL;
  return 0;
}
