#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "analisador.h"
#include "../utils/list.h"
#include "../utils/bool.h"


const char *RESERVED_WORDS[] = {"S", "s", "K", "k", "I", "i", "'", "*", "1", "0", "(", ")"};

bool is_reserved(char *string){
  int i = 0;

  for(i = 0; RESERVED_WORDS[i]; i++) {
    if(strcmp(RESERVED_WORDS[i], string) == 0) {
      return TRUE;
    }
  }
  return FALSE;
}

Token_type get_token_type(char *string){
  if(strcmp(string, "S") == 0){
    return TT_S;
  }else if(strcmp(string, "s") == 0){
    return TT_s;
  }else if(strcmp(string, "K") == 0){
    return TT_K;    
  }else if(strcmp(string, "k") == 0){
    return TT_k;    
  }else if(strcmp(string, "I") == 0){
    return TT_I;    
  }else if(strcmp(string, "i") == 0){
    return TT_i;    
  }else if(strcmp(string, "1") == 0){
    return TT_1;    
  }else if(strcmp(string, "0") == 0){
    return TT_0;    
  }else if(strcmp(string, "'") == 0){
    return TT_S_QUOTE;    
  }else if(strcmp(string, "*") == 0){
    return TT_ASTERISK;    
  }else if(strcmp(string, "(") == 0){
    return TT_L_PARENTHESIS;    
  }else if(strcmp(string, ")") == 0){
    return TT_R_PARENTHESIS;    
  }else{
    return TT_UNKNOWN;
  }
}

void destroy_token_string(char *string){
  free(string);
} 

Token find_possible_token(FILE *file){
  // constroi(&l);
  Token return_token;
  char c;
  char *buffer = (char *)malloc(2 * sizeof(char));

  //pule os espacos!
  do{
    c = fgetc(file);

    if(feof(file)){
      return token_create("\0", TT_UNKNOWN);
    }
  }while(isspace((int)c));
  
  fseek(file, -1, SEEK_CUR);
  buffer[0] = fgetc(file);
  buffer[1] = '\0';
  if(is_reserved(buffer)){
    return_token = token_create(buffer, get_token_type(buffer));
  }else{
    return token_create("\0", TT_UNKNOWN);
  }
  return return_token;
}

bool reached_eof(FILE *file){
  int c, ft;
  ft = ftell(file);
  c = fgetc(file);
  c = fgetc(file);
  if(c != EOF){
    fseek(file, ft, SEEK_SET);
    return FALSE;
  }else{
    fseek(file, ft, SEEK_SET);
    return TRUE;
  }
}