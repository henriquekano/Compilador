#include "token.h"

token token_create(char *string, token_type type){
  token t = {string,type};
  return t;
}

void token_pretty_print(token *t){
  printf("%s | %i", t->string, t->type);
}
