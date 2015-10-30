#ifndef AUTOMATA_UTIL_H2
  #define AUTOMATA_UTIL_H2

  #include <limits.h>
  
  #define FINAL_STATE INT_MAX
  #define ERROR_STATE INT_MIN

  #include "table.h"
  /*
  Automato:
    state: o estado atual;
    state_transition_table: matriz de transicao de estado (linha = estado, coluna = input)
    input_converter_function: funcao que converte um char para um int
  */
  typedef struct Automata2{
    int state;
    Table table;
    
  }Automata2;

  Automata2 automata_create2(int state, Table *table);
  
  void automata_destroy2(Automata2 *a);
  void automata_goto_next_state2(Automata2 *a, int input);
  int automata_next_state2(Automata2 *a, int input);
  int automata_current_state2(Automata2 *a);

  void automata_print_table(Automata2 *a);
#endif //AUTOMATA_UTIL_H2