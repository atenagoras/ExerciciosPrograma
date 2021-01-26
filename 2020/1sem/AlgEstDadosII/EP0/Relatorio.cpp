/*-+****** Relatório da Simulação do Aeroporto Pátria Que Progride (PQP) *****-+
 | Nome: Atenágoras Souza Silva              Nº USP: 5447262                   |
 * Obs: O relatório não, apesar da extensão não é um programa.                 *
 *      Ele foi feito desta forma para ser lido numa IDE com identação e       *
 *      destaques de sintaxe para uma leitura mais agradável                   *
 *                      Índice:                                                *
 *  1) Instruções de uso                                                       *
 *  2) Explicação do trabalho realizado, do funcionamento e fluxo de dados     *
 *  3) Funções principais e classes utilizadas                                 *
 *  4) Bugs Conhecidos                                                         *
 *  5) Resultados                                                              *
 *  6) Discussão e comparação com os aeroportos de Congonhas e de Guarulhos    *
 |  7)Conclusão                                                                |
 +-****************************************************************************/

// Instruções de Uso
sessão1: InstruçõesDeUso(){
  /***************************************************************************-+
  | Há um Makefile, e basta digitar 'make' na linha de commando compilá-lo:    |
    $ make
    O programa lê na linha de comando os seguintes parâmetros:
    aeroportos: Arquivo contendo os aeroportos utilizados na simulação
    companhias: Arquivo contendo as companhias aéreas da imulação
    K  : N° Máximo de vôos sorteados em cada intervalo de tempo       
    C  : Tamanho máximo de combustível do vôo sorteado                
    T  : Unidades de Tempo da Simulação                               
    V  : N° Máximo de horas de vôo de cada vôo sorteado para decolagem
    PrV: Probabilidade de um vôo ser sorteado                         
    PrE: Probabilidade de um vôo de emergência ser sorteado           
    
    Desta forma, o programa deve ser chamado com:
    ./pqp aeroportos companhias K C T V PrV PrE
    Exemplo:
  - ./pqp aeroportos companhias 4 3 1 5 100 40                                   |
  +-*****************************************************************************/
}

// Explicação do trabalho realizado, do funcionamento e fluxo de dados
sessão2: ExplicaçãoDoTrabalhoRealizadoDoFuncionamentoEFluxoDeDados(){
  // Ítem 1: Introdução, Explicação e trabalho realizado
  Item1 Explicação(){
    /*-                                                                            -+
    | A simulação foi pensada para colocar a segurança como principal prioridade,   |
      a ponto de até mesmo vôos de emergência poderem ser realocados, caso haja
      necessidade.
      A estratégia de fila de prioridade adotada foi a de uma fila de inserção 
      ordenada, e dentro dessa fila ordenada, tem 3 filas simples, uma para vôos
      de emergência, outra para aterrizagem e outra para decolagem.
      Ter 3 filas dentro de uma única fila ordenada foi uma estratégia pensada
      para não haver necessidade de fazer buscas por decolagem, por exemplo, no
      fim da fila que fossem muito custosas.

      Foram estudados 3 cenários de utilização do aeroporto:
      - Subutilização: São sorteados poucos vôos a cada iteração, inclusive com 
      baixa probabilidade de novos vôos serem sorteados, e baixa probabilidade de
      vôos de emergência.
      Deste modo, não há muitos problemas de gerenciamento da fila, nem risco de 
      aviões cairem, ou vôos sendo desviados. A fila trabalha vazia ou pouco
      utilzada na maior parte do tempo.
      - Operação normal: Neste caso, em geral, mais vôos se comunicam com a torre 
      de controle do que o número de pistas disponíveis, mas não muito mais.
      Neste caso, a fila cresce, mas ainda poucos vôos precisam ser redirecionados
      Há aumento de probabilidade de vôos serem sorteados, bem como maior chance
      de vôos emegência, também
      - Sobreutilização e estresse: Neste caso, muito mais vôos se comunicam com a
      torre, numa ordem de grandeza uma ou duas vezes maior do que o número de
      pistas a cada unidade de tempo. Vôos de emergência tem probabilidade maior
      ou igual a 60% de ocorrer,e há chance maior do ou igual a 80% dos vôos serem
      sorteados. A maioria dos vôos sorteados possuem pouco combustível, ou tem
      previsão para voar de poucas unidades de tempo, em caso de decolagem.
      Decolagens, quando são sorteadas, possuem o dobro de combustível do tempo
      estimado de vôo, por precaução. Normalmente, vôos decolam com pelo menos 
      2/3 de combustível a mais do que o necessário para alcançar o destino.
      O vôo do time da Chapecoense foi exemplar para mostrar como não fazer
      economia no quesito segurança.
      
      Para tentar garantir que os vôos não irão cair, foi criada uma função que 
      faz mais cálculos além do sugerido no enunciado para redirecionar os vôos
      cujo combustível pode acabar antes de chegar na pista, bem como uma função
      que o derruba em caso de insucesso.
      
      Foram calculados mais dados estatísticos do que o sugerido no enunciado
      para que este programa seja mais útil na simulação de uma situação crítica
      próxima do real.
      Foi criado um programa chamado Idoneidade para testar o balanceamento das
      funções de sorteio.cpp

      Optou-se por registrar a saída do programa em arquivo de log.                  
      Para facilitar o trabalho de testar os casos, criei scripts que chamam o
    | programa para cada um dos casos.                                               |
    +-                                                                             -*/
  }
  
  // Ítem 2: Funcionamento e Fluxo de Dados
  Ítem2 FluxoDeDados(){
    /*
      - Looping de tempo 0 a T
         - Sorteia Nº de Vôos
             - Tenta Inserí-los nas Pistas
	     - Coloca os não inseridos nas Pistas na Fila Ordenada
	     - Checa se os vôos na fila precisam ser redirecionados, ou precisam cair
	       Caso sejam redirecionados, o serão para o aeroporto Familícia Do
	       Presidente (FDP)
	 - Calcula Estatísticas
      - Calcula estatísticas finais da simulação
     */
  }
}

// Funções Principais e Classes utilizadas
sessão3: FunçõesPrincipaisClassesUtilizadas(){
  Ítem1 PrincipaisArquivosFontes(){
    /*
      - pqp.cpp: Programa principal, que executa a lógica de operação do aeroporto
      - Fila.h, Fila.tcc, Fila.cpp: Cabeçalho e implementação dos templates de
        fila simples.
      - voo.cpp: classe para criar os vôos que se comunicam com a torre
      - sorteio.cpp: Faz várias operações de seleção aleatória de variáveis, bem
        como a criação de vôos que se comunicam com a torre.			
      - FilaOrd.cpp: Fila Ordenada, com algorítimos e 3 filas simples para usar no
        gerenciamento dos vôos que se comunicam com a torre do aeroporto.
      - Pistas.cpp: Traz as classes de gerenciamento das pistas do aeroporto
    */
  }

  // Ítem 2: Principais funções de pqp.cpp
  Ítem2 FunçõesDe_pqp(){
    // Realiza a simulação de controle de tŕafego
    void SIMULACAO(FILE *f, char **porto, int Np, char **cia, int Ncia, int K, int C, int T, int V, int PrV, int PrE);
    /*
       SIMULACAO() recebe o arquivo em que os dados serão gravados, os dados de entrada, e executa a simulação
     */
    
    // analFila(): Analiza Fila para atualizá-la e/ou tomar deciões a respeito dos vôos (redirecioná-los, ou abatê-los, se necessário)
    // Retorno: String com relatório do que foi feito nesta função
    /*
       analFila recebe as Pistas do aeroporto, a fila ordenada, o tempo médio de Pouso, a fila de aviões que devem ser redirecionados, 
       e a fila de aviões que serão abatidos (para tentar contornar problemas de falha de segmentação de memória ao debugá-los, tomou-se
       a decisão de armazenar todos os vôos que saem da Fila Ordenada ou entram nas Pistas em outras filas, liberando a memória de forma unificada
       no final do programa, ao deletar todas as filas).
       De posse desses dados, analFila chama outras subfunções para tomar as decisões a respeito dos vôos.
     */
    char *analFila(PISTAS &P, FilaOrd *F, int tmPouso, int how, Fila<voo> &fFDP, Fila<voo> &fThecrash);

    // Estima o tempo para o avião pousar de acordo com sua posição na fila (útil para o cálculo mais preciso de quando um vôo deve ser desviado)
    /* Esta função é chamada por analFila() para checar se um vôo deve ser redirecionado, ou não
     */
    int Tpouso(PISTAS &P, FilaOrd &F, No<voo> *no);
  }
  
  // Cabeçalho para Fila Simples Fila.h
  Ítem3 Fila_h(){
    // Classe Nó e suas funções de gerenciamento:
    template <class Item>
      class No{
    public:
      No<Item> *ant, *prox;
      Item *item;
      No();
      No(Item *info);
      ~No();
    };

    // Classe Fila simples e suas funções de gerenciamento
    template <class Item>
      class Fila{
    public:
      Fila();
      ~Fila();
      bool vazia();
      bool inserirINI(No<Item> *no);
      bool inserirFIM(No<Item> *no);
      bool inserirMeio(No<Item> *no, No<Item> *cmp);
      // Obs: As funções de remoção de Item não removem-no da memória, apenas os retiram da lista. a remoção deverá ser feita por outras funções do programa principal ou nas classes Pistas ou Pista
      Item* removeINI();
      Item* removeFIM();
      Item* remove(No<Item> *no); // sempre puxa o nó seguinte para o lugar do nó removido
      Item* mostraMeio();
      Item* mostraINI();
      Item* mostraFIM();
      No<Item> *ini, *fim;
      int tam;
    };
  }

  // Ítem : Cabeçalho para a classe voo, e suas funções de gerenciamento (voo.h)
  Ítem4 voo_h(){
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
      char *printPOUSO(); // função auxiliar à printString();
      char *printDECOLAGEM(); // função auxiliar à printString();
      char *printString(); // Imprime vôo em uma string
    };
  }

  // Funções para sorteio utilizadas para sortear vôo
  Ítem5 sorteio_h(){
    int sorteia(int x); // sorteia um inteiro entre 0 a x.
    bool sorteiaPr(int Pr); // sorteia verdadeiro com probabilidade Pr.
    // cria vôo a partir de parâmetros sorteados
    voo* criaVoo(char **cia, char **portos, int tcia, int tportos, int C, int V, int Pr = 0);
  }
  
  // Fila Ordenada e suas funções de gerenciamento
  Ítem6 FilaOrd_h(){
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
  }

  // Cabeçalho para as classes de gerenciamento das pistas de PQP Pistas.h
  Ítem7 Pistas_h(){
    class Pista{
    public:
      voo *V;
      int tcount;
      char *label; // Nome da Pista (para informar ao usuário quando pista for usada)
      Pista(const char *Label);
      ~Pista();
      bool liberado(); // informa se a pista está liberada para uso
      bool usarPista(voo *v); // recebe vôo para usar pista
      int Contador(); // informa status do contador
      voo* decrementa(); // decrementa o contador
      char* imprime(); // imprime o vôo que está usando a pista
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
  }
}

// Sessão 4: Bugs Conhecidos
sessão4: BugsConhecidos(){
  /*-                                                                              -+
  |  - Memory leaks: Eu corrigi muitos erros de memory leak, e até criei um caso    |
     para investigar isto, que insere apenas um vôo.
     Não sei, entretando corrigir o último que sobrou, já que mesmo com a inserção 
     de apenas um caso não consegui encontrá-lo, e o valgrind não ajudou neste
     último.
     - Alguns vôos são desviados quando a fila é pequena, e há combustível para
     pousar. Como estou muito atrasado, não vou tentar corrigir este bug, mas esse
     é mais fácil de corrigir.
     - Falsos positivos para vôos desviados e que cairam.
     - Parece haver alguma coisa errada com o cálculo de algumas médias
     - Combustível negativo: Há um caso exagerado com o sorteio de até 100 
     inserções, e máximo de combustível de 3 unidades de tempo, 100% de 
     probabilidade de sorteio de vôo, 1000 unidades de tempo de simulação e 40% de
     chances de geração de vôos de emergência. Neste caso, não pude mais investigar
     o problema, pois eu demorei, em média 1 semana para encontrar e corrigir cada
     bug crítico, e já estou muito atrasado para entregar este trabalho.
   |  O arquivo de log deu mais de 800Mb.                                           |
   +-                                                                             -*/
}

// Sessão 5: Resultados
sessão5: Resultados(){
  /* Os resultados aqui exibidos se referem à situação final das simulações.
     Se necessário, serão apresentados resultados de um intervalo especifico. 
   */
  
  /*
    Caso 1: Subutilização

      Caso criado para investigar, memory leak por gerar apenas um vôo
      - K = 1, C = 3, T = 4, V = 5, PrV = 100, PrE = 40
      
      @@@#* Estatísticas finais da simulação: *#@@@


      Dados e estatísticas no tempo 4 da simulação:

      Nenhum avião esperando para pousar ou decolar neste tempo!
      Média de Combustível dos aviões que pousaram no tempo atual: 0.000000
      Nº de pousos no tempo atual: 0
      Nº de decolagens no tempo atual: 1
      Nº de vôos de emergência usando as Pistas no tempo atual: 0
      Média de Combustível dos voôs que pousaram na simulação até aqui: 0.000000
      Total de Pousos: 0
      Total de Decolagens: 1
      Total de vôos de emergência que usaram a pista: 0
      Total de vôos de emergência que pousaram: 0
      Tempo Médio para: Pouso: 0.000000 , Decolagem: 0.000000
      Fração de vôos de emergência que usaram as pistas: 0.000000%
      Fração de vôos que pousaram: 0.000000%
      Fração de vôos que decolaram: 100.000000%
      
      Fração de vôos de emergência sorteados: 0.000000%
      Fração de pousos sorteados: 0.000000%
      Fração de decolagens sorteadas: 100.000000%
      Fração de vôos ainda na fila que não pousaram: 0.000000%
      Fração de vôos desviados: 0.000000%
      Fração de vôos que cairam: 0.000000%
      Situação das Pistas de PQP após a simulação:
      
      Tempos das Pistas de PQP para destravamento (0 significa pista livre):
      P1: 0 P2: 0 Decolagem: 2
      -----------------------------------------------------------------------

      // Primeiro caso para investigar subutilização
      - K = 3, C = 10, T = 10, V = 10, PrV = 60, PrE = 10

      @@@#* Estatísticas finais da simulação: *#@@@
      
      
      Dados e estatísticas no tempo 10 da simulação:
      Aviões esperando para pousar:
      Nº Vôo: AV-876 - Pouso - Origem: MFM Combustível: 9 Emergência não
      Média de combustível dos aviões esperando para pousar: 9.000000
      Aviões esperando para decolar:
      Média de Combustível dos aviões que pousaram no tempo atual: 4.000000
      Nº de pousos no tempo atual: 1
      Nº de decolagens no tempo atual: 0
      Nº de vôos de emergência usando as Pistas no tempo atual: 0
      Média de Combustível dos voôs que pousaram na simulação até aqui: 1.000000
      Total de Pousos: 3
      Total de Decolagens: 6
      Total de vôos de emergência que usaram a pista: 1
      Total de vôos de emergência que pousaram: 1
      Tempo Médio para: Pouso: 3.000000 , Decolagem: 0.000000
      Fração de vôos de emergência que usaram as pistas: 9.090909%
      Fração de vôos que pousaram: 27.272728%
      Fração de vôos que decolaram: 54.545456%
      
      Fração de vôos de emergência sorteados: 9.090909%
      Fração de pousos sorteados: 36.363636%
      Fração de decolagens sorteadas: 54.545456%
      Fração de vôos ainda na fila que não pousaram: 9.090909%
      Fração de vôos desviados: 0.000000%
      Fração de vôos que cairam: 0.000000%
      Situação das Pistas de PQP após a simulação:
      
      Tempos das Pistas de PQP para destravamento (0 significa pista livre):
      P1: 2 P2: 1 Decolagem: 0
      -----------------------------------------------------------------------------

      1º Caso em que há possibilidade de, a cada iteração, gerar mais vôos que o número de pistas,
      mas ainda estamos no caso de subutlização por causa do baixo número de iterações de T
       
      - K 5, C 10, T 4, V 10, PrV 75 PrE 40

      @@@#* Estatísticas finais da simulação: *#@@@
      
      
      Dados e estatísticas no tempo 4 da simulação:
      Aviões esperando para pousar:
      Média de combustível dos aviões esperando para pousar: 0.000000
      Aviões esperando para decolar:
      Nº Vôo: QV-812 - Decolagem - Destino: PEK Tempo de Vôo Estimado: 11 Espera 0 Emergência: não
      Média de Combustível dos aviões que pousaram no tempo atual: 7.000000
      Nº de pousos no tempo atual: 1
      Nº de decolagens no tempo atual: 0
      Nº de vôos de emergência usando as Pistas no tempo atual: 0
      Média de Combustível dos voôs que pousaram na simulação até aqui: 3.500000
      Total de Pousos: 1
      Total de Decolagens: 4
      Total de vôos de emergência que usaram a pista: 1
      Total de vôos de emergência que pousaram: 1
      Tempo Médio para: Pouso: 4.000000 , Decolagem: 0.000000
      Fração de vôos de emergência que usaram as pistas: 12.500000%
      Fração de vôos que pousaram: 12.500000%
      Fração de vôos que decolaram: 50.000000%
      
      Fração de vôos de emergência sorteados: 25.000000%
      Fração de pousos sorteados: 12.500000%
      Fração de decolagens sorteadas: 62.500000%
      Fração de vôos ainda na fila que não pousaram: 25.000000%
      Fração de vôos desviados: 0.000000%
      Fração de vôos que cairam: 0.000000%
      Situação das Pistas de PQP após a simulação:
      
      Tempos das Pistas de PQP para destravamento (0 significa pista livre):
      P1: 1 P2: 2 Decolagem: 1
      ----------------------------------------------------------------------
      
      Caso 2 - Uso normal:
      - K = 5, C = 15, T = 20, V = 10, PrV = 60, PrE = 10

      Dados e estatísticas no tempo 20 da simulação:
      Aviões esperando para pousar:
      Nº Vôo: JS-599 - Pouso - Origem: BSB Combustível: 16 Emergência não
      Média de combustível dos aviões esperando para pousar: 16.000000
      Aviões esperando para decolar:
      Nº Vôo: TR-084 - Decolagem - Destino: MCP Tempo de Vôo Estimado: 5 Espera 0 Emergência: não
      Nº Vôo: AV-159 - Decolagem - Destino: FLN Tempo de Vôo Estimado: 7 Espera 6 Emergência: não
      Nº Vôo: CU-058 - Decolagem - Destino: BSB Tempo de Vôo Estimado: 10 Espera 9 Emergência: não
      Média de Combustível dos aviões que pousaram no tempo atual: 10.500000
      Nº de pousos no tempo atual: 2
      Nº de decolagens no tempo atual: 0
      Nº de vôos de emergência usando as Pistas no tempo atual: 0
      Média de Combustível dos voôs que pousaram na simulação até aqui: 0.875000
      Total de Pousos: 11
      Total de Decolagens: 14
      Total de vôos de emergência que usaram a pista: 1
      Total de vôos de emergência que pousaram: 1
      Tempo Médio para: Pouso: 1.000000 , Decolagem: 0.000000
      Fração de vôos de emergência que usaram as pistas: 2.857143%
      Fração de vôos que pousaram: 31.428572%
      Fração de vôos que decolaram: 40.000000%
      
      Fração de vôos de emergência sorteados: 5.714286%
      Fração de pousos sorteados: 45.714287%
      Fração de decolagens sorteadas: 48.571430%
      Fração de vôos ainda na fila que não pousaram: 14.285714%
      Fração de vôos desviados: 8.571428%
      Fração de vôos que cairam: 2.857143%
      Situação das Pistas de PQP após a simulação:
      
      Tempos das Pistas de PQP para destravamento (0 significa pista livre):
      P1: 2 P2: 2 Decolagem: 1
      
      ----------------------------------------------------------------------

      Caso 3 - SobreCarga e estresse:
      
      // Até vôos de emergência foram redirecionados, mas nenhum caiu
      K = 20, C = 3, T = 10, V = 5, PrV = 80, PrE = 60
      
      @@@#* Estatísticas finais da simulação: *#@@@
      
      
      Dados e estatísticas no tempo 10 da simulação:
      Aviões esperando para pousar:
      Média de combustível dos aviões esperando para pousar: 0.000000
      Aviões esperando para decolar:
      Nº Vôo: JS-596 - Decolagem - Destino: GYN Tempo de Vôo Estimado: 1 Espera 2 Emergência: não
      Nº Vôo: LA-253 - Decolagem - Destino: VTE Tempo de Vôo Estimado: 2 Espera 1 Emergência: não
      Nº Vôo: AV-141 - Decolagem - Destino: GRU Tempo de Vôo Estimado: 3 Espera 8 Emergência: não
      Nº Vôo: JS-948 - Decolagem - Destino: NVT Tempo de Vôo Estimado: 3 Espera 8 Emergência: não
      Nº Vôo: LA-005 - Decolagem - Destino: MCZ Tempo de Vôo Estimado: 3 Espera 3 Emergência: não
      Nº Vôo: G3-038 - Decolagem - Destino: GYN Tempo de Vôo Estimado: 3 Espera 3 Emergência: não
      Nº Vôo: AV-998 - Decolagem - Destino: MAO Tempo de Vôo Estimado: 3 Espera 3 Emergência: não
      Nº Vôo: RG-624 - Decolagem - Destino: PVG Tempo de Vôo Estimado: 6 Espera 2 Emergência: não
      Média de Combustível dos aviões que pousaram no tempo atual: 0.000000
      Nº de pousos no tempo atual: 0
      Nº de decolagens no tempo atual: 0
      Nº de vôos de emergência usando as Pistas no tempo atual: 0
      Média de Combustível dos voôs que pousaram na simulação até aqui: 0.000000
      Total de Pousos: 3
      Total de Decolagens: 10
      Total de vôos de emergência que usaram a pista: 2
      Total de vôos de emergência que pousaram: 0
      Tempo Médio para: Pouso: 3.000000 , Decolagem: 0.000000
      Fração de vôos de emergência que usaram as pistas: 2.469136%
      Fração de vôos que pousaram: 3.703704%
      Fração de vôos que decolaram: 12.345679%
      
      Fração de vôos de emergência sorteados: 62.962963%
      Fração de pousos sorteados: 14.814815%
      Fração de decolagens sorteadas: 22.222221%
      Fração de vôos ainda na fila que não pousaram: 32.098766%
      Fração de vôos desviados: 49.382717%
      Fração de vôos que cairam: 0.000000%
      Situação das Pistas de PQP após a simulação:
      
      Tempos das Pistas de PQP para destravamento (0 significa pista livre):
      P1: 1 P2: 1 Decolagem: 1
      -----------------------------------------------------------------------
      
      Com um tempo T de simulação maior, o que era um caso de subutilização
      se tornou um caso de estresse.
      - K = 5, C = 10, T = 20, V = 6, PrV = 75, PrE = 40

      @@@#* Estatísticas finais da simulação: *#@@@

      
      Dados e estatísticas no tempo 20 da simulação:
      Aviões esperando para pousar:
      Média de combustível dos aviões esperando para pousar: 0.000000
      Aviões esperando para decolar:
      Média de Combustível dos aviões que pousaram no tempo atual: 0.000000
      Nº de pousos no tempo atual: 0
      Nº de decolagens no tempo atual: 1
      Nº de vôos de emergência usando as Pistas no tempo atual: 0
      Média de Combustível dos voôs que pousaram na simulação até aqui: 0.000000
      Total de Pousos: 7
      Total de Decolagens: 17
      Total de vôos de emergência que usaram a pista: 2
      Total de vôos de emergência que pousaram: 1
      Tempo Médio para: Pouso: 2.000000 , Decolagem: 0.000000
      Fração de vôos de emergência que usaram as pistas: 4.545455%
      Fração de vôos que pousaram: 15.909091%
      Fração de vôos que decolaram: 38.636364%
      
      Fração de vôos de emergência sorteados: 38.636364%
      Fração de pousos sorteados: 22.727272%
      Fração de decolagens sorteadas: 38.636364%
      Fração de vôos ainda na fila que não pousaram: 20.454546%
      Fração de vôos desviados: 20.454546%
      Fração de vôos que cairam: 0.000000%
      Situação das Pistas de PQP após a simulação:
      
      Tempos das Pistas de PQP para destravamento (0 significa pista livre):
      P1: 2 P2: 0 Decolagem: 1
      
  */
}

// Discussão e Comparação com os aeroportos de Congonhas e Guarulhos
sessão6: Discussão(){
  /*
     Apesar dos bugs, o programa se saiu bem nos casos de subutilização e também nos
     de Sobrecarga. Nos dois casos, não houve nenhum avião derrubado.
     Nota-se, entretanto, que nos casos de sobrecarga e estresse, a maioria dos vôos
     que se comunicaram com a torre de PQP acabaram sendo desviados.
     
     No caso de utilização normal, ironicamente, é que o programa se comportou mal, 
     revelando todos os seus bugs.
     Normalmente, quando programa em C puro, sem a utilização de objetos, consigo
     fazer programas bem estruturados, com funções mais compactas, e uma
     organização muito mais modularizada, além de gerenciar bem a memória.
     Não é comum que eu apanhe do Valgrind como apanhei para fazer este programa.
     É incrível como ao aprender um novo paradigma, voltei a cometer todos os erros
     que um iniciante comete quando aprende programação pela primeira vez.
     Apesar das muitas funções, há muitas delas que poderiam ser métodos dentro das
     classes, e poderiam ter sua lógica escrita de forma muito mais simples.
     O fato de deixar tudo público dentro das classes parece que deixou o programa
     tão difícl de detectar os bugs quando os que são feitos usando variáveis
     globais.
     É até estranho que não perdia tanto o controle quando trabalhava apenas com
     estruturas em C.
     
     Em função dos bugs, o atual programa não representa uma simulação tão boa para
     uso normal do aeroporto, embora tenha se saído bem em casos de subutilização

     Ainda assim, serão feitas comparações com os aeroportos de Congonhas e
     Guarulhos.
   */
  // Ítem 1: Comparação com o Aeroporto de Congonhas
  Ítem1 Congonhas(){
    /*
       De acordo com dados da Infraero (http://www4.infraero.gov.br/aeroportos/aeroporto-de-sao-paulo-congonhas-deputado-freitas-nobre/sobre-o-aeroporto/caracteristicas/),
       o aeroporto de Congonhas possui duas pistas (uma principal, e outra auxiliar, e atende 592 por dia, entre 6h e 23h.
       São cerca de 33 slots por hora para utilizar o aeroporto, ou cerca de 2min
       para pousos ou decolagens, mais 2min fechada entre um vôo e outro.
       Antes do acidente da TAM, em 2007, o aeroporto tinha cerca de 40 slots para
       cada pista, o que caracterizaria a situação de sobrecarga.

       Uma utilização normal deste aeroporto seria o recebimento de algo em torno
       de 2 vôos para cada unidade de tempo (ou slot), e teríamos uma fila administrável.
       Acima disto, os acidentes mostraram que é perigoso, não necessariamente por
       conta do combustível.

       No aeroporto PQP há uma pista a mais que o aeroporto de Congonhas, e se
       considerarmos também um slot como sendo de 2min, o que daria 45 vôos por hora,
       Poderíamos trabalhar com 3 vôos solicitando permissão para o uso da pista,
       sendo um, necessariamente de decolagem, ou em condição de emergência, se
       utilizar a pista auxiliar.
     */
  }

  // Ítem 2: Comparação com o aeroporto Internacional de Guarulhos
  Ítem2 Guarulhos(){
    /*-                                                                             -+
    |  Em 2019, o Aeroporto Internacional de Guarulhos foi utilizado por 292.047     |
       vôos, o que resulta em 33 vôos por minuto. O aeroporto opera 24h por dia.
       (https://www.gru.com.br/pt/RelatorioOperacional/2019-12.pdf)
       Ele permite até 47 slots por hora.
       Apesar do aeroporto Internacional de Guarulhos também possuir duas pistas,
       ele funciona durante mais tempo que o aerporto de congonhas, mas por sua
       utilização no ano de 2019, podemos estimar slots de 1min20s, de modo que o
       que o programa simula um aeroporto com mais capacidade que o de Cumbica, a
       exemplo do de Congonhas. A diferença é que faz sentido considerar simulações
       24h, em vez de 12.
       As simulações, se fossem para Congonhas, simulariam até 40min de operação, e
       em Guarulhos, um pouco menos, em função do maior número de slots por hora,
       considerando sua capacidade máxima, e levando em consideração o caso máximo
       simulado.
       
       O que foi considerado funcionamento normal na sessão anterior já seria uma
     | situação de sobrecarga em ambos os aeroportos.                                |
     +-                                                                             */
  }
}

// Conclusão
sessão7: Conclusão(){
  /*-                                                                               -+
  |  Em função do meu noviciado com Orientação à Objetos e o cometimento de erros de |
     principiante, o programa tem bugs severos que não podem ser completamente
     representativos do funcionamento de um aeroporto real.
     Ainda assim, embora, pelo menos uma melhor revisão no processamento de
     estatísticas seja necesário, a simulação se comportou bem nos casos de
     subutilização do aeroporto, e de sobrecarga, não tenho redirecionado
     nenhum avião.
     Ironicamente, no que seria considerado um funcionamento normal, o programa
     não se comportou tão bem, desviando vôos sem necessidade.
     
     Embora seja verdade que a função Tpouso(), que auxilia os cálculos de
     redirecionamento, substima as pistas disponíveis para vôos de emergência e de
     mudança de prioridade para os que apresentam pouco combustível (deveria 
     considerar a utilização de todas as 3 pistas nessas situações), não está
     descartada a possibildade de haver mais erros, posto que no caso normal,
     vôos que claramente apresentavam combustível suficiente foram remanejados.
     A função Tpouso() foi projetada, de fato, para desviar vôos com combustível
     maior que 1, caso a fila esteja muito grande, em vez de esperar chegar numa
     situação crítica para fazer o redirecionamento, mas é necessário procurar bugs
     em AnalFila() para entender porque desvios equivocados estão acontecendo.
     
     Recomendações para reescrever este código:
     - Utilizar melhor o encapsulamento;
     - Modularizar mais as estapas e a estrutura do fluxo de dados
   | - Utilizar mais new e delete para gerenciar memória                             |
                                                                                   -*/
}
