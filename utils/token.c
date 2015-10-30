#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

Token token_create(char *string, Token_type type, tokenFreeFunction freeFn){
  Token t = {string,type,freeFn};
  return t;
}

void token_destroy(Token *t){
  if(t->freeFn)
    t->freeFn(t->string);
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
    case TT_STRING:
      return "STRING";
    case TT_ARITH_SYMBOL:
      return "ARITH_SYMBOL";
    case TT_INT:
      return "INT";
    case TT_COMPARATOR:
      return "COMPARATOR";
    case TT_RESERVED:
      return "RESERVED";
    case TT_IDENTIFIER:
      return "IDENTIFIER";
    case TT_SEPARATOR:
      return "SEPARATOR";
    case TT_END_OF_COMMAND:
      return "END_OF_COMMAND";
    case TT_ASSIGNMENT:
      return "ASSIGNMENT";
    case TT_UNKNOWN:
      return "UNKNOWN";
    case TT_FLOAT:
      return "FLOAT";
    default:
      return "";
  }
}