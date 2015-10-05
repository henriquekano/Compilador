#include <stdio.h>
#include <ctype.h>
#include "../utils/token.h" 
#include "transition_table.h"
#include "automata.h"

Automata automata_create(int state){
  Automata a = {state};
  return a;
};

int automata_next_state(Automata *a, int input){
  return STATE_TRANSITION_TABLE[a->state][input];
}

void automata_goto_next_state(Automata *a, int input){
  a->state = automata_next_state(a, input);
}

int automata_current_state(Automata *a){
  return a->state;
}
