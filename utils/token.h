#ifndef TOKEN_H_
  #define TOKEN_H_

  #include "bool.h"

  typedef enum{
    TT_STRING = 0,
    TT_ARITH_SYMBOL = 1,
    TT_INT = 2,
    TT_COMPARATOR = 3,
    TT_RESERVED = 4,
    TT_IDENTIFIER = 5,
    TT_SEPARATOR = 6,
    TT_END_OF_COMMAND = 7,
    TT_UNKNOWN = 8,
    TT_ASSIGNMENT = 9,
    TT_FLOAT = 10,
    TT_ARRAY = 11,
    TT_MATRIX = 12,
    TT_IGNORE = 13
  }Token_type;

  typedef struct{
    char *string;
    Token_type type;
  }Token;

  Token token_create(char *string, Token_type type);
  void token_pretty_print(Token *t);
  bool token_is_empty(Token *t);
  char *token_type_to_string(Token_type token_type);
#endif
