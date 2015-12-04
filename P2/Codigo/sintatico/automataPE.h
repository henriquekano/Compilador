#ifndef AUTOMATA_PE_H
  #define AUTOMATA_PE_H
  #include <stdio.h>
  #include "../utils/bool.h"
  #include "../utils/list.h"
  #include "../utils/automata2.h"
  #include "../utils/token.h"
  #include "../utils/table.h"

  #define CALL_SUBMACHINE INT_MIN << 2

  typedef int AutomataId;

  typedef struct AutomataPE{
    struct List stack; //a pilha...
    int numberOfMachines; //numero de maquinas consideradas
    struct Table *transitionTables; //TODAS as tabelas de transicao das maquinas em um vetor ordenado por um machineId (enum?)
    struct Table *subMachineCall; //array de Tabelas auxiliar machine_id x token que diz, para cada tipo possivel de token, qual eh a prox maquina (id) para a maquina atual
    struct Table *afterCallStates; //tabela auxiliar machine_id x machine_id que diz qual o estado de uma maquina apos chamar outra
    struct Table *finalStates;
    Automata2 currentMachine; //maquina sendo corrida agora
  }AutomataPE;

  AutomataPE automataPE_create(AutomataId currentMachine, int numberOfMachines, 
    Table *transitionTables, Table *subMachineCall, Table *afterCallStates, Table *finalStates);
  void automataPE_destroy(AutomataPE *a);
  bool automataPE_run(AutomataPE *a, FILE *input, Token *t);
  void automataPE_goto_next_state(AutomataPE *a, Token *t);
  int automataPE_next_state(AutomataPE *a, Token *t);
  int automataPE_current_state(AutomataPE *a);
  AutomataId automataPE_current_machineId(AutomataPE *a);

  void list_destroy_automata2(void *data);
#endif //AUTOMATA_PE_H