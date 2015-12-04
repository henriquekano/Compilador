#include <string.h>
#include "machines.h"
#include "automataPE.h"
#include "../utils/token.h"
#include "../utils/list.h"
#include "../utils/string_utils.h"
#include "../utils/file_manager.h"
#include "semantic_actions.h"
#include "../semantico/scope.h"
#define ASM_FILENAME "SAIDA.asm"

static FILE *output;

static int if_counter			= 0;
static int else_counter			= 0;
static int while_counter		= 0;
static int temp_count			= 0;
static int TAMANHO 				= 4;
static char * ADDR 				= "/0300";
static char * last_command;

static List if_stack; 			// pilha de if, else, elsif, endif
static List output_stack; 		// pilha para despejar o if_stack para saida, depois das labels consertadas
static char last_else_label[50]; 			
static bool inside_if  			= FALSE;
static char buffer[150]; 			

static struct List operands_stack;
static struct List operator_stack;
static struct List char_pointer_garbage;

// void expression_print(FILE *output, Token *token);

typedef enum{
	ACTION_WHILE = 0,
	ACTION_IF = 1,
	ACTION_ELSIF = 2,
	ACTION_ELSE = 3,
	ACTION_OTHER = 4
}action;

static action current_action = ACTION_IF;

char *get_begin_program_label(){
	return "begin";
}

char *get_end_program_label(){
	return "end";
}

char *get_temp_label(){
  char *temp = (char *)malloc(20 * sizeof(char));
  list_append(&char_pointer_garbage, temp);
  sprintf(temp, "temp_%d", temp_count);
  temp_count ++;
  return temp;
}

void semantic_actions_end(){
	scope_destroy();
  list_destroy(&operator_stack);
  list_destroy(&operands_stack);
  list_destroy(&if_stack); 			// pilha de if, else, elsif, endif
	list_destroy(&output_stack);
  list_destroy(&char_pointer_garbage);
}

void nop(Token * token) {
	// DOES NOTHING
}

void resolve_expression(Token * token){
	// expression_print(output, token);
}

void resolve_declaration(Token * token) {
	int var_info[7] = {0, 1, 0, 0, 0, 0, 0};
	scope_add_var(token->string, var_info);
}

// se estiver dentro de um if, imprime na stack
void custom_print(char * pr_buffer){
	if(inside_if == TRUE){
		list_prepend(&if_stack, pr_buffer);
	} else {
		write(output, pr_buffer);
	}
}

char * get_if_label() {
	if_counter++;
	else_counter = 0;
	char * if_label = (char *)malloc(10*sizeof(char));
	sprintf(if_label, "if_%d", if_counter);

	return if_label;
}

char * get_do_if_label() {
	char * do_if_label = (char *)malloc(10*sizeof(char));
	sprintf(do_if_label, "do_if_%d", if_counter);

	return do_if_label;
}

char * get_else_label() {
	else_counter++;
	char * else_label = (char *)malloc(10*sizeof(char));
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
	sprintf(endif_label, "endif_%d", if_counter);

	return endif_label;
}

char * get_while_label() {
	while_counter++;
	char * while_label = (char *)malloc(10*sizeof(char));
	sprintf(while_label, "while_%d", while_counter);

	return while_label;
}

char * get_do_while_label() {
	char * do_while_label = (char *)malloc(10*sizeof(char));
	sprintf(do_while_label, "do_while_%d", while_counter);

	return do_while_label;
}

char * get_endwhile_label() {
	char * endwhile_label = (char *)malloc(10*sizeof(char));
	sprintf(endwhile_label, "endwhile_%d", while_counter);

	return endwhile_label;
}

char * get_condition_label() {
	char * condition_label = (char *)malloc(10*sizeof(char));
	sprintf(condition_label, "CONDICAO");

	return condition_label;
}

void if_stack_to_output() {
	bool havent_found_if = TRUE;
	char * stack_buffer;

	while(havent_found_if){
		stack_buffer = (char *)list_get_first(&if_stack);

		if(startsWith("if", stack_buffer)){
			sprintf(buffer, "\t\tJN\t\t%s\n", last_else_label);
			list_prepend(&output_stack, buffer);

			if(list_size(&if_stack) == 0){
				inside_if = FALSE;
			}

			print_list_on_file(&output_stack, output);
			list_destroy(&output_stack);
			havent_found_if = FALSE;

		} else if(startsWith("do_if", stack_buffer)){
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", get_do_if_label());
			list_prepend(&output_stack, buffer);

		} else if(startsWith("elsif", stack_buffer)){
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", strip(stack_buffer));
			list_prepend(&output_stack, buffer);
			sprintf(buffer, "\t\tJN\t\t%s\t\t\n", last_else_label);
			list_prepend(&output_stack, buffer);

			memcpy(last_else_label, stack_buffer, strlen(stack_buffer));

		} else if(startsWith("else", stack_buffer)){
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", strip(stack_buffer));
			list_prepend(&output_stack, buffer);

			memcpy(last_else_label, stack_buffer, strlen(stack_buffer));

		} else if(startsWith("do_elsif", stack_buffer)){
			// acho que vai dar pau aqui
			sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", stack_buffer);
			list_prepend(&output_stack, buffer);

		} else {
			list_prepend(&output_stack, stack_buffer);
		}
	}
}

void resolve_begin(Token * token) {
	sprintf(buffer, "%s\t\tOS\t\t=0\n", get_begin_program_label());
	custom_print(buffer);
}

void resolve_end(Token * token) {
	sprintf(buffer, "%s\t\tOS\t\t=0\n", get_end_program_label());
	custom_print(buffer);
}

void resolve_if(Token * token) {
	inside_if = TRUE;
	last_command = "if";
	sprintf(buffer, "%s\t\tOS\t\t=0\n", get_if_label());
	custom_print(buffer);
}

void resolve_do_if(Token * token) {
	sprintf(buffer, "\t\tJP\t\t%s\n", get_do_if_label());
	custom_print(buffer);
	sprintf(buffer, "%s\t\tOS\t\t=0\t\t\n", get_do_if_label());
	custom_print(buffer);
}

void resolve_else(Token * token) {
	printf("cheguei no else\n\n\n");
	sprintf(buffer, "\t\tJP\t\t%s\n", get_endif_label());
	custom_print(buffer);
	sprintf(buffer, "%s\n", get_else_label());
	custom_print(buffer);
}

void resolve_elsif(Token * token) {
	last_command = "elsif";
	sprintf(buffer, "\t\tJP\t\t%s\n", get_endif_label());
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
	sprintf(buffer, "%s\t\tOS\t\t=0\n", get_while_label());
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

void resolve_if_else_do(Token * token) {
	printf("last_command= %s\n\n", last_command);
	if(strcmp(last_command, "if") == 0){
		resolve_do_if(token);
	} else if(strcmp(last_command, "elsif") == 0){
		resolve_do_elsif(token);
	}
}

void init_semantic_actions() {
	int n, i, j;

	for (n = 0; n < N_MACHINE_TYPES; n++) {
		for(i=0; i < MAX_STATES; i++){
			for(j=0; j < N_MACHINE_TOKEN_TYPES; j++){
				actions_on_state_transition[n][i][j] = nop;
			}

			actions_on_machine_return[n][i] = nop;
		}
	}

	scope_init(output);
	list_new(&if_stack, 100*sizeof(char*), list_free_string);
	list_new(&output_stack, 100*sizeof(char*), list_free_string);
	output = fopen(ASM_FILENAME, "w");
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

char *apply(FILE *output,char *operation, char *operand1, char *operand2){
  bool op1_is_digit = isDigit(operand1);
  bool op2_is_digit = isDigit(operand2);

  char *result_temp = get_temp_label();   
  char *num1_temp = op1_is_digit? get_temp_label() : operand1;
  char *num2_temp = op2_is_digit? get_temp_label() : operand2;

  if(strcmp(operation, "+") == 0){
    // itoa(atoi(operand1) + atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n + %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(output, buffer);
    
  }else if(strcmp(operation, "-") == 0){
    // itoa(atoi(operand1) - atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n - %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(output, buffer);
  }else if(strcmp(operation, "*") == 0){
    // itoa(atoi(operand1) * atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n * %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(output, buffer);
  }else if(strcmp(operation, "/") == 0){
    // itoa(atoi(operand1) / atoi(operand2), temp, 10);
    sprintf(buffer, "LD %s\n / %s\nMM %s\n", num1_temp, num2_temp, result_temp);
    write(output, buffer);
  }else if(strcmp(operation, "==") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJZ %s\nJP %s\n", num1_temp, num2_temp, get_next_action_label(), get_end_label());
    write(output, buffer);
  }else if(strcmp(operation, ">=") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJZ %s\nJN %s\nJP %s\n", num2_temp, num1_temp, get_next_action_label(), get_next_action_label(), get_end_label());
    write(output, buffer);
  }else if(strcmp(operation, "<=") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJZ %s\nJN %s\nJP %s\n", num1_temp, num2_temp, get_next_action_label(), get_next_action_label(), get_end_label());
    write(output, buffer);
  }else if(strcmp(operation, ">") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJN %s\nJP %s\n", num2_temp, num1_temp, get_next_action_label(), get_end_label());
    write(output, buffer);
  }else if(strcmp(operation, "<") == 0){
  	sprintf(buffer, "LD %s\n - %s\nJN %s\nJP %s\n", num1_temp, num2_temp, get_next_action_label(), get_end_label());
    write(output, buffer);
  }

  printf("%s %s %s = %s\n", num1_temp, operation, num2_temp, result_temp);
  return result_temp;
}

// https://en.wikipedia.org/wiki/Shunting-yard_algorithm 
// void expression_print(FILE *output, Token *token){
//   char *operand1;
//   char *operand2;
//   char *operator;
//   char *result;

//   if(token->type == TT_IDENTIFIER || token->type == TT_INT){
//   	sprintf(buffer, "%s", token->string);
//     list_prepend(&operands_stack, buffer);

//   } else if(token->type == TT_ARITH_SYMBOL || token->type == TT_COMPARATOR){
//     char *last_operator = (char *)list_peek_head(&operator_stack);
//     if(list_size(&operator_stack) <= 0 || strcmp(last_operator, "(") == 0 || operator_precedence(token->string) >= operator_precedence(last_operator)){
//       sprintf(buffer, "%s", token->string);
//       list_prepend(&operator_stack, buffer);
//     }else if(operator_precedence(token->string) < operator_precedence(last_operator)){
//       while(list_size(&operator_stack) > 0){
//         operator = list_get_first(&operator_stack);
//         operand2 = (char *)list_get_first(&operands_stack);
//         operand1 = (char *)list_get_first(&operands_stack);
//         result = apply(output, operator, operand1, operand2);
//         sprintf(buffer, "%s", result);
//         list_prepend(&operands_stack, buffer);
//       }
//       sprintf(buffer, "%s", token->string);
//       list_prepend(&operator_stack, buffer);
//     }
//   } else if(token->type == TT_L_PARENTHESIS){
//     sprintf(buffer, "%s", token->string);
//     list_prepend(&operator_stack, buffer);
//   } else if(token->type == TT_R_PARENTHESIS){
//     while(list_size(&operator_stack) > 0 && strcmp((char *)list_peek_head(&operator_stack), "(") != 0){
//       operator = list_get_first(&operator_stack);
//       operand2 = (char *)list_get_first(&operands_stack);
//       operand1 = (char *)list_get_first(&operands_stack);
//       result = apply(output, operator, operand1, operand2);
//       sprintf(buffer, "%s", result);
//       list_prepend(&operands_stack, buffer);
//     }
//     list_get_first(&operator_stack);
//   } else if(token->type == TT_END_OF_COMMAND){
//     while(list_size(&operator_stack) > 0){
//       operator = list_get_first(&operator_stack);
//       operand2 = (char *)list_get_first(&operands_stack);
//       operand1 = (char *)list_get_first(&operands_stack);
//       result = apply(output, operator, operand1, operand2);
//       sprintf(buffer, "%s", result);
//       list_prepend(&operands_stack, buffer);
//     }
//   }

// }