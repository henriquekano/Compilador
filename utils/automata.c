#include <stdio.h>
#include <ctype.h>
#include "automata.h"
#include "token.h" 

automata automata_create(int **state_transition_table, int (*function_converter)(char)){
  automata a = {0, state_transition_table, function_converter};
  return a;
};

int automata_next_state(automata *a, int input){
  return a->state_transition_table[a->state][input];
}

void automata_goto_next_state(automata *a, int input){
  a->state = automata_next_state(a, input);
}

int automata_current_state(automata *a){
  return a->state;
}

void automata_run_machine(automata *a, char *input){
  char *ch = input;
  //Ignora espacos e </br>s
  while(*ch != '\0'){
    automata_goto_next_state(a, a->input_converter_function(*ch));
    ch++;
  }
 
}
