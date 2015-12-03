#include "machines.h"
#include "automataPE.h"
#include "../utils/token.h"
#include "../utils/list.h"
#include "../utils/string_utils.h"
#include "semantic_actions.h"

#include "../utils/bool.h"
#include "../utils/file_manager.h"

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
static char * ADDR 				= "/0300";

static List if_stack; 			// pilha de if, else, elsif, endif
static List output_stack; 		// pilha para despejar o if_stack para saida, depois das labels consertadas
static char last_else_label[50]; 			
static bool inside_if  			= FALSE;
static char buffer[50]; 			

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

// se estiver dentro de um if, imprime na stack
void custom_print(char pr_buffer[50]){
	if(inside_if == TRUE){
		printf("%s", pr_buffer);
		list_prepend(&if_stack, pr_buffer);
	} else {
		printf(pr_buffer);
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
	else_counter = 0;
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
	else_counter++;
	char * else_label = (char *)malloc(10*sizeof(char));
	list_append(&char_pointer_garbage, else_label);
	sprintf(else_label, "else_%d", if_counter);

	return else_label;
}

char * get_elsif_label() {
	else_counter++;
	char * else_label = (char *)malloc(10*sizeof(char));
	sprintf(else_label, "elsif_%d_%d", if_counter, else_counter);

	return else_label;
}

char * get_do_elsif_label() {
	char * do_elsif_label = (char *)malloc(10*sizeof(char));
	sprintf(do_elsif_label, "do_elsif_%d_%d", if_counter, else_counter);

	return do_elsif_label;
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

void if_stack_to_output() {
	bool havent_found_if = TRUE;
	char stack_buffer[1000];

	while(havent_found_if){
		list_head(&if_stack, &stack_buffer, TRUE);

		printf("stack_buffer: %s\n", stack_buffer);
		// nao sei se funfa
		if(startsWith("if", stack_buffer)){
			sprintf(buffer, "\t\tJN\t\t%s\n", last_else_label);
			list_prepend(&output_stack, buffer);

			// não sei se funciona
			custom_print(list_to_char_array(&output_stack));
			list_destroy(&output_stack);
			havent_found_if = FALSE;

			printf("desempilhei if");

		} else if(startsWith("do_if", stack_buffer)){
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", get_do_if_label());
			list_prepend(&output_stack, buffer);

		} else if(startsWith("elsif", stack_buffer)){
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", trimwhitespace(stack_buffer));
			list_prepend(&output_stack, buffer);
			sprintf(buffer, "\t\tJN\t\t%s\t\t\n", last_else_label);
			list_prepend(&output_stack, buffer);

			memcpy(last_else_label, stack_buffer, strlen(stack_buffer));

		} else if(startsWith("else", stack_buffer)){
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", trimwhitespace(stack_buffer));
			list_prepend(&output_stack, buffer);

			memcpy(last_else_label, stack_buffer, strlen(stack_buffer));

		} else if(startsWith("do_elsif", stack_buffer)){
			// acho que vai dar pau aqui
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", trimwhitespace(stack_buffer));
			list_prepend(&output_stack, buffer);

		} else {
			list_prepend(&output_stack, stack_buffer);
		}

		printf("tamanho da if_stack: %d\n", list_size(&if_stack));

		if(list_size(&if_stack) == 0){
			printf("passei por aqui no inside_if = FALSE");
			inside_if = FALSE;
		}
	}
}

void resolve_if(Token * token) {
	printf("passei pelo resolve if");
	inside_if = TRUE;
	sprintf(buffer, "%s\t\tLD\t\t%s\n", get_if_label(), get_condition_label());
	custom_print(buffer);
}

void resolve_do_if(Token * token) {
	sprintf(buffer, "\t\tJP\t\t%s\n", get_do_if_label());
	custom_print(buffer);
	sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", get_do_if_label());
	custom_print(buffer);
}

void resolve_else(Token * token) {
	sprintf(buffer, "\t\tJP\t\t%s\n", get_endif_label());
	custom_print(buffer);
	sprintf(buffer, "%s\n", get_else_label());
	custom_print(buffer);
}

void resolve_elsif(Token * token) {
	sprintf(buffer, "\t\tJP\t\t%s\n", get_endif_label());
	custom_print(buffer);
	sprintf(buffer, "\t\tLD\t\t%s\n", get_condition_label());
	custom_print(buffer);
	sprintf(buffer, "%s\n", get_elsif_label());
	custom_print(buffer);
	sprintf(buffer, "\t\tJN\t\t%s\n", "empty");
	custom_print(buffer);
	sprintf(buffer, "\t\tJP\t\t%s\n", get_do_elsif_label());
	custom_print(buffer);
}

void resolve_do_elsif(Token * token) {
	sprintf(buffer, "\t\tJP\t\t%s\n", get_do_elsif_label());
	custom_print(buffer);
	sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", get_do_elsif_label());
	custom_print(buffer);
}

void resolve_endif(Token * token) {
	sprintf(buffer, "%s\t\tOS\t\t=0\n", get_endif_label());
	custom_print(buffer);

	if_stack_to_output();
}

void resolve_while(Token * token) {
	sprintf(buffer, "%s\t\tLD\t\t%s\n", get_while_label(), get_condition_label());
	custom_print(buffer);
	sprintf(buffer, "\t\tJN\t\t%s\n", get_endwhile_label());
	custom_print(buffer);
	sprintf(buffer, "\t\tJP\t\t%s\n", get_do_while_label());
	custom_print(buffer);
}

void resolve_do_while(Token * token) {
	sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", get_do_while_label());
	custom_print(buffer);
}

void resolve_endwhile(Token * token) {
	sprintf(buffer, "%s\t\tOS\t\t=0\n", get_endwhile_label());
	custom_print(buffer);
}

void resolve_scan(Token * token) {
	sprintf(buffer, "\t\tLV\t\t%s\n", ADDR);
	custom_print(buffer);
	sprintf(buffer, "\t\tMM\t\t_TEMP_1\n");
	custom_print(buffer);
	sprintf(buffer, "\t\tLV\t\t=%d\n", TAMANHO);
	custom_print(buffer);
	sprintf(buffer, "\t\tSC\t\tREAD\t\t; scan()\n");
	custom_print(buffer);
}

void resolve_print(Token * token) {
	sprintf(buffer, "\t\tLV\t\t/FFFF\n");
	custom_print(buffer);
	sprintf(buffer, "\t\tMM\t\t_TEMP_7\n");
	custom_print(buffer);
	sprintf(buffer, "\t\tLV\t\t%s\n", ADDR);
	custom_print(buffer);
	sprintf(buffer, "\t\tMM\t\t_TEMP_1\n");
	custom_print(buffer);
	sprintf(buffer, "\t\tLV\t\t=%d\n", TAMANHO);
	custom_print(buffer);
	sprintf(buffer, "\t\tSC\t\tPRINT\t\t; print()\n");
	custom_print(buffer);
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

	list_new(&if_stack, sizeof(char*), list_free_string);
	list_new(&output_stack, sizeof(char*), list_free_string);

	// TRANSITION TABLE --------------------------------------

	actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_ID] = get_id;
	actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_SCAN] = resolve_scan;
	actions_on_state_transition[MTYPE_COMMAND][12][MTTYPE_RIGHT_PARENTHESIS] = resolve_print;
	actions_on_state_transition[MTYPE_COMMAND][22][MTTYPE_RIGHT_PARENTHESIS] = resolve_if;
	actions_on_state_transition[MTYPE_COMMAND][23][MTTYPE_DO] = resolve_do_if;

	actions_on_state_transition[MTYPE_COMMAND][27][MTTYPE_ELSIF] = resolve_elsif;
	actions_on_state_transition[MTYPE_COMMAND][27][MTTYPE_ELSE] = resolve_else;

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
