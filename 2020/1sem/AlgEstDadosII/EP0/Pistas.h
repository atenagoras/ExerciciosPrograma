#ifndef PISTAS_H
#define PISTAS_H
#include<stdio.h>
class Pista{
public:
  voo *V;
  int tcount;
  char *label; // Nome da Pista (para informar ao usuário quando pista for usada)
  Pista(const char *Label);
  ~Pista();
  bool liberado();
  bool usarPista(voo *v);
  int Contador(); 
  voo* decrementa();
  char* imprime();
};

class PISTAS{
public:
  Pista P1, P2, D;
  Fila<voo> Pousos, Decolagens, Emergencia;
  // recebe as mensagens de vôos pousando nas pistas
  char *mensagem;
  PISTAS();
  ~PISTAS();
  Pista* livrePousar(); // retorna a pista Livre para pouso
  bool livreDecolar(); // informa se pode haver decolagem 
  bool pousar(voo *v); // recebe avião para pouso
  bool decolar(voo *v); // recebe avião para decolagem
  bool emergencia(voo *v); // recebe vôos de emergências, pane seca ou com atraso >= 10%
  bool decidePistaUsada(voo *v); // decide, com base no vôo, que pista utilizar
  bool livreEmergencia(); // verifica se um vôo de emergência pode pousar
  void Decrementa(); // decrementa contagem de pista bloqueada
  void Contadores(FILE *f); // armazena os contadores das PISTAS em arquivo
};

#endif // PISTAS_H
