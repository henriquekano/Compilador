#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "automata.h"
#include "transition_table.h"

#define FILENAME "input_file.txt"

int main(){
	char c;
	FILE *file = fopen(FILENAME, "r");
	int current_state;

	if (file == NULL)
		printf("Arquivo não existe!!!");
	else {
		Automata automata = automata_create(S0);
		while ((c = fgetc(file)) != EOF) {
			current_state = automata_current_state(&automata);
			automata_goto_next_state(&automata, input_converter_function((char)c));
			next_state = automata_current_state(&automata);
			

		}		
	}
  return 0;
}
