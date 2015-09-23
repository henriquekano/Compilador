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
	int c, current_state, next_state;
  
  do {
    //faz um lookahead - se nao for retornar para o S0 (=criar um token), 
    //le um caracter, else: não le um caracter e cria o token
    next_state = automata_next_state(automata, input_converter_function((char)c));
    if(next_state != S0){
      c = fgetc(file);
    }else{
      automata->state = S0;
      break;
    }
  	printf("%c", (char)c);
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