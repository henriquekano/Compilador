#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./lexico/analisador.h"
#include "./utils/token.h"
#include "./lexico/transition_table.h"
#include "./sintatico/automataPE.h"
#include "./sintatico/machines.h"
#include "./sintatico/semantic_actions.h"

#include "./utils/list.h"

#include "utils/automata2.h"
#include <limits.h>

#include "utils/symbol_table.h"

#include "semantico/semantico_actions.h"

#define FILENAME "ENTRADA.txt"
#define OUTPUT_FILENAME "SAIDA.txt"


void semantic_tbd(AutomataPE *aPE, Token *t, FILE *file){
  printf("TODO\n");
  automataPE_run(aPE, file, t);
      
}

#define ASM_FILENAME "SAIDA.asm"


int main(){
	FILE *input = fopen(FILENAME, "r");
  FILE *output = fopen(ASM_FILENAME, "w");


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

  FILE *file = fopen(OUTPUT_FILENAME, "w+");

  init_semantic();

  char  one[2] = {'1', '\0'}, 
        plus[2] = {'+', '\0'}, 
        end[2] = {';', '\0'}, 
        mult[2] = {'*', '\0'},
        rpar[2] = {')', '\0'},
        lpar[2] = {'(', '\0'};
  

  Token oneT, plusT, endT, multT, rparT, lparT;
  oneT = token_create(one, TT_INT, NULL);
  plusT = token_create(plus, TT_ARITH_SYMBOL, NULL);
  multT = token_create(mult, TT_ARITH_SYMBOL, NULL);
  endT = token_create(end, TT_END_OF_COMMAND, NULL);
  rparT = token_create(rpar, TT_R_PARENTHESIS, NULL);
  lparT = token_create(lpar, TT_L_PARENTHESIS, NULL);
  
  // // printf("%s", get_number_hex_string(16));

  // (1 + (1 + 1 + 1) * (1 * (1 + 1 + 1)) * (1 + 1))
  expression_print(file, lparT);
  expression_print(file, oneT);
  expression_print(file, plusT);
  
  expression_print(file, lparT);
    expression_print(file, oneT);
    expression_print(file, plusT);
    expression_print(file, oneT);
    expression_print(file, plusT);
    expression_print(file, oneT);
  expression_print(file, rparT);

  expression_print(file, multT);

    expression_print(file, lparT);
    expression_print(file, oneT);
    expression_print(file, multT);

      expression_print(file, lparT);
        expression_print(file, oneT);
        expression_print(file, plusT);
        expression_print(file, oneT);
        expression_print(file, plusT);
        expression_print(file, oneT);
      expression_print(file, rparT);

    expression_print(file, rparT);

    expression_print(file, multT);
    expression_print(file, lparT);
      expression_print(file, oneT);
      expression_print(file, plusT);
      expression_print(file, oneT);
    expression_print(file, rparT);

  expression_print(file, rparT);

  expression_print(file, endT);



  end_semantic();
  
 //  Token t;
 //  Automata automata = automata_create(S0);

	// if (input == NULL){
	// 	printf("Arquivo não existe!!!");
 //  } else {
 //    do{
 //      t = find_possible_token(input);
 //      token_destroy(&t);
 //    }while(!reached_eof(input));
	// }

/*sintatic test*/ 
  AutomataPE aPE;
  Token t = find_possible_token(input);
  aPE = init_machines();
  init_semantic_actions();
   
  while(!reached_eof(input)){
    automataPE_run(&aPE, input, output, &t);
  }

  fclose(output);
  fclose(input);

  fclose(file);

  return 0;
}
