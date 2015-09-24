#include <stdio.h>
#include "token.h"

Token token_create(char *string, Token_type type){
  Token t = {string,type};
  return t;
}

void token_pretty_print(Token *t){
  printf("%s \t\t\t | %s (%i)", t->string, token_type_to_string(t->type), t->type);
}

char *token_type_to_string(Token_type token_type){
  switch(token_type){
    case TT_STRING:
      return "STRING";
    case TT_ARITH_SYMBOL:
      return "ARITH_SYMBOL";
    case TT_NUMBER:
      return "NUMBER";
    case TT_COMPARATOR:
      return "COMPARATOR";
    case TT_IDENT_RESERVED:
      return "IDENT_RESERVED";
    case TT_SEPARATOR:
      return "SEPARATOR";
    case TT_END_OF_COMMAND:
      return "END_OF_COMMAND";
    case TT_UNKNOWN:
      return "UNKNOWN";
    default:
      return "UNKNOWN";
  }
}