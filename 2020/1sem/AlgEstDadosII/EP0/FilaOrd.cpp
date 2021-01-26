#include<iostream>
#include "Fila.h"
#include "FilaOrd.h"
#include "voo.h"

FilaOrd::FilaOrd(){}

FilaOrd::~FilaOrd(){
  terminateFilas();
}

/* inserirORD(): Insere Nó na fila ordenadamente.
   Critérios:
   1º Emergência
   2º Aterrizagem
   3º Menos Combustível (Em caso de dois aviões que farão aterrizagem);
      Tempo Estimado de Vôo (Em caso de dois aviões que farão decolagem)
   Argumentos:
   No *no: Nó a ser inserido */
bool FilaOrd:: inserirORD(No<voo> *no){
  if (no->item->emergencia)
    return inserirEmergencia(no);
  else if (!no->item->Ctorre)
    return inserirAterrizagem(no);
  else
    return inserirDecolagem(no);
}

bool FilaOrd:: inserirEmergencia(No<voo> *no){
  if (Emergencia.vazia()){
    return Emergencia.inserirINI(no);
  }
  No<voo> *p = Emergencia.ini;
  while(p){
    if (no->item->Ctorre < p->item->Ctorre){ // 2º critério: Aterrizagem 
      return Emergencia.inserirMeio(no, p);
    }
    else if(no->item->Ctorre == p->item->Ctorre == 0) // 3º critério: Combustível
      if (no->item->combustivel < p->item->combustivel){
	return Emergencia.inserirMeio(no, p);
      }
      else if (no->item->Ctorre == p->item->Ctorre == 1) // 4º critério: Tempo de vôo
	if (no->item->tvoo < p->item->tvoo){
	  return Emergencia.inserirMeio(no, p);
	}
    p = p->prox;
  }
  return Emergencia.inserirFIM(no);
}

bool FilaOrd:: inserirAterrizagem(No<voo> *no){
  if (Aterrizagem.vazia()){
    return Aterrizagem.inserirINI(no);
  }
  No<voo> *p = Aterrizagem.ini;
  while(p){
    if (no->item->combustivel < p->item->combustivel){
      return Aterrizagem.inserirMeio(no, p);
    }
    p = p->prox;
  }
  return Aterrizagem.inserirFIM(no);
}

bool FilaOrd:: inserirDecolagem(No<voo> *no){
  if (Decolagem.vazia()){
    return Decolagem.inserirINI(no);
  }
  No<voo> *p = Decolagem.ini;
  while(p){
    if (no->item->tvoo < p->item->tvoo){
      return Decolagem.inserirMeio(no, p);
    }
    p = p->prox;
  }
  return Decolagem.inserirFIM(no);
}

voo* FilaOrd:: removeOrd(){
  if (!Emergencia.vazia()){ // 1º critério, remover emergência
    if (!Aterrizagem.vazia()){
      if (Aterrizagem.ini->item->combustivel == 0 && Emergencia.ini->item->combustivel > 0) // Se Combustível da fila de aterrizagem == 0, remover primeiro Aterrizagem
	return Aterrizagem.removeINI();
    }
    else if (!Decolagem.vazia()){
      if (dizimo(Decolagem) && !dizimo(Emergencia)) // Se a espera da decolagem >= 10% do tempo de vôo, remover primeiro Decolagem
	return Decolagem.removeINI();
      else if (dizimo(Decolagem) && dizimo(Emergencia)) 
	if (Decolagem.ini->item->tvoo > Emergencia.ini->item->tvoo)
	  return Decolagem.removeINI();
    }
    else
      return Emergencia.removeINI();
  }
  
  if (!Aterrizagem.vazia()){ // 2º critério, remover Aterrizagem
    if (!Decolagem.vazia() && Aterrizagem.ini->item->combustivel){ // Se a espera da decolagem >= 10% do tempo de vôo, remover primeiro Decolagem
      if (dizimo(Decolagem))
	return Decolagem.removeINI();
    }
    return Aterrizagem.removeINI();
  }
  
  if (!Decolagem.vazia()) // 3º critério, remover Decolagem
    return Decolagem.removeINI();
  return NULL;
}

bool FilaOrd:: dizimo(Fila<voo> &P){
  if (!P.ini->item->Ctorre)
    return false;
  if ( (float) P.ini->item->espera / P.ini->item->tvoo >= 0.1)
    return true;
  return false;
}

bool FilaOrd:: vazia(){
  if (Emergencia.vazia() && Aterrizagem.vazia() && Decolagem.vazia())
    return true;
  return false;
}

void FilaOrd:: terminateFilas(){
  // delete Emergencia;
  // delete Aterrizagem;
  // delete Decolagem;
}

void FilaOrd:: reduzCombustivel(){
  No<voo> *p;
  if (!Emergencia.vazia())
    for (p = Emergencia.ini; p; p = p->prox)
      if (!p->item->Ctorre)
	p->item->combustivel--;
  if (!Aterrizagem.vazia())
    for (p = Aterrizagem.ini; p; p = p->prox)
      p->item->combustivel--;
}

void FilaOrd:: atrasa(){
  No<voo> *p;
  if (!Emergencia.vazia())
    for (p = Emergencia.ini; p; p = p->prox)
      if (p->item->Ctorre)
	p->item->espera++;
  if (!Decolagem.vazia())
    for (p = Decolagem.ini; p; p = p->prox)
      p->item->espera++;
}

void FilaOrd:: atualiza(){
  reduzCombustivel();
  atrasa();
}

voo* FilaOrd:: mostraINI(){
  bool em = Emergencia.vazia(), at = Aterrizagem.vazia(), dec = Decolagem.vazia();
  if ( em && at && dec )
    return NULL;
  voo *Vem =  em == false ? Emergencia.ini->item:NULL,
    *Vat   =  at == false ? Aterrizagem.ini->item:NULL,
    *Vdec  = dec == false ? Decolagem.ini->item:NULL;
  
  if (Vem){ // 1º critério: mostrar emergência
    if (Vat){
      if (!Vat->combustivel && Vem->combustivel) // Se Combustível da fila de aterrizagem == 0, mostra primeiro Aterrizagem
	return Vat;
    }
    else if (Vdec){
      if (dizimo(Decolagem) && !dizimo(Emergencia)) // Se a espera da decolagem >= 10% do tempo de vôo, mostrar primeiro Decolagem
	return Vdec;
      else if (dizimo(Decolagem) && dizimo(Emergencia))
	if (Vdec->tvoo > Vem->tvoo)
	  return Vdec;
    }
    else
      return Vem;
  }
  if (Vat){ // 2º critério, mostrar Aterrizagem
    if (Vdec && Vat->combustivel ){ // Se espera da decolagem >= 10% do tempo de vôo, mostrar primeiro Decolagem
      if (dizimo(Decolagem))
	return Vdec;
    }
    return Vat;
  }
  return Vdec; // 3º critério, mostra Decolagem
}

int FilaOrd:: tam(){
  return Emergencia.tam + Aterrizagem.tam + Decolagem.tam;
}
