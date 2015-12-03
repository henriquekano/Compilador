#include "machines.h"
#include "automataPE.h"
#include "semantic_actions.h"

#include "../utils/list.h"
#include "../utils/bool.h"
#include "../utils/file_manager.h"
#include "../utils/string_utils.h"

#include "../semantico/scope.h"
#include "../utils/symbol_table.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int if_counter			= 0;
static int while_counter		= 0;
static int temp_count = 0;
static int last_id 				= 333;
static int TAMANHO 				= 4;
static char* ADDR 				= "/0300";

static struct List operands_stack;
static struct List operator_stack;
static struct List char_pointer_garbage;

static char buffer[100];

typedef enum{
	ACTION_WHILE = 0,
	ACTION_IF = 1,
	ACTION_ELSIF = 2,
	ACTION_ELSE = 3,
	ACTION_OTHER = 4
}action;

static action current_action = ACTION_IF;

void semantic_actions_end(){
  list_destroy(&operator_stack);
  list_destroy(&operands_stack);
  
  list_destroy(&char_pointer_garbage);
}

void nop(Token * token) {
	// DOES NOTHING
}

void get_id(Token * token) {
	last_id = 123123;
}

char *get_begin_program_label(){
	return "";
}

char *get_end_program_label(){
	return "";
}


char *get_temp_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "temp_%d", temp_count);
  temp_count ++;
  return temp;
}

char * get_if_label() {
	if_counter++;
	char * if_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, if_label);
	sprintf(if_label, "if_%d", if_counter);

	return if_label;
}

char * get_do_if_label() {
	char * do_if_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, do_if_label);
	sprintf(do_if_label, "do_if_%d", if_counter);

	return do_if_label;
}

char * get_do_elsif_label() {
	char * do_if_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, do_if_label);
	sprintf(do_if_label, "do_elsif_%d", if_counter);

	return do_if_label;
}

char * get_else_label() {
	// zerar depois
	char * else_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, else_label);
	sprintf(else_label, "else_%d", if_counter);

	return else_label;
}

char * get_endif_label() {
	char * endif_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, endif_label);
	sprintf(endif_label, "endif_%d", if_counter);

	return endif_label;
}

char * get_while_label() {
	while_counter++;
	char * while_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, while_label);
	sprintf(while_label, "while_%d", while_counter);

	return while_label;
}

char * get_do_while_label() {
	char * do_while_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, do_while_label);
	sprintf(do_while_label, "do_while_%d", while_counter);

	return do_while_label;
}

char * get_endwhile_label() {
	char * endwhile_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, endwhile_label);
	sprintf(endwhile_label, "endwhile_%d", while_counter);

	return endwhile_label;
}

char * get_condition_label() {
	char * condition_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, condition_label);
	sprintf(condition_label, "CONDICAO");

	return condition_label;
}

void resolve_if(Token * token) {
	printf("%s\t\tLD\t\t%s\n", get_if_label(), get_condition_label());
	printf("\t\tJN\t\t%s\n", get_endif_label());
	printf("\t\tJP\t\t%s\n", get_do_if_label());
}

void resolve_do_if(Token * token) {
	printf("%s\t\tOS\t\t=0\t\t\n", get_do_if_label());
}

void resolve_endif(Token * token) {
	printf("%s\t\tOS\t\t=0\n", get_endif_label());
}

void resolve_while(Token * token) {
	printf("%s\t\tLD\t\t%s\n", get_while_label(), get_condition_label());
	printf("\t\tJN\t\t%s\n", get_endwhile_label());
	printf("\t\tJP\t\t%s\n", get_do_while_label());
}

void resolve_do_while(Token * token) {
	printf("%s\t\tOS\t\t=0\t\t\n", get_do_while_label());
}

void resolve_endwhile(Token * token) {
	printf("%s\t\tOS\t\t=0\n", get_endwhile_label());
}

void resolve_scan(Token * token) {
	printf("\t\tLV\t\t%s\n", ADDR);
	printf("\t\tMM\t\t_TEMP_1\n");
	printf("\t\tLV\t\t=%d\n", TAMANHO);
	printf("\t\tSC\t\tREAD\t\t; scan()\n");
}

void resolve_print(Token * token) {
	printf("\t\tLV\t\t/FFFF\n");
	printf("\t\tMM\t\t_TEMP_7\n");
	printf("\t\tLV\t\t%s\n", ADDR);
	printf("\t\tMM\t\t_TEMP_1\n");
	printf("\t\tLV\t\t=%d\n", TAMANHO);
	printf("\t\tSC\t\tPRINT\t\t; print()\n");
}

void semantic_actions_init() {
	int n, i, j;

	list_new(&char_pointer_garbage, sizeof(char*), list_free_string);

  list_new(&operands_stack, sizeof(char *), list_free_string);
  list_new(&operator_stack, sizeof(char *), list_free_string);

	for (n = 0; n < N_MACHINE_TYPES; n++) {
		for(i=0; i < MAX_STATES; i++){
			for(j=0; j < N_MACHINE_TOKEN_TYPES; j++){
				actions_on_state_transition[n][i][j] = nop;
			}

			actions_on_machine_return[n][i] = nop;
		}
	}

	// TRANSITION TABLE --------------------------------------

	actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_ID] = get_id;
	actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_SCAN] = resolve_scan;
	actions_on_state_transition[MTYPE_COMMAND][12][MTTYPE_RIGHT_PARENTHESIS] = resolve_print;
	actions_on_state_transition[MTYPE_COMMAND][22][MTTYPE_RIGHT_PARENTHESIS] = resolve_if;
	actions_on_state_transition[MTYPE_COMMAND][23][MTTYPE_DO] = resolve_do_if;
	actions_on_state_transition[MTYPE_COMMAND][27][MTTYPE_ENDIF] = resolve_endif;
	actions_on_state_transition[MTYPE_COMMAND][39][MTTYPE_RIGHT_PARENTHESIS] = resolve_while;
	actions_on_state_transition[MTYPE_COMMAND][41][MTTYPE_DO] = resolve_do_while;
	actions_on_state_transition[MTYPE_COMMAND][45][MTTYPE_ENDWHILE] = resolve_endwhile;

}


//EXPRESSIONS

// OBS: quanto menor, menos prioritario
int operator_precedence(char * operator) {
  if(operator != NULL) {
    if(strcmp(operator, "==") == 0) return 0;
    if(strcmp(operator, ">=") == 0) return 0;
    if(strcmp(operator, "<=") == 0) return 0;
    if(strcmp(operator, ">") == 0) return 0;
    if(strcmp(operator, "<") == 0) return 0;
    if(strcmp(operator, "+") == 0) return 1;
    if(strcmp(operator, "-") == 0) return 1;
    if(strcmp(operator, "*") == 0) return 2;
    if(strcmp(operator, "/") == 0) return 2;
    if(strcmp(operator, "(") == 0) return 3;
    if(strcmp(operator, ")") == 0) return 3;
  }
  return -1;
}

char *get_end_label(){
	switch(current_action){
		case ACTION_IF:
			return get_else_label();
			break;

		case ACTION_ELSIF:
			return get_else_label();
			break;

		case ACTION_WHILE:
			return get_endwhile_label();
			break;

		default:
			get_end_program_label();
			break;
	}
	return "ERROR";
}

char *get_next_action_label(){
	switch(current_action){
		case ACTION_IF:
			return get_do_if_label();
			break;

		case ACTION_ELSIF:
			return get_do_elsif_label();
			break;

		case ACTION_WHILE:
			return get_do_while_label();
			break;

		default:
			get_end_program_label();
			break;
	}
	return "ERROR";
}

char *apply(FILE *file,char *operation, char *operand1, char *operand2){
  bool op1_is_digit = isDigit(operand1);
  bool op2_is_digit = isDigit(operand2);

  char *result_temp = get_temp_label();   
  char *num1_temp = op1_is_digit? get_temp_label() : operand1;
  char *num2_temp = op2_is_digit? get_temp_label() : operand2;

  if(strcmp(operation, "+") == 0){
    // itoa(atoi(operand1) + atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n + %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(file, buffer);
    
  }else if(strcmp(operation, "-") == 0){
    // itoa(atoi(operand1) - atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n - %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(file, buffer);
  }else if(strcmp(operation, "*") == 0){
    // itoa(atoi(operand1) * atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n * %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(file, buffer);
  }else if(strcmp(operation, "/") == 0){
    // itoa(atoi(operand1) / atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n / %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(file, buffer);
  }else if(strcmp(operation, "==") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJZ %s\nJP %s\n", num1_temp, num2_temp, get_next_action_label(), get_end_label());
    write(file, buffer);
  }else if(strcmp(operation, ">=") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJZ %s\nJN %s\nJP %s\n", num2_temp, num1_temp, get_next_action_label(), get_next_action_label(), get_end_label());
    write(file, buffer);
  }else if(strcmp(operation, "<=") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJZ %s\nJN %s\nJP %s\n", num1_temp, num2_temp, get_next_action_label(), get_next_action_label(), get_end_label());
    write(file, buffer);
  }else if(strcmp(operation, ">") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJN %s\nJP %s\n", num2_temp, num1_temp, get_next_action_label(), get_end_label());
    write(file, buffer);
  }else if(strcmp(operation, "<") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJN %s\nJP %s\n", num1_temp, num2_temp, get_next_action_label(), get_end_label());
    write(file, buffer);
  }

  printf("%s %s %s = %s\n", num1_temp, operation, num2_temp, result_temp);
  return result_temp;
}

// https://en.wikipedia.org/wiki/Shunting-yard_algorithm 
void expression_print(FILE *file, Token token){
  char *operand1;
  char *operand2;
  char *operator;
  char *result;

  if(token.type == TT_IDENTIFIER || token.type == TT_INT){
    list_prepend(&operands_stack, token.string);

  } else if(token.type == TT_ARITH_SYMBOL || token.type == TT_COMPARATOR){
    char *last_operator = (char *)list_peek_head(&operator_stack);
    if(list_size(&operator_stack) <= 0 || strcmp(last_operator, "(") == 0 || operator_precedence(token.string) >= operator_precedence(last_operator)){
      list_prepend(&operator_stack, token.string);
    }else if(operator_precedence(token.string) < operator_precedence(last_operator)){
      while(list_size(&operator_stack) > 0){
        operator = list_get_first(&operator_stack);
        operand2 = (char *)list_get_first(&operands_stack);
        operand1 = (char *)list_get_first(&operands_stack);
        result = apply(file, operator, operand1, operand2);
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
      result = apply(file, operator, operand1, operand2);
      list_prepend(&operands_stack, result);
    }
    list_get_first(&operator_stack);
  } else if(token.type == TT_END_OF_COMMAND){
    while(list_size(&operator_stack) > 0){
      operator = list_get_first(&operator_stack);
      operand2 = (char *)list_get_first(&operands_stack);
      operand1 = (char *)list_get_first(&operands_stack);
      result = apply(file, operator, operand1, operand2);
      list_prepend(&operands_stack, result);
    }
  } else if(token.type == TT_SEPARATOR){

  }

}
