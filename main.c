#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./lexico/analisador.h"
#include "./utils/list.h"


#define FILENAME "ENTRADA.txt"

bool print_int(void *i);

int main(){
	// FILE *file = fopen(FILENAME, "r");

	// if (file == NULL){
	// 	printf("Arquivo não existe!!!");
 //  } else {
	// Automata automata = automata_create(S0);
 //    tokenize(&automata, file);
	// }
  int i;
  List list;
  list_new(&list, sizeof(int), NULL);

  for(i = 0; i < 10; i++){
    list_append(&list, &i);
  }

  print_int(list_get_n(&list, 2));

  list_destroy(&list);

  return 0;
}


bool print_int(void *i){
  printf("%d", *(int*)i);
  return TRUE;
}