#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "automata2.h"

Automata2 automata_create2(int state, int row, int column, int table[row][column]){
  int i = 0;
  int j = 0;

  int **transitionTable = (int **)malloc(sizeof(int*));
  for(i = 0; i < row; i++){
    transitionTable[i] = (int *)malloc(column * sizeof(int));

    for(j = 0; j < column; j++){
      transitionTable[i][j] = table[i][j];
    }
  }

  Automata2 a = {state, transitionTable, row, column};
  return a;
};

void automata_destroy2(Automata2 *a){
  int i = 0, j = 0;

  for(i = 0; i < a->tableRows; i++){
    free(a->table[i]);
  }

};

int automata_next_state2(Automata2 *a, int input){
  return a->table[a->state][input];
}

void automata_goto_next_state2(Automata2 *a, int input){
  a->state = automata_next_state2(a, input);
}

int automata_current_state2(Automata2 *a){
  return a->state;
}

void automata_print_table(Automata2 *a){
  int i, j;
  for(i = 0; i < a->tableRows; i++){
    for(j = 0; j < a->tableColumns; j++){
      printf("%d ", a->table[i][j]);
    }
    printf("\n");
  }
}