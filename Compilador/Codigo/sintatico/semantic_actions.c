#include "machines.h"
#include "automataPE.h"
#include "semantic_actions.h"

#include "../utils/list.h"
#include "../utils/bool.h"
#include "../utils/file_manager.h"
#include "../utils/string_utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int if_counter			= 0;
static int else_counter			= 0;
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
	WHILE = 0,
	IF = 1,
	ELSIF = 2,
	ELSE = 3,
	OTHER = 4
}action;

static action current_action = OTHER;

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

char * get_else_label() {
	else_counter++;
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
	// rawSubmachineCallTables[MTYPE_COMMAND][0] = MTYPE_DECLARATION;
	// actions_on_machine_return[MTYPE_COMMAND][0][MTYPE_DECLARATION] = 2;

	// actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_IF] = resolve_if;
	// actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_WHILE] = 4;
	// actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_WHEN] = 5;
	actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_SCAN] = resolve_scan;
	// actions_on_state_transition[MTYPE_COMMAND][0][MTTYPE_PRINT] = 7;
	// actions_on_state_transition[MTYPE_COMMAND][1][MTTYPE_LEFT_BRACKET] = 8;
	// actions_on_state_transition[MTYPE_COMMAND][1][MTTYPE_EQUAL] = 9;
	// actions_on_state_transition[MTYPE_COMMAND][3][MTTYPE_LEFT_PARENTHESIS] = 21;
	// actions_on_state_transition[MTYPE_COMMAND][4][MTTYPE_LEFT_PARENTHESIS] = 37;
	// actions_on_state_transition[MTYPE_COMMAND][5][MTTYPE_LEFT_PARENTHESIS] = 34;
	// actions_on_state_transition[MTYPE_COMMAND][6][MTTYPE_LEFT_PARENTHESIS] = 18;
	// actions_on_state_transition[MTYPE_COMMAND][7][MTTYPE_LEFT_PARENTHESIS] = 10;
	// actions_on_state_transition[MTYPE_COMMAND][8][MTTYPE_INT] = 13;
	// rawSubmachineCallTables[MTYPE_COMMAND][9] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_COMMAND][9][MTYPE_EXPRESSION] = 11;

	// actions_on_state_transition[MTYPE_COMMAND][9][MTTYPE_STRING] = 11;
	// rawSubmachineCallTables[MTYPE_COMMAND][10] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_COMMAND][10][MTYPE_EXPRESSION] = 12;

	// actions_on_state_transition[MTYPE_COMMAND][10][MTTYPE_STRING] = 12;
	// actions_on_state_transition[MTYPE_COMMAND][11][MTTYPE_SEMICOLON] = 2;
	actions_on_state_transition[MTYPE_COMMAND][12][MTTYPE_RIGHT_PARENTHESIS] = resolve_print;
	// actions_on_state_transition[MTYPE_COMMAND][12][MTTYPE_COMMA] = 10;
	// actions_on_state_transition[MTYPE_COMMAND][13][MTTYPE_RIGHT_BRACKET] = 14;
	// actions_on_state_transition[MTYPE_COMMAND][14][MTTYPE_LEFT_BRACKET] = 15;
	// actions_on_state_transition[MTYPE_COMMAND][14][MTTYPE_EQUAL] = 9;
	// actions_on_state_transition[MTYPE_COMMAND][15][MTTYPE_INT] = 16;
	// actions_on_state_transition[MTYPE_COMMAND][16][MTTYPE_RIGHT_BRACKET] = 17;
	// actions_on_state_transition[MTYPE_COMMAND][17][MTTYPE_EQUAL] = 9;
	// actions_on_state_transition[MTYPE_COMMAND][18][MTTYPE_ID] = 19;
	// actions_on_state_transition[MTYPE_COMMAND][19][MTTYPE_LEFT_BRACKET] = 20;
	// actions_on_state_transition[MTYPE_COMMAND][19][MTTYPE_RIGHT_PARENTHESIS] = 11;
	// actions_on_state_transition[MTYPE_COMMAND][19][MTTYPE_COMMA] = 18;
	// actions_on_state_transition[MTYPE_COMMAND][20][MTTYPE_INT] = 24;
	// rawSubmachineCallTables[MTYPE_COMMAND][21] = MTYPE_CONDITION;
	// actions_on_machine_return[MTYPE_COMMAND][21] = resolve_if;

	actions_on_state_transition[MTYPE_COMMAND][22][MTTYPE_RIGHT_PARENTHESIS] = resolve_if;
	actions_on_state_transition[MTYPE_COMMAND][23][MTTYPE_DO] = resolve_do_if;
	// actions_on_state_transition[MTYPE_COMMAND][24][MTTYPE_RIGHT_BRACKET] = 26;
	// rawSubmachineCallTables[MTYPE_COMMAND][25] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][25] = resolve_do_if;

	// actions_on_state_transition[MTYPE_COMMAND][26][MTTYPE_LEFT_BRACKET] = 28;
	// actions_on_state_transition[MTYPE_COMMAND][26][MTTYPE_RIGHT_PARENTHESIS] = 11;
	// actions_on_state_transition[MTYPE_COMMAND][26][MTTYPE_COMMA] = 18;
	// rawSubmachineCallTables[MTYPE_COMMAND][27] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][27][MTYPE_COMMAND] = 27;

	// actions_on_state_transition[MTYPE_COMMAND][27][MTTYPE_ELSIF] = 3;
	// actions_on_state_transition[MTYPE_COMMAND][27][MTTYPE_ELSE] = 29;
	actions_on_state_transition[MTYPE_COMMAND][27][MTTYPE_ENDIF] = resolve_endif;
	// actions_on_state_transition[MTYPE_COMMAND][28][MTTYPE_INT] = 30;
	// actions_on_state_transition[MTYPE_COMMAND][29][MTTYPE_DO] = 32;
	// actions_on_state_transition[MTYPE_COMMAND][30][MTTYPE_RIGHT_BRACKET] = 31;
	// actions_on_state_transition[MTYPE_COMMAND][31][MTTYPE_RIGHT_PARENTHESIS] = 11;
	// actions_on_state_transition[MTYPE_COMMAND][31][MTTYPE_COMMA] = 18;
	// rawSubmachineCallTables[MTYPE_COMMAND][32] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][32][MTYPE_COMMAND] = 33;

	// rawSubmachineCallTables[MTYPE_COMMAND][33] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][33][MTYPE_COMMAND] = 33;

	// actions_on_state_transition[MTYPE_COMMAND][33][MTTYPE_ENDIF] = 2;
	// rawSubmachineCallTables[MTYPE_COMMAND][34] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_COMMAND][34][MTYPE_EXPRESSION] = 35;

	// actions_on_state_transition[MTYPE_COMMAND][35][MTTYPE_RIGHT_PARENTHESIS] = 36;
	// actions_on_state_transition[MTYPE_COMMAND][36][MTTYPE_IS] = 38;
	// rawSubmachineCallTables[MTYPE_COMMAND][37] = MTYPE_CONDITION;
	// actions_on_machine_return[MTYPE_COMMAND][37] = resolve_while;

	// actions_on_state_transition[MTYPE_COMMAND][38][MTTYPE_LEFT_PARENTHESIS] = 40;
	actions_on_state_transition[MTYPE_COMMAND][39][MTTYPE_RIGHT_PARENTHESIS] = resolve_while;
	// rawSubmachineCallTables[MTYPE_COMMAND][40] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_COMMAND][40][MTYPE_EXPRESSION] = 42;

	actions_on_state_transition[MTYPE_COMMAND][41][MTTYPE_DO] = resolve_do_while;
	// actions_on_state_transition[MTYPE_COMMAND][42][MTTYPE_RIGHT_PARENTHESIS] = 44;
	// rawSubmachineCallTables[MTYPE_COMMAND][43] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][43][MTYPE_COMMAND] = 45;

	// actions_on_state_transition[MTYPE_COMMAND][44][MTTYPE_DO] = 46;
	// rawSubmachineCallTables[MTYPE_COMMAND][45] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][45][MTYPE_COMMAND] = 45;

	actions_on_state_transition[MTYPE_COMMAND][45][MTTYPE_ENDWHILE] = resolve_endwhile;
	// rawSubmachineCallTables[MTYPE_COMMAND][46] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][46][MTYPE_COMMAND] = 47;

	// rawSubmachineCallTables[MTYPE_COMMAND][47] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_COMMAND][47][MTYPE_COMMAND] = 47;

	// actions_on_state_transition[MTYPE_COMMAND][47][MTTYPE_CONTINUE] = 48;
	// actions_on_state_transition[MTYPE_COMMAND][48][MTTYPE_SEMICOLON] = 49;
	// actions_on_state_transition[MTYPE_COMMAND][49][MTTYPE_IS] = 38;
	// actions_on_state_transition[MTYPE_COMMAND][49][MTTYPE_ENDWHEN] = 2;

	// // MTYPE_DECLARATION ||||||||||||||||||||||||||||||||||||||||
	// rawFinalStatesTables[MTYPE_DECLARATION][0] = 7;

	// // TRANSITION TABLE --------------------------------------
	// actions_on_state_transition[MTYPE_DECLARATION][0][MTTYPE_TYPE] = 1;
	// actions_on_state_transition[MTYPE_DECLARATION][0][MTTYPE_FUNCTION] = 2;
	// actions_on_state_transition[MTYPE_DECLARATION][0][MTTYPE_STRUCT] = 3;
	// actions_on_state_transition[MTYPE_DECLARATION][1][MTTYPE_ID] = 4;
	// actions_on_state_transition[MTYPE_DECLARATION][2][MTTYPE_TYPE] = 25;
	// actions_on_state_transition[MTYPE_DECLARATION][3][MTTYPE_ID] = 5;
	// actions_on_state_transition[MTYPE_DECLARATION][4][MTTYPE_LEFT_BRACKET] = 6;
	// actions_on_state_transition[MTYPE_DECLARATION][4][MTTYPE_COMMA] = 1;
	// actions_on_state_transition[MTYPE_DECLARATION][4][MTTYPE_SEMICOLON] = 7;
	// actions_on_state_transition[MTYPE_DECLARATION][5][MTTYPE_DO] = 8;
	// actions_on_state_transition[MTYPE_DECLARATION][6][MTTYPE_INT] = 12;
	// actions_on_state_transition[MTYPE_DECLARATION][8][MTTYPE_TYPE] = 9;
	// actions_on_state_transition[MTYPE_DECLARATION][8][MTTYPE_FUNCTION] = 10;
	// actions_on_state_transition[MTYPE_DECLARATION][8][MTTYPE_ENDSTRUCT] = 7;
	// actions_on_state_transition[MTYPE_DECLARATION][9][MTTYPE_ID] = 34;
	// actions_on_state_transition[MTYPE_DECLARATION][10][MTTYPE_TYPE] = 11;
	// actions_on_state_transition[MTYPE_DECLARATION][11][MTTYPE_ID] = 13;
	// actions_on_state_transition[MTYPE_DECLARATION][12][MTTYPE_RIGHT_BRACKET] = 14;
	// actions_on_state_transition[MTYPE_DECLARATION][13][MTTYPE_LEFT_PARENTHESIS] = 15;
	// actions_on_state_transition[MTYPE_DECLARATION][14][MTTYPE_LEFT_BRACKET] = 16;
	// actions_on_state_transition[MTYPE_DECLARATION][14][MTTYPE_COMMA] = 1;
	// actions_on_state_transition[MTYPE_DECLARATION][14][MTTYPE_SEMICOLON] = 7;
	// actions_on_state_transition[MTYPE_DECLARATION][15][MTTYPE_TYPE] = 17;
	// actions_on_state_transition[MTYPE_DECLARATION][15][MTTYPE_RIGHT_PARENTHESIS] = 18;
	// actions_on_state_transition[MTYPE_DECLARATION][16][MTTYPE_INT] = 19;
	// actions_on_state_transition[MTYPE_DECLARATION][17][MTTYPE_ID] = 26;
	// actions_on_state_transition[MTYPE_DECLARATION][18][MTTYPE_DO] = 20;
	// actions_on_state_transition[MTYPE_DECLARATION][19][MTTYPE_RIGHT_BRACKET] = 21;
	// rawSubmachineCallTables[MTYPE_DECLARATION][20] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_DECLARATION][20][MTYPE_COMMAND] = 20;

	// actions_on_state_transition[MTYPE_DECLARATION][20][MTTYPE_RETURN] = 22;
	// actions_on_state_transition[MTYPE_DECLARATION][20][MTTYPE_ENDFUNCTION] = 8;
	// actions_on_state_transition[MTYPE_DECLARATION][21][MTTYPE_COMMA] = 1;
	// actions_on_state_transition[MTYPE_DECLARATION][21][MTTYPE_SEMICOLON] = 7;
	// actions_on_state_transition[MTYPE_DECLARATION][22][MTTYPE_SEMICOLON] = 23;
	// rawSubmachineCallTables[MTYPE_DECLARATION][22] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_DECLARATION][22][MTYPE_EXPRESSION] = 24;

	// actions_on_state_transition[MTYPE_DECLARATION][23][MTTYPE_ENDFUNCTION] = 8;
	// actions_on_state_transition[MTYPE_DECLARATION][24][MTTYPE_SEMICOLON] = 23;
	// actions_on_state_transition[MTYPE_DECLARATION][25][MTTYPE_ID] = 27;
	// actions_on_state_transition[MTYPE_DECLARATION][26][MTTYPE_COMMA] = 28;
	// actions_on_state_transition[MTYPE_DECLARATION][26][MTTYPE_RIGHT_PARENTHESIS] = 18;
	// actions_on_state_transition[MTYPE_DECLARATION][27][MTTYPE_LEFT_PARENTHESIS] = 29;
	// actions_on_state_transition[MTYPE_DECLARATION][28][MTTYPE_TYPE] = 17;
	// actions_on_state_transition[MTYPE_DECLARATION][29][MTTYPE_TYPE] = 30;
	// actions_on_state_transition[MTYPE_DECLARATION][29][MTTYPE_RIGHT_PARENTHESIS] = 31;
	// actions_on_state_transition[MTYPE_DECLARATION][30][MTTYPE_ID] = 41;
	// actions_on_state_transition[MTYPE_DECLARATION][31][MTTYPE_DO] = 32;
	// rawSubmachineCallTables[MTYPE_DECLARATION][32] = MTYPE_COMMAND;
	// actions_on_machine_return[MTYPE_DECLARATION][32][MTYPE_COMMAND] = 32;

	// actions_on_state_transition[MTYPE_DECLARATION][32][MTTYPE_RETURN] = 33;
	// actions_on_state_transition[MTYPE_DECLARATION][32][MTTYPE_ENDFUNCTION] = 7;
	// actions_on_state_transition[MTYPE_DECLARATION][33][MTTYPE_SEMICOLON] = 36;
	// rawSubmachineCallTables[MTYPE_DECLARATION][33] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_DECLARATION][33][MTYPE_EXPRESSION] = 37;

	// actions_on_state_transition[MTYPE_DECLARATION][34][MTTYPE_LEFT_BRACKET] = 35;
	// actions_on_state_transition[MTYPE_DECLARATION][34][MTTYPE_COMMA] = 9;
	// actions_on_state_transition[MTYPE_DECLARATION][34][MTTYPE_SEMICOLON] = 8;
	// actions_on_state_transition[MTYPE_DECLARATION][35][MTTYPE_INT] = 38;
	// actions_on_state_transition[MTYPE_DECLARATION][36][MTTYPE_ENDFUNCTION] = 7;
	// actions_on_state_transition[MTYPE_DECLARATION][37][MTTYPE_SEMICOLON] = 36;
	// actions_on_state_transition[MTYPE_DECLARATION][38][MTTYPE_RIGHT_BRACKET] = 39;
	// actions_on_state_transition[MTYPE_DECLARATION][39][MTTYPE_LEFT_BRACKET] = 40;
	// actions_on_state_transition[MTYPE_DECLARATION][39][MTTYPE_COMMA] = 9;
	// actions_on_state_transition[MTYPE_DECLARATION][39][MTTYPE_SEMICOLON] = 8;
	// actions_on_state_transition[MTYPE_DECLARATION][40][MTTYPE_INT] = 42;
	// actions_on_state_transition[MTYPE_DECLARATION][41][MTTYPE_COMMA] = 43;
	// actions_on_state_transition[MTYPE_DECLARATION][41][MTTYPE_RIGHT_PARENTHESIS] = 31;
	// actions_on_state_transition[MTYPE_DECLARATION][42][MTTYPE_RIGHT_BRACKET] = 44;
	// actions_on_state_transition[MTYPE_DECLARATION][43][MTTYPE_TYPE] = 30;
	// actions_on_state_transition[MTYPE_DECLARATION][44][MTTYPE_COMMA] = 9;
	// actions_on_state_transition[MTYPE_DECLARATION][44][MTTYPE_SEMICOLON] = 8;

	// // MTYPE_CONDITION ||||||||||||||||||||||||||||||||||||||||
	// rawFinalStatesTables[MTYPE_CONDITION][0] = 1;
	// rawFinalStatesTables[MTYPE_CONDITION][1] = 3;

	// // TRANSITION TABLE --------------------------------------
	// rawSubmachineCallTables[MTYPE_CONDITION][0] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_CONDITION][0][MTYPE_EXPRESSION] = 1;

	// actions_on_state_transition[MTYPE_CONDITION][1][MTTYPE_COMPARATOR] = 2;
	// rawSubmachineCallTables[MTYPE_CONDITION][2] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_CONDITION][2][MTYPE_EXPRESSION] = 3;


	// // MTYPE_EXPRESSION ||||||||||||||||||||||||||||||||||||||||
	// rawFinalStatesTables[MTYPE_EXPRESSION][0] = 3;
	// rawFinalStatesTables[MTYPE_EXPRESSION][1] = 4;
	// rawFinalStatesTables[MTYPE_EXPRESSION][2] = 10;

	// // TRANSITION TABLE --------------------------------------
	// actions_on_state_transition[MTYPE_EXPRESSION][0][MTTYPE_NOT] = 1;
	// actions_on_state_transition[MTYPE_EXPRESSION][0][MTTYPE_LEFT_PARENTHESIS] = 2;
	// actions_on_state_transition[MTYPE_EXPRESSION][0][MTTYPE_BOOL] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][0][MTTYPE_ID] = 4;
	// actions_on_state_transition[MTYPE_EXPRESSION][0][MTTYPE_INT] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][0][MTTYPE_FLOAT] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][1][MTTYPE_LEFT_PARENTHESIS] = 2;
	// actions_on_state_transition[MTYPE_EXPRESSION][1][MTTYPE_BOOL] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][1][MTTYPE_ID] = 4;
	// rawSubmachineCallTables[MTYPE_EXPRESSION][2] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_EXPRESSION][2][MTYPE_EXPRESSION] = 5;

	// actions_on_state_transition[MTYPE_EXPRESSION][3][MTTYPE_MULTIPLICATION] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][3][MTTYPE_DIVISION] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][3][MTTYPE_AND] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][3][MTTYPE_PLUS] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][3][MTTYPE_MINUS] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][3][MTTYPE_OR] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_LEFT_PARENTHESIS] = 6;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_LEFT_BRACKET] = 7;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_DOT] = 8;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_MULTIPLICATION] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_DIVISION] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_AND] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_PLUS] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_MINUS] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][4][MTTYPE_OR] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][5][MTTYPE_RIGHT_PARENTHESIS] = 3;
	// rawSubmachineCallTables[MTYPE_EXPRESSION][6] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_EXPRESSION][6][MTYPE_EXPRESSION] = 13;

	// actions_on_state_transition[MTYPE_EXPRESSION][6][MTTYPE_RIGHT_PARENTHESIS] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][7][MTTYPE_INT] = 9;
	// actions_on_state_transition[MTYPE_EXPRESSION][8][MTTYPE_ID] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][9][MTTYPE_RIGHT_BRACKET] = 10;
	// actions_on_state_transition[MTYPE_EXPRESSION][10][MTTYPE_LEFT_BRACKET] = 11;
	// actions_on_state_transition[MTYPE_EXPRESSION][10][MTTYPE_MULTIPLICATION] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][10][MTTYPE_DIVISION] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][10][MTTYPE_AND] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][10][MTTYPE_PLUS] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][10][MTTYPE_MINUS] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][10][MTTYPE_OR] = 0;
	// actions_on_state_transition[MTYPE_EXPRESSION][11][MTTYPE_INT] = 12;
	// actions_on_state_transition[MTYPE_EXPRESSION][12][MTTYPE_RIGHT_BRACKET] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][13][MTTYPE_RIGHT_PARENTHESIS] = 3;
	// actions_on_state_transition[MTYPE_EXPRESSION][13][MTTYPE_COMMA] = 14;
	// rawSubmachineCallTables[MTYPE_EXPRESSION][14] = MTYPE_EXPRESSION;
	// actions_on_machine_return[MTYPE_EXPRESSION][14][MTYPE_EXPRESSION] = 13;
}


//EXPRESSIONS

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
