#ifndef AUTOMATA_H_
  #define AUTOMATA_H_

  #define STATE_NUMBER 20; 
  #include "token.h"

  typedef struct{
    int state;
    int **state_transition_table;
  }automata;

  token automata_get_token(FILE *file, automata *a);
#endif