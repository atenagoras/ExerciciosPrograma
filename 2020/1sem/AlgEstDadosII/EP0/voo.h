#ifndef VOO
#define VOO

class voo{
public:
  // cia: companhia de aviação a que o avião pertence
  // porto: aeroporto de origem ou destino do avião
  char *cia, *porto;
  
  // tvoo: tempo de vôo
  // espera: tempo de espera
  // Ctorre - Comunicação com a torre: 0 - aterrizagem, 1 - decolagem
  int nroAviao, combustivel, tvoo, espera, Ctorre;
  bool emergencia; // 1 - emergência, 0 - vôo normal
  voo(const char *CIA, const char *PORTO, int nro, int fuel, int tempo, int CTorre, bool Emergencia);
  ~voo();
  char *printPOUSO();
  char *printDECOLAGEM();
  char *printString();
};

#endif // VOO
