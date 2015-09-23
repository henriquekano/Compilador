#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./utils/automata.h"
#include "./transition_table.h"

#define FILENAME "input_file.txt"

int main(){
	int c;
	FILE *file = fopen(FILENAME, "r");

	if (file == NULL)
		printf("Arquivo não existe!!!");
	else {
		automata autom = automata_create(state_transition_table);
		while ((c = fgetc(file)) != EOF) {
			printf("%c", c);
			automata_goto_next_state(&autom, state_transition_table);
		}		
	}
  return 0;
}
