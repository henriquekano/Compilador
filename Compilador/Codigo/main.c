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

#define FILENAME "ENTRADA.txt"
#define ASM_FILENAME "SAIDA.asm"

int main(){
	FILE *input = fopen(FILENAME, "r");
  FILE *output = fopen(ASM_FILENAME, "w");

  
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

  // SymbolTable s = symbol_table_create();

  // char *string = "dsfjalsdkfjaçlsdf";
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

  return 0;
}
