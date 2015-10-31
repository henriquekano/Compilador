#include <stdio.h>
#include <stdlib.h>

#include "automataPE.h"

#include "../lexico/analisador.h"
#include "machines.h"


//funcoes auxiliares
void list_destroy_automata2(void *data){
  free((Automata2*)data);
}


// a coisa de verdade
AutomataPE automataPE_create(AutomataId currentMachineId, int numberOfMachines, 
  Table transitionTables[numberOfMachines], Table subMachineCall[numberOfMachines], Table afterCallStates[numberOfMachines], Table finalStates[numberOfMachines]){

  List stack;
  list_new(&stack, sizeof(struct Automata2), list_destroy_automata2);

  Table initialAutomataTable = transitionTables[currentMachineId];
  Automata2 firstAutomata = automata_create2(currentMachineId,
                                0, 
                                &initialAutomataTable);

  AutomataPE aPE = {stack, numberOfMachines, transitionTables, subMachineCall, afterCallStates, finalStates, currentMachineId, firstAutomata};
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

// void automataPE_goto_next_state(AutomataPE *a, Token *t){
//   //Pega o token, transforma em um index da tabela de transicao e tenta achar o prox estado
//   int next_state = table_convert_to_index(&(a->currentMachine.table), t);
//   if(next_state == CALL_SUBMACHINE){
//     Table next_automata_table = a->subMachineCall[a->currentMachineId];
//     int next_automata_id = table_get(&next_automata_table, a->currentMachineId, t);

//     Table next_automata_transition_table = a->transitionTables[next_automata_id];
//     Automata2 next_automata = automata_create2(0,
//                                 &next_automata_transition_table);

//     list_prepend(&(a->stack), &(a->currentMachine));
//     a->currentMachine = next_automata;
//     a->currentMachineId = next_automata_id;
    
//   }else if(next_state == FINAL_STATE){
//     if(list_size(&(a->stack)) > 0){
//       Automata2 *nextAutomata = list_get_first(&(a->stack));
//       a->currentMachine = *nextAutomata;

//     }else{
//       return;
//     }
//   }else if(next_state == ERROR_STATE){
//     automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), t));
//     return;
//   }else{
//     automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), t));
//   }
// }

bool automataPE_run(AutomataPE *a, FILE *file){
  //Pega o token, transforma em um index da tabela de transicao e tenta achar o prox estado
  Token t = find_possible_token(file);
  int iterationPlusOne = 0;
  while(iterationPlusOne < 2){

    if(iterationPlusOne == 1){
      iterationPlusOne += 1;
    }

    if(reached_eof(file)){
      iterationPlusOne += 1;
    }

    int next_state = automata_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), &t));
    // verifica se e estado final
    if(is_value_in_array(next_state, a->finalStates->table[a->currentMachineId], a->finalStates->columns)){

      automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), &t));

      if(list_size(&(a->stack)) > 0){
        //desempilha a ultima maquina, vai para o prox estado 
        Automata2 *pop_automata = list_get_first(&(a->stack));
        a->currentMachine = *pop_automata;
        a->currentMachineId = pop_automata->id;

        t = find_possible_token(file);
      }else{
        return TRUE;
      }
    } else if(next_state == MINVALID_STATE){
      Table next_automata_table = a->subMachineCall[a->currentMachineId];
      int next_automata_id = table_get(&next_automata_table, 
                                       a->currentMachineId, 
                                      table_convert_to_index(&(a->currentMachine.table), &t));

      Table next_automata_transition_table = a->transitionTables[next_automata_id];
      Automata2 next_automata = automata_create2(
                                  next_automata_id,
                                  0,
                                  &next_automata_transition_table);

      list_prepend(&(a->stack), &(a->currentMachine));
      a->currentMachine = next_automata;
      a->currentMachineId = next_automata_id;
      
    }else if(next_state == ERROR_STATE){
      // automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), t));
      return FALSE;
    }else{
      automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), &t));
      t = find_possible_token(file);
    }
  }
  return TRUE;
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
