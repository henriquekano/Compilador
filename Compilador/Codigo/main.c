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
#include "./utils/string_utils.h"

#include "utils/automata2.h"
#include <limits.h>

#include "utils/symbol_table.h"

#include "semantico/semantico_actions.h"

#define FILENAME "ENTRADA.txt"

int main(){
	FILE *input = fopen(FILENAME, "r");
  
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
    automataPE_run(&aPE, input, &t);
  }

  fclose(input);

  return 0;
}
