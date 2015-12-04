#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

Token token_create(char *string, Token_type type){
  Token t = {string,type};
  return t;
}

void token_destroy(Token *t){
  free(t->string);
}

void token_pretty_print(Token *t){
  printf("%s \t\t\t | %s (%i)\n", t->string, token_type_to_string(t->type), t->type);
}

bool token_is_empty(Token *t){
  if(strcmp(t->string, "\0") == 0 || strcmp(t->string, "") == 0){
    return TRUE;
  }else{
    return FALSE;
  }
}

char *token_type_to_string(Token_type token_type){
  switch(token_type){
    case TT_S:
      return "TT_S";
    case TT_s:
      return "TT_s";
    case TT_K:
      return "TT_K";
    case TT_k:
      return "TT_k";
    case TT_I:
      return "TT_I";
    case TT_i:
      return "TT_i";
    case TT_L_PARENTHESIS:
      return "TT_L_PARENTHESIS";
    case TT_R_PARENTHESIS:
      return "TT_R_PARENTHESIS";
    case TT_0:
      return "TT_0";
    case TT_1:
      return "TT_1";
    case TT_S_QUOTE:
      return "TT_S_QUOTE";
    case TT_ASTERISK:
      return "TT_ASTERISK";
    default:
      return "???";

    }
}