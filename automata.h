#ifndef AUTOMATA_H_INCLUDED
  #define AUTOMATA_H_INCLUDED

  #define STATE_NUMBER 20; 
  #define BUFFER_MAX 50; 
  #include "./utils/token.h"

  /*
  Automato:
    state: o estado atual;
    state_transition_table: matriz de transicao de estado (linha = estado, coluna = input)
    input_converter_function: funcao que converte um char para um int
  */
  typedef struct{
    int state;
    char buffer[];
  }Automata;

  Automata automata_create(int state);
  void automata_goto_next_state(Automata *a, int input);
  int automata_next_state(Automata *a, int input);
  int automata_current_state(Automata *a);
#endif //AUTOMATA_H_INCLUDED