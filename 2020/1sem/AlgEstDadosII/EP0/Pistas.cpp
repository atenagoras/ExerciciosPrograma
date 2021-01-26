#include "voo.h"
#include "Fila.h"
#include "Pistas.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

Pista::Pista(const char *Label): V(NULL), tcount(0), label(strdup(Label)) {};
Pista::~Pista(){
  if (V) // O vôo pode ter sito apagado antes do objeto Pista ser desconstruido
    delete V;
  V = NULL;
  if (label)
    free(label);
  label = NULL;
} // eliminar vôo

bool Pista::liberado(){
  if (!tcount)
    return true;
  return false;
}

bool Pista::usarPista(voo *v){
  if (liberado()){
    V = v;
    tcount = 2;
    return true;
  }
  return false;
}

int Pista::Contador(){
  return tcount;
}

voo* Pista::decrementa(){
  if (tcount == 0)
    return NULL; // não permite contagem negativa
  tcount--;
  voo *retorno = NULL;
  if (tcount == 0){ // libera a pista
    voo *retorno = V;
    V = NULL; 
  }
  return retorno; // retorna o vôo que liberou a pista
}

/* Informa que a pista está sendo usada, e qual o uso (pouso, decolagem, GPs de F-Indy etc)
   Parâmetros:
   const char *uso: Informa o uso da pista
   Retorno: string com informações sobre o vôo que está usando a pista, como e nome da pista */
char* Pista:: imprime(){
  char *retorno, *infoVoo = V->printString();
  char Mensagem[512];
  sprintf(Mensagem, "Pista %s sendo utilizada para o vôo:\n",label);
 
  strcat(Mensagem, infoVoo);
  retorno = strdup(Mensagem);
  free(infoVoo);
  infoVoo = NULL;
  return retorno;
}

PISTAS::PISTAS(): mensagem(NULL), P1("P1"), P2("P2"), D("Decolagem") {};
PISTAS::~PISTAS(){
  if (mensagem)
    free(mensagem);
  mensagem = NULL;
}

Pista* PISTAS::livrePousar(){
  if (P1.liberado())
    return &P1;
  else if (P2.liberado())
    return &P2;
  else
    return NULL;
}

bool PISTAS::livreDecolar(){
  return D.liberado();
}

bool PISTAS::pousar(voo *v){
  Pista *p;
  if (p = livrePousar()){
    p->usarPista(v);
    mensagem = p->imprime();
    return true;
  }
  return false;
}

bool PISTAS::decolar(voo *v){
  Pista *p;
  if (livreDecolar()){
    D.usarPista(v);
    mensagem = D.imprime();
    return true;
  }
  else if (p = livrePousar()){
    p->usarPista(v);
    mensagem = p->imprime();
    return true;
  }
  return false;
}

bool PISTAS::emergencia(voo *v){
  Pista* p = NULL;
  if (v->emergencia || !v->combustivel || v->espera / v->tvoo >= 0.1)
    if (v->Ctorre == 0){
      p = livrePousar();
      if (p){
	p->usarPista(v);
	mensagem = p->imprime();
	return true;
      }
      else if (livreDecolar()){
	D.usarPista(v);
	mensagem = D.imprime();
	return true;
      }
    }
    else if (livreDecolar()){
      D.usarPista(v);
      mensagem = D.imprime();
      return true;
    }
    else{
      p = livrePousar();
      if (p){
	p->usarPista(v);
	mensagem = p->imprime();
	return true;
      }
    }
  return false;
}

bool PISTAS::decidePistaUsada(voo *v){
  if (v->emergencia || !v->combustivel || (v->Ctorre && v->espera / v->tvoo >= 0.1)) // casos de emergência, pane seca ou espera >= 10%
    return emergencia(v);
  if (!v->Ctorre) // pousar
    return pousar(v);
  return decolar(v);
}

void PISTAS::Decrementa(){
  voo *v;
  v = P1.decrementa();
  if (v)
    if (v->emergencia)
      Emergencia.inserirFIM(new No<voo>(v));
  v = P2.decrementa();
  if (v)
    if (!v->emergencia && !v->Ctorre)
      Pousos.inserirFIM(new No<voo>(v));
    else if (!v->emergencia && !v->Ctorre)
      Decolagens.inserirFIM(new No<voo>(v));
  v = D.decrementa();
  if (v)
    if (!v->emergencia && !v->Ctorre)
      Pousos.inserirFIM(new No<voo>(v));
    else if (!v->emergencia && !v->Ctorre)
      Decolagens.inserirFIM(new No<voo>(v));
}

bool PISTAS::livreEmergencia(){
  if (livrePousar() && livreDecolar())
    return true;
  return false;
}

void PISTAS::Contadores(FILE *f){
  fprintf(f, "\nTempos das Pistas de PQP para destravamento (0 significa pista livre):\n");
  fprintf(f, "P1: %d P2: %d Decolagem: %d\n\n", P1.Contador(), P2.Contador(), D.Contador());
}
