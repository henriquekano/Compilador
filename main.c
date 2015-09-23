#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// #include "./utils/automata.h"

#define FILENAME "input_file.txt"

int main(){
	int c;
	FILE *file = fopen(FILENAME, "r");

	if (file == NULL)
		printf("Arquivo não existe!!!");

	while ((c = fgetc(file)) != EOF) {
		printf("%c", c);
	}

  // token t = token_create("asdasd", 0);
  // token_pretty_print(&t);
  return 0;
}
