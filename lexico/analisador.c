#include "analisador.h"
#include "../transition_table.h"
#include "../utils/listaLigada.h"
#include "../automata.h"
#include <ctype.h>

// Lista tokenize(char *file){

//   FILE *oFile = fopen(file, "r");

//   fclose(oFile);
//   return 0;
// }

Token find_possible_token(Automata *automata, FILE *file){
	Lista l;
	Token return_token;
	constroi(&l);
	int c, current_state, previous_state;
  
  do {
  	c = fgetc(file);
  	printf("%c", (char)c);
		previous_state = automata_current_state(automata);
		automata_goto_next_state(automata, input_converter_function((char)c));
		current_state = automata_current_state(automata);

		insereInicio(c, &l);

  }while(current_state != S0);

  return_token = token_create(toArray(&l), 0);
 	destroi(&l);
  printf("\n");

  // while ((c = fgetc(file)) != EOF) {

  return return_token;

  	

  // }		
}