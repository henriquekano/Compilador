#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./lexico/analisador.h"
#include "./utils/token.h"
#include "./lexico/transition_table.h"
#include "./sintatico/automataPE.h"
#include "./sintatico/machines.h"

#include "./utils/list.h"

#include "utils/automata2.h"
#include <limits.h>

#include "utils/symbol_table.h"

#include "semantico/semantico_actions.h"

#define FILENAME "ENTRADA.txt"

void semantic_tbd(AutomataPE *aPE, Token *t, FILE *file){
  printf("TODO\n");
  automataPE_run(aPE, file, t);
      
}

int main(){


  // SymbolTable s = symbol_table_create();
  // char *string = "lalalalala";
  // int array[SYMBOL_TABLE_SYMBOL_INFO] = {0, 0, 0, 0, 0};
  // int i, *otherArray;

  // symbol_table_add(&s, string, array);
  // symbol_table_pretty_print(&s);

  // otherArray = symbol_table_get_info(&s, string);
  // for(i = 0; i < SYMBOL_TABLE_SYMBOL_INFO; i ++){
  //   printf("%d ", otherArray[i]);
  // }
  // printf("\n");

  // symbol_table_destroy(&s);

  printf("%s", get_number_hex_string(16));

  return 0;
}
