#ifndef ANALISADOR_LEXICO_H_
  #define ANALISADOR_LEXICO_H_

  #include <stdio.h>
  #include "../utils/token.h"
  #include "../utils/bool.h"

	void tokenize(FILE *file);
	Token find_possible_token(FILE *file);
	bool can_create_token(int previous_state);
	void lexical_analysis(FILE *file);

  bool reached_eof(FILE *file);
#endif