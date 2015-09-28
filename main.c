#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "automata.h"
#include "transition_table.h"
#include "./lexico/analisador.h"


#define FILENAME "ENTRADA.txt"

int main(){
	FILE *file = fopen(FILENAME, "r");

	if (file == NULL){
		printf("Arquivo não existe!!!");
  } else {
	Automata automata = automata_create(S0);
    tokenize(&automata, file);
	}
  return 0;
}
