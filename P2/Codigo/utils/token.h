#ifndef TOKEN_H_
  #define TOKEN_H_

  #include "bool.h"

  typedef enum{
    TT_S = 0,
    TT_s = 1,
    TT_K = 2,
    TT_k = 3,
    TT_I = 4,
    TT_i = 5,
    TT_L_PARENTHESIS = 6,
    TT_R_PARENTHESIS = 7,
    TT_0 = 8,
    TT_1 = 9,
    TT_S_QUOTE = 10,
    TT_ASTERISK = 11,
    TT_UNKNOWN = 12
  }Token_type;

  typedef struct{
    char *string;
    Token_type type;
  }Token;

  Token token_create(char *string, Token_type type);
  void token_destroy(Token *t);
  
  void token_pretty_print(Token *t);
  bool token_is_empty(Token *t);
  char *token_type_to_string(Token_type token_type);
#endif
