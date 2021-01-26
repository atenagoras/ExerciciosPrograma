#ifndef FILAORD
#define FILAORD
#include "voo.h"
#include "Fila.h"

// Idéia: Fila Ordenada agora trabalha com 3 subfilas diferentes, cuja inserção e remoção é hierárquica
class FilaOrd{
public:
  FilaOrd();
  ~FilaOrd();
  
  Fila<voo> Emergencia, Aterrizagem, Decolagem;
  // Insere vôo na fila de forma ordenada. true, se inserido, false se não for inserido
  bool inserirORD(No<voo> *no);
  
  void reduzCombustivel(); // reduz combustível de vôos a pousar
  void atrasa(); // incrementa o tempo de espera dos vôos a decolar
  void atualiza(); // utiliza as funções acima para atualizar toda a lista
  // Inserem vôo nas filas: true, se vôo inserido, false se não inserido
  bool inserirEmergencia(No<voo> *no);
  bool inserirAterrizagem(No<voo> *no);
  bool inserirDecolagem(No<voo> *no);
  // checa se vôo no início da fila está esperando mais de 10% do tempo de vôo estimado
  bool dizimo(Fila<voo> &P);
  voo* removeOrd(); // remove ordenadamente, obedecendo a prioridade das filas
  voo* removeDecolagem();
  void terminateFilas();
  voo* mostraINI();
  bool vazia();
  int tam(); // retorna o tamanho da Fila Ordenada (soma o tamanho de todas as filas
};
#endif // FILAORD
