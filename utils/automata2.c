#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "automata2.h"
#include "table.h"

Automata2 automata_create2(int id, int state, Table *table){
  // Table transitionTable = table_create(row, column, table);

  Automata2 a = {id, state, table};
  return a;
}

void automata_destroy2(Automata2 *a){
  table_destroy(&(a->table));
}

int automata_next_state2(Automata2 *a, int input){
  return table_get(&(a->table), a->state, input);
}

void automata_goto_next_state2(Automata2 *a, int input){
  a->state = automata_next_state2(a, input);
}

int automata_current_state2(Automata2 *a){
  return a->state;
}

void automata_print_table(Automata2 *a){
  table_print_table(&(a->table));
}