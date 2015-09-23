#ifndef AUTOMATA_H_
  #define AUTOMATA_H_

  #define STATE_NUMBER 20; 
  #include "token.h"

  /*
  Automato:
    state: o estado atual;
    state_transition_table: matriz de transicao de estado (linha = estado, coluna = input)
    input_converter_function: funcao que converte um char para um int
  */
  typedef struct{
    int state;
    int **state_transition_table;
  }automata;

  // token automata_get_token(FILE *file, automata *a);
  automata automata_create(int **state_transition_table);
  void automata_goto_next_state(automata *a, int input);
  int automata_next_state(automata *a, int input);
  int automata_current_state(automata *a);
#endif