#include "token.h"

Token token_create(char *string, Token_type type){
  Token t = {string,type};
  return t;
}

void token_pretty_print(Token *t){
  printf("%s | %i", t->string, t->type);
}
