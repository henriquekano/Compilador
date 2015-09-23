#include <stdio.h>
#include <ctype.h>
#include "automata.h"
#include "token.h" 

automata automata_create(int **state_transition_table){
  automata a = {0, state_transition_table};
  return a;
}

token automata_get_token(FILE *file, automata *a){
  int ch;
  //Ignora espacos e </br>s
  do{
    ch = (char)fgetc(file);
  }while(isspace(ch));

  do{
    automata_next_state(a, ch);
    ch = (char)fgetc(file);
  }while(isspace(ch));

  return token_create("asdasdas", 0);
}

// void automata_next_state(automata *a, char input_type){
// }

// int automata_current_state(automata *a){
//   return a->state;
// }