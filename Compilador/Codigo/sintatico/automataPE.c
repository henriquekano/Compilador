#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automataPE.h"

#include "semantic_actions.h"
#include "../lexico/analisador.h"
#include "machines.h"

bool automataPE_is_final_state(int state, AutomataPE *a);
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

  AutomataPE aPE = {stack, numberOfMachines, transitionTables, subMachineCall, afterCallStates, finalStates, firstAutomata};
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

bool automataPE_run(AutomataPE *a, FILE *input, Token *t){
  //Pega o token, transforma em um index da tabela de transicao e tenta achar o prox estado

  if(a->currentMachine.id == MTYPE_INVALID){
    return FALSE;
  }

  // printf("\t---------- %s\n", machineid_to_name(a->currentMachine.id));

  int next_state = table_get(&(a->currentMachine.table), a->currentMachine.state, convert_token_to_machine_type(t));
  
  //verifica se tem uma transicao normal pra algum estado
  if(next_state != MINVALID_STATE){
    actions_on_state_transition[a->currentMachine.id][a->currentMachine.state][convert_token_to_machine_type(t)](t);
    automata_goto_next_state2(&(a->currentMachine), convert_token_to_machine_type(t));
    Token t2 = find_possible_token(input);
    t->string = t2.string;
    t->type = t2.type;
    if(strcmp(t->string, "end") == 0){
      actions_on_state_transition[MTYPE_PROGRAM][2][MTTYPE_END](t);
    }

  //verifica se tem alguma transicao para uma maquina
  }else if(next_state == MINVALID_STATE){
    Table submachinecall_table = a->subMachineCall[a->currentMachine.id];
    int next_automata_id = table_get(&submachinecall_table, 
                                     a->currentMachine.state, 
                                    0);

    //n tem maquina pra chamar
    if(next_automata_id == MTYPE_INVALID){
      //verifica se eh estado final
      if(automataPE_is_final_state(next_state, a)){

        automata_goto_next_state2(&(a->currentMachine), convert_token_to_machine_type(t));

        if(list_size(&(a->stack)) > 0){
          //desempilha a ultima maquina, vai para o prox estado 
          Automata2 *pop_automata = list_get_first(&(a->stack));
          int temp_state = table_get(&(a->afterCallStates[pop_automata->id]), 
                                automata_current_state2(pop_automata),
                                a->currentMachine.id);
          // acao semantica quando desempilho a maquina
          actions_on_machine_return[a->currentMachine.id][a->currentMachine.state](t);
          a->currentMachine = *pop_automata;
          a->currentMachine.state = temp_state;
        }else{
          //se n tem maquina pra desempilhar, foi aceito!
          return TRUE;
        }
      }else{
        return FALSE;
      }
      //tem maquina pra chamar
    }else{
      Table next_automata_transition_table = a->transitionTables[next_automata_id];
      Automata2 next_automata = automata_create2(
                                  next_automata_id,
                                  0,
                                  &next_automata_transition_table);

      list_prepend(&(a->stack), &(a->currentMachine));
      a->currentMachine = next_automata;
      a->currentMachine.id = next_automata_id;
    }
  }else{
    // automata_goto_next_state2(&(a->currentMachine), table_convert_to_index(&(a->currentMachine.table), t));
    return FALSE;
  }
  return FALSE;
}

bool automataPE_is_final_state(int state, AutomataPE *a){
  return is_value_in_array(state, a->finalStates->table[a->currentMachine.id], a->finalStates->columns);
}

int automataPE_next_state(AutomataPE *a, Token *t){
  return automata_next_state2(&(a->currentMachine), convert_token_to_machine_type(t));
}

int automataPE_current_state(AutomataPE *a){
  return automata_current_state2(&(a->currentMachine));
}

AutomataId automataPE_current_machineId(AutomataPE *a){
  return a->currentMachine.id;
}
