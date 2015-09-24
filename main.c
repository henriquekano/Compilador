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

	if (file == NULL){
		printf("Arquivo não existe!!!");
  } else {
  	printf("%d\n\n", EOL);
		Automata automata = automata_create(S0);
    tokenize(&automata, file);
	}
  return 0;
}
