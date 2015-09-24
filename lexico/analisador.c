#include "analisador.h"
#include "../transition_table.h"
#include "../utils/listaLigada.h"
#include "../automata.h"
#include <ctype.h>
#include <string.h>
#include "../utils/token.h"
#include "../transition_table.h"

// Lista tokenize(char *file){

//   FILE *oFile = fopen(file, "r");

//   fclose(oFile);
//   return 0;
// }

void find_possible_token(Automata *automata, FILE *file){
  // constroi(&l);
  Token return_token;
  States current_state, previous_state;
  int c;
  char buffer[50] = "\0";
  char temp[2] = "\0";
  do {
    //faz um lookahead - se nao for retornar para o S0 (=criar um token), 
    //le um caracter, else: não le um caracter e cria o token
    // next_state = automata_next_state(automata, input_converter_function((char)c));
    // if(next_state != S0){
    //   c = fgetc(file);
    // }else{
    //   automata->state = S0;
    //   break;
    // }
    c = fgetc(file);
    previous_state = automata_current_state(automata);
    automata_goto_next_state(automata, input_converter_function((char)c));
    current_state = automata_current_state(automata);

    if(current_state != S0){
      temp[0] = (char)c;
      strcat(buffer, temp);
    }

    // insereFim(c, &l);

  }while(current_state != S0 && c != EOF);

  fseek(file, -1, SEEK_CUR);
  return_token = token_create(buffer, state_converter_token_type(previous_state));
  token_pretty_print(&return_token);
  // return_token = token_create(toArray(&l), 0);
  // destroi(&l);
  printf("\n");

  // while ((c = fgetc(file)) != EOF) {
  // }    
}

void tokenize(Automata *automata, FILE *file){
  int c;
  // Token t;

  //Leia todo o arquivo!
  do{
    //pule os espacos!
    do{
      c = fgetc(file);
      if(feof(file)){
        return;
      }
    }while(isspace(c));
    fseek(file, -1, SEEK_CUR);

    find_possible_token(automata, file);
    // token_pretty_print(&t);
    fgetc(file);
    c = fgetc(file);
  }while(!feof(file) && !fseek(file, -2, SEEK_CUR));
}

