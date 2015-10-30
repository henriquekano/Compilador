#include <stdio.h>
#include <stdlib.h>

#include "automataPE.h"

//funcoes auxiliares
void list_destroy_automata2(void *data){
  free((Automata2*)data);
}


// a coisa de verdade
AutomataPE automataPE_create(AutomataId currentMachineId, int numberOfMachines, 
  Table transitionTables[numberOfMachines], Table subMachineCall[numberOfMachines], Table afterCallStates[numberOfMachines]){

  List stack;
  list_new(&stack, sizeof(struct Automata2), list_destroy_automata2);

  Table initialAutomataTable = transitionTables[currentMachineId];
  Automata2 firstAutomata = automata_create2(0, 
                                &initialAutomataTable);

  AutomataPE aPE = {stack, numberOfMachines, transitionTables, subMachineCall, afterCallStates, currentMachineId, firstAutomata};
  return aPE;
}

void automataPE_destroy(AutomataPE *a){
  list_destroy(&(a->stack));
  int i = 0;
  for(i = 0; i < a->numberOfMachines; i++){
    table_destroy(&(a->transitionTables[i]));
    table_destroy(&(a->subMachineCall[i]));
    table_destroy(&(a->afterCallStates[i])); 
  }
}

void automataPE_goto_next_state(AutomataPE *a, Token *t){
  //Pega o token, transforma em um index da tabela de transicao e tenta achar o prox estado
  int next_state = table_convert_to_index(&(a->currentMachine.table), t);
  if(next_state == CALL_SUBMACHINE){
    Table next_automata_table = a->subMachineCall[a->currentMachineId];
    int next_automata_id = table_get(&next_automata_table, a->currentMachineId, table_convert_to_index(&next_automata_table, t));

    Table next_automata_transition_table = a->transitionTables[next_automata_id];
    Automata2 next_automata = automata_create2(0,
                                &next_automata_transition_table);

    list_prepend(&(a->stack), &(a->currentMachine));
    a->currentMachine = next_automata;
    a->currentMachineId = next_automata_id;
    
  }else if(next_state == FINAL_STATE){
    if(list_size(&(a->stack)) > 0){
      Automata2 *nextAutomata = list_get_first(&(a->stack));
      a->currentMachine = *nextAutomata;

    }else{
      return;
    }
  }else if(next_state == ERROR_STATE){
    automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), t));
    return;
  }else{
    automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), t));
  }
}

int automataPE_next_state(AutomataPE *a, Token *t){
  return automata_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), t));
}

int automataPE_current_state(AutomataPE *a){
  return automata_current_state2(&(a->currentMachine));
}

AutomataId automataPE_current_machineId(AutomataPE *a){
  return a->currentMachineId;
}
