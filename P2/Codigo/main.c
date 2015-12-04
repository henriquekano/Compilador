#include <stdio.h>
#include <stdlib.h>
#include "lexico/analisador.h"
#include "utils/token.h"

#define FILENAME "ENTRADA.txt"

int main(){
	FILE *input = fopen(FILENAME, "r");
  Token t;
  while(!reached_eof(input)){
    t = find_possible_token(input);
    token_pretty_print(&t);
    token_destroy(&t);
  }

  fclose(input);

  return 0;
}
