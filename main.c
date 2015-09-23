#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "automata.c"
#include "transition_table.c"

#define FILENAME "input_file.txt"

int main(){
	char c;
	FILE *file = fopen(FILENAME, "r");

	if (file == NULL)
		printf("Arquivo não existe!!!");
	else {
		automata autom = automata_create(S0);
		while ((c = fgetc(file)) != EOF) {
			printf("%c", c);
			automata_goto_next_state(&autom, input_converter_function(c));
		}		
	}
  return 0;
}
