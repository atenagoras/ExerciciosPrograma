#include <iostream>
#include "voo.h"
#include <string.h>
#include <stdio.h>
#include "itoa.h"
#include <stdlib.h>
using namespace std;

voo::voo(const char *CIA, const char *PORTO, int nro, int fuel, int tempo, int CTorre, bool Emergencia){
  cia         = strdup(CIA);
  porto       = strdup(PORTO);
  nroAviao    = nro;
  combustivel = fuel;
  tvoo        = tempo;
  Ctorre      = CTorre;
  emergencia  = Emergencia;
  espera      = 0;
}

voo::~voo(){
  if (cia)
    free(cia);
  if (porto)
    free(porto);
  cia = NULL;
  porto = NULL;
}


char* voo::printPOUSO(){
  char String[1024];
  sprintf(String, "Nº Vôo: %s-%03d - Pouso - Origem: %s Combustível: %d Emergência %s\n", cia, nroAviao, porto, combustivel, emergencia == true ? "sim":"não");
  char *POUSO = strdup(String);
  return POUSO;
}

char* voo::printDECOLAGEM(){
  char String[1024];
  sprintf(String, "Nº Vôo: %s-%03d - Decolagem - Destino: %s Tempo de Vôo Estimado: %d Espera %d Emergência: %s\n", cia, nroAviao, porto, tvoo, espera, emergencia == true ? "sim":"não");
  char *DECOLAGEM = strdup(String);
  return DECOLAGEM;
}

char* voo::printString(){
  if (!Ctorre)
    return printPOUSO();
  return printDECOLAGEM();
}
