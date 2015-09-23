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
    int (*input_converter_function)(char input);
  }automata;

  // token automata_get_token(FILE *file, automata *a);
  automata automata_create(int **state_transition_table, int (*function_converter)(char));
  int automata_next_state(automata *a, int input);
  int automata_current_state(automata *a);
  void automata_run_machine(automata *a, char *input);
#endif