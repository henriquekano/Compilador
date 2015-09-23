#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./utils/automata.h"

int main(){
  token t = token_create("asdasd", 0);
  token_pretty_print(&t);
  return 0;
}
