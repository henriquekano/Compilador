#ifndef SEMANTIC_ACTIONS_H_INCLUDED
#define SEMANTIC_ACTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../utils/token.h"

void init_semantic();
void end_semantic();
char *get_label();
char *get_number_hex_string(int number);
void expression_print(FILE *file, Token token);

#endif