#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "automata.h"
#include "transition_table.h"
#include "./lexico/analisador.h"


#define FILENAME "input_file.txt"

int main(){
	FILE *file = fopen(FILENAME, "r");
	int count = 0;

	if (file == NULL)
		printf("Arquivo não existe!!!");
	else {
		Automata automata = automata_create(S0);
		while(count < 10) {
			find_possible_token(&automata, file);
			count++;
		}

	}
  return 0;
}
