#include <stdio.h>
#include <ctype.h>
#include "transition_table.h"

int char_to_table_input(char character){
  if(isalpha(character)){
    return LETTER;
  }else if(isdigit(character)){
    return NUMBER;
  }else if(character == '+' || character == '-' || character == '/' || character == '*'){
    return ARITH_SYMBOL;
  }else if(character == '\"'){
    return DOUBLE_QUOTE;
  }else if(character == '\''){
    return SINGLE_QUOTE;
  }else if(character == ';'){
    return END_OF_COMMAND;
  }else if(character == '='){
    return EQUALS;
  }else if(character == '<' || character == '>' || character == '!' || character == '='){
    return COMPARATOR;
  }else if(character == '_'){
    return UNDERLINE;
  }else if(isspace(character)){
    return UNDERLINE;
  }else{
    return UNKNOWN;
  }
}