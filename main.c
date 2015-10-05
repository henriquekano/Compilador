#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./lexico/analisador.h"
#include "./utils/list.h"

#define FILENAME "ENTRADA.txt"

bool print_int(void *i);

int main(){
	FILE *file = fopen(FILENAME, "r");

	if (file == NULL){
		printf("Arquivo não existe!!!");
  } else {
    lexical_analysis(file);
	}
  return 0;
}

bool print_int(void *i){
  printf("%d", *(int*)i);
  return TRUE;
}