#ifndef SEMANTIC_ACTIONS_H_
#define SEMANTIC_ACTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include "machines.h"

void (*actions_on_state_transition[N_MACHINE_TYPES][MAX_STATES][N_MACHINE_TOKEN_TYPES])();
void (*actions_on_machine_return[N_MACHINE_TYPES][MAX_STATES])();

void semantic_actions_init();
void semantic_actions_end();
void expression_print(FILE *file, Token token);

#endif /* SEMANTIC_ACTIONS_H_ */
