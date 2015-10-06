#include <ctype.h>
#include <string.h>
#include "analisador.h"
#include "transition_table.h"

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

    c = fgetc(file);

    if(c == EOF){
      break;
    }
    
    previous_state = automata_current_state(automata);
    automata_goto_next_state(automata, input_converter_function((char)c));
    current_state = automata_current_state(automata);

    if(current_state != S0){
      temp[0] = (char)c;
      strcat(buffer, temp);
    }


  }while(current_state != S0);

  fseek(file, -1, SEEK_CUR);

  if (can_create_token(previous_state)){
    return_token = token_create(buffer, state_converter_token_type(previous_state, buffer));
    token_pretty_print(&return_token);
  }
  
}

void tokenize(Automata *automata, FILE *file){
  int c, ft;
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
