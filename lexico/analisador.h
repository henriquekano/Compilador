#ifndef ANALISADOR_LEXICO_H_
  #define ANALISADOR_LEXICO_H_

  #include "../utils/token.h"
  #include "../utils/listaLigada.h"
  #include "../automata.h"
  #include <stdio.h>

  // Lista tokenize(char *file);
  // token get_token(char *file);

	int tokenizer(int state);
	Token find_possible_token(Automata *automata, FILE *file);
#endif