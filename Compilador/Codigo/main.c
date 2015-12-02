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

  init_semantic();

  char  one[2] = {'1', '\0'}, 
        plus[2] = {'+', '\0'}, 
        end[2] = {';', '\0'}, 
        mult[2] = {'*', '\0'},
        rpar[2] = {')', '\0'},
        lpar[2] = {'(', '\0'};
  
  // (1 + (1 + 1 + 1) * (1 * (1 + 1 + 1)) * (1 + 1))

  Token oneT, plusT, endT, multT, rparT, lparT;
  oneT = token_create(one, TT_INT, NULL);
  plusT = token_create(plus, TT_ARITH_SYMBOL, NULL);
  multT = token_create(mult, TT_ARITH_SYMBOL, NULL);
  endT = token_create(end, TT_END_OF_COMMAND, NULL);
  rparT = token_create(rpar, TT_R_PARENTHESIS, NULL);
  lparT = token_create(lpar, TT_L_PARENTHESIS, NULL);
  
  // // printf("%s", get_number_hex_string(16));

  expression_print(NULL, lparT);
  expression_print(NULL, oneT);
  expression_print(NULL, plusT);
  
  expression_print(NULL, lparT);
    expression_print(NULL, oneT);
    expression_print(NULL, plusT);
    expression_print(NULL, oneT);
    expression_print(NULL, plusT);
    expression_print(NULL, oneT);
  expression_print(NULL, rparT);

  expression_print(NULL, multT);

    expression_print(NULL, lparT);
    expression_print(NULL, oneT);
    expression_print(NULL, multT);

      expression_print(NULL, lparT);
        expression_print(NULL, oneT);
        expression_print(NULL, plusT);
        expression_print(NULL, oneT);
        expression_print(NULL, plusT);
        expression_print(NULL, oneT);
      expression_print(NULL, rparT);

    expression_print(NULL, rparT);

    expression_print(NULL, multT);
    expression_print(NULL, lparT);
      expression_print(NULL, oneT);
      expression_print(NULL, plusT);
      expression_print(NULL, oneT);
    expression_print(NULL, rparT);

  expression_print(NULL, rparT);

  expression_print(NULL, endT);

  end_semantic();

  return 0;
}