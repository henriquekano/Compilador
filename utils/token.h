#ifndef TOKEN_H_
  #define TOKEN_H_

  typedef enum{
    TT_STRING,
    TT_ARITH_SYMBOL,
    TT_NUMBER,
    TT_COMPARATOR,
    TT_IDENT_RESERVED,
    TT_SEPARATOR,
    TT_END_OF_COMMAND,
    TT_UNKNOWN
  }Token_type;

  typedef struct{
    char *string;
    Token_type type;
  }Token;

  Token token_create(char *string, Token_type type);
  void token_pretty_print(Token *t);
  char *token_type_to_string(Token_type token_type);
#endif
