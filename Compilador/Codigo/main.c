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

#define FILENAME "ENTRADA.txt"

void semantic_tbd(AutomataPE *aPE, Token *t, FILE *file){
  printf("TODO\n");
  automataPE_run(aPE, file, t);
      
}

int main(){
	// FILE *file = fopen(FILENAME, "r");
  // Token t;
  // Automata automata = automata_create(S0);

 //  printf("Changed!\n");

	// if (file == NULL){
	// 	printf("Arquivo não existe!!!");
 //  } else {
 //    do{
 //      t = find_possible_token(file);
 //      token_destroy(&t);
 //    }while(!reached_eof(file));
	// }

// /*sintatic test*/ 
//   AutomataPE aPE;
//   Token t = find_possible_token(file);
//   aPE = init_machines();
   
//   while(!reached_eof(file)){

//       semantic_tbd(&aPE, &t, file);   
//   }

//   fclose(file);

  SymbolTable s = symbol_table_create();
  char *string = "lalalalala";
  int array[SYMBOL_TABLE_SYMBOL_INFO] = {0, 0, 0, 0, 0};
  int i, *otherArray;

  symbol_table_add(&s, string, array);
  symbol_table_pretty_print(&s);

  otherArray = symbol_table_get_info(&s, string);
  for(i = 0; i < SYMBOL_TABLE_SYMBOL_INFO; i ++){
    printf("%d ", otherArray[i]);
  }
  printf("\n");

  symbol_table_destroy(&s);

  return 0;
}
