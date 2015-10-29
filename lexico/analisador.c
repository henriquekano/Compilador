#include <ctype.h>
#include <string.h>
#include "analisador.h"
#include "transition_table.h"
#include "../utils/list.h"

// Lista tokenize(char *file){

//   FILE *oFile = fopen(file, "r");

//   fclose(oFile);
//   return 0;
// }

Token find_possible_token(Automata *automata, FILE *file){
  // constroi(&l);
  Token return_token;
  States current_state, previous_state;
  char c;
  List buffer;
  list_new(&buffer, sizeof(char), NULL);

  //pule os espacos!
  do{
    c = fgetc(file);

    if(feof(file)){
      return;
    }
  }while(isspace(c));
  
  fseek(file, -1, SEEK_CUR);

  // list_append(buffer, "\0");
  do {
    //faz um lookahead - se nao for retornar para o S0 (=criar um token), 
    //le um caracter, else: não le um caracter e cria o token

    c = (char)fgetc(file);

    if(c == (char)EOF){
      break;
    }
    
    previous_state = automata_current_state(automata);
    automata_goto_next_state(automata, input_converter_function(c));
    current_state = automata_current_state(automata);

    if(current_state != S0){
      list_append(&buffer, &c);
    }


  }while(current_state != S0);

  fseek(file, -1, SEEK_CUR);

  if (can_create_token(previous_state)){
    char *token_value = list_to_char_array(&buffer);
    return_token = token_create(token_value, state_converter_token_type(previous_state, token_value));
    token_pretty_print(&return_token);
  }
  
  list_destroy(&buffer);

  return return_token;
}

void tokenize(Automata *automata, FILE *file){
  int c, ft;
  // Token t;

  //Leia todo o arquivo!
  do{
    
    find_possible_token(automata, file);

    ft = ftell(file);
    c = fgetc(file);
    c = fgetc(file);
    if(c != EOF){
      fseek(file, ft, SEEK_SET);
      continue;
    }else{
      fseek(file, ft, SEEK_SET);
      break;
    }
    
  }while(TRUE);
}

bool can_create_token(int previous_state){
  if (state_converter_token_type(previous_state, "") == TT_IGNORE){
    return FALSE;
  } else {
    return TRUE;
  }
}

void lexical_analysis(FILE *file){
  Automata automata = automata_create(S0);
  tokenize(&automata, file);
}