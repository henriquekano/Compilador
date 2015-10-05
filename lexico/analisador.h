#ifndef ANALISADOR_LEXICO_H_
  #define ANALISADOR_LEXICO_H_

  #include <stdio.h>
  #include "../utils/token.h"
  #include "automata.h"

  // Lista tokenize(char *file);
  // token get_token(char *file);

	void tokenize(Automata *automata, FILE *file);
	void find_possible_token(Automata *automata, FILE *file);
	int can_create_token(int previous_state);
	void lexical_analysis(FILE *file);
#endif