#include "semantico_actions.h"
#include "../utils/Token.h"
#include "../utils/list.h"
#include "../utils/bool.h"
#include "../utils/file_manager.h"
#include "../utils/string_utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int temp_count = 0;
static int while_count = 0;
static int if_count = 0;
static int elsif_count = 0;

static char buffer[100];

static struct List char_pointer_garbage;

static struct List operands_stack;
static struct List operator_stack;



void init_semantic(){
  list_new(&char_pointer_garbage, sizeof(char*), list_free_string);

  list_new(&operands_stack, sizeof(char *), list_free_string);
  list_new(&operator_sta  ck, sizeof(char *), list_free_string);
}

void end_semantic(){
  list_destroy(&operator_stack);
  list_destroy(&operands_stack);
  
  list_destroy(&char_pointer_garbage);
}

// LABELS - depois tem de dar um free!

char *get_temp_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "temp_%d", temp_count);
  temp_count ++;
  return temp;
}

char *get_while_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "while_%d", while_count);
  while_count ++;
  return temp;
}

char *get_while_do_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "while_%d_do", while_count);
  return temp;
}

char *get_while_end_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "while_%d_end", while_count);
  return temp;
}

char *get_if_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "if_%d", if_count);
  if_count ++;
  return temp;
}

char *get_if_do_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "if_%d_do", if_count);
  return temp;
}

char *get_elsif_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "if_%d_elsif_%d", if_count, elsif_count);
  elsif_count ++;
  return temp;
}

char *get_elsif_do_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "if_%d_elsif_%d_do", if_count, elsif_count);
  return temp;
}

char *get_else_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "if_%d_elsif", if_count);
  return temp;
}

char *get_end_if_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "if_end_%d", if_count);
  elsif_count = 0;
  return temp;
}


char *get_number_hex_string(int number){
  char *temp = (char *)malloc(4 * sizeof(char));
  sprintf(temp, "%04x", number);
  return temp;
}

// Printando codigo!

void program_start(FILE *file) {
  write(file, "main\t\tJP  /0000\t\t;\n");
}

void program_end(FILE *file) {
  sprintf(buffer, "\t\t\tHM  main\t\t;\n");
  write(file, buffer);
  sprintf(buffer, "\t\t\t#  main \t\t;\n\n");
  write(file, buffer);
}


//EXPRESSIONS

int operator_precedence(char * operator) {
  if(operator != NULL) {
    if(strcmp(operator, "+") == 0) return 0;
    if(strcmp(operator, "-") == 0) return 0;
    if(strcmp(operator, "*") == 0) return 1;
    if(strcmp(operator, "/") == 0) return 1;
    if(strcmp(operator, "(") == 0) return 2;
    if(strcmp(operator, ")") == 0) return 2;
  }
  return -1;
}

char *apply(char *operation, char *operand1, char *operand2){
  char *temp = (char *)malloc(6 * sizeof(char));
  bool op1_is_digit = isDigit(operand1);
  bool op2_is_digit = isDigit(operand2);


  if(op1_is_digit && op2_is_digit){
    list_append(&char_pointer_garbage, temp);
    if(strcmp(operation, "+") == 0){
      itoa(atoi(operand1) + atoi(operand2), temp, 10);
    }else if(strcmp(operation, "-") == 0){
      itoa(atoi(operand1) - atoi(operand2), temp, 10);
    }else if(strcmp(operation, "*") == 0){
      itoa(atoi(operand1) * atoi(operand2), temp, 10);
    }else if(strcmp(operation, "/") == 0){
      itoa(atoi(operand1) / atoi(operand2), temp, 10);
    }else{
      return NULL;
    }
  }
  printf("%s\n", temp);
  return temp;
}

// https://en.wikipedia.org/wiki/Shunting-yard_algorithm 
void expression_print(FILE *file, Token token){
  char *operand1;
  char *operand2;
  char *operator;
  char *result;

  if(token.type == TT_IDENTIFIER || token.type == TT_INT){
    list_prepend(&operands_stack, token.string);

  } else if(token.type == TT_ARITH_SYMBOL){
    char *last_operator = (char *)list_peek_head(&operator_stack);
    if(list_size(&operator_stack) <= 0 || strcmp(last_operator, "(") == 0 || operator_precedence(token.string) >= operator_precedence(last_operator)){
      list_prepend(&operator_stack, token.string);
    }else if(operator_precedence(token.string) < operator_precedence(last_operator)){
      while(list_size(&operator_stack) > 0){
        operator = list_get_first(&operator_stack);
        operand2 = (char *)list_get_first(&operands_stack);
        operand1 = (char *)list_get_first(&operands_stack);
        result = apply(operator, operand1, operand2);
        list_prepend(&operands_stack, result);
      }
      list_prepend(&operator_stack, token.string);
    }
  } else if(token.type == TT_L_PARENTHESIS){
    list_prepend(&operator_stack, token.string);
  } else if(token.type == TT_R_PARENTHESIS){
    while(list_size(&operator_stack) > 0 && strcmp((char *)list_peek_head(&operator_stack), "(") != 0){
      operator = list_get_first(&operator_stack);
      operand2 = (char *)list_get_first(&operands_stack);
      operand1 = (char *)list_get_first(&operands_stack);
      result = apply(operator, operand1, operand2);
      list_prepend(&operands_stack, result);
    }
    list_get_first(&operator_stack);
  } else if(token.type == TT_END_OF_COMMAND){
    while(list_size(&operator_stack) > 0){
      operator = list_get_first(&operator_stack);
      operand2 = (char *)list_get_first(&operands_stack);
      operand1 = (char *)list_get_first(&operands_stack);
      result = apply(operator, operand1, operand2);
      list_prepend(&operands_stack, result);
    }
  }

}
