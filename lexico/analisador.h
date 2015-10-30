#ifndef ANALISADOR_LEXICO_H_
  #define ANALISADOR_LEXICO_H_

  #include <stdio.h>
  #include "../utils/token.h"
  #include "automata.h"
  #include "../utils/bool.h"

  // Lista tokenize(char *file);
  // token get_token(char *file);

  typedef struct Lexic{
    Automata a;
  } Lexic;

	void tokenize(Automata *automata, FILE *file);
	Token find_possible_token(Automata *automata, FILE *file);
	bool can_create_token(int previous_state);
	void lexical_analysis(FILE *file);
#endif