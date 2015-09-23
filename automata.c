#include <stdio.h>
#include <ctype.h>
#include "automata.h"
#include "./utils/token.h" 
#include "transition_table.h"

automata automata_create(int state){
  automata a = {state};
  return a;
};

int automata_next_state(automata *a, int input){
  return state_transition_table[a->state][input];
}

void automata_goto_next_state(automata *a, int input){
  a->state = automata_next_state(a, input);
}

int automata_current_state(automata *a){
  return a->state;
}
