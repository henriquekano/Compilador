#ifndef TOKEN_H_
  #define TOKEN_H_

  #include <string.h>
  #include <stdio.h>
  #include <stdlib.h>

  typedef enum{
    TT_STRING,
    TT_ARITH_SYMBOL,
    TT_NUMBER,
    TT_COMPARATOR,
    TT_IDENT_RESERVED,
    TT_SEPARATOR,
    TT_END_OF_COMMAND,
    TT_UNKNOWN
  }token_type;

  typedef struct{
    char *string;
    token_type type;
  }token;

  token token_create(char *string, token_type type);
  void token_pretty_print(token *t);
#endif
