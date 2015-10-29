#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./lexico/analisador.h"
// #include "./utils/list.h"

#include "utils/automata2.h"
#include <limits.h>

#define FILENAME "ENTRADA.txt"

int main(){
	FILE *file = fopen(FILENAME, "r");

	if (file == NULL){
		printf("Arquivo não existe!!!");
  } else {
    lexical_analysis(file);
	}
  // int i, j;
  // int table[4][4] = 
  // {
  //   {0, 1, 2, FINAL_STATE},
  //   {0, 1, 2, ERROR_STATE},
  //   {0, 1, 2, 3},
  //   {0, 1, 2, 3} 
  // };

  // Automata2 a = automata_create2(0, 4, 4, table);

  // automata_print_table(&a);

  // automata_destroy2(&a);

  // if(0 == NULL)
  //   printf("Damn");

  return 0;
}