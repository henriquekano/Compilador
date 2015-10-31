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

#define FILENAME "ENTRADA.txt"

void semantic_tbd(AutomataPE *aPE, Token *t, FILE *file){
  printf("TODO\n");
  automataPE_run(aPE, file, t);
      
}

int main(){
	FILE *file = fopen(FILENAME, "r");
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


  AutomataPE aPE;
  Token t = find_possible_token(file);
  aPE = init_machines();
   
  while(!reached_eof(file)){

      semantic_tbd(&aPE, &t, file);   
  }

  fclose(file);
  return 0;
}
