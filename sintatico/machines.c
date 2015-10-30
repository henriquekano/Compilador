#include "machines.h"

void setup_machine(Machine *machine) {
	int i, j;

	machine->current_state = MINVALID_STATE;
	machine->id = MTYPE_INVALID;

	for(i = 0; i < MAX_FINAL_STATES; i++) {
		machine->final_state[i] = MINVALID_STATE;
	}
	for(i=0; i < MAX_STATES; i++){
		for(j=0; j < N_MACHINE_TOKEN_TYPES; j++){
			machine->transition_table[i][j] = MINVALID_STATE;
		}
	}
	for(i=0; i < MAX_STATES; i++) {
		for(j=0; j < N_MACHINE_TYPES; j++) {
			machine->submachine_call[i][j] = MINVALID_STATE;
		}
	}
}

void init_machines() {
	Machine program, command, declaration, condition, expression, expression_arit, expression_bool, value;

	// START MACHINE GENERATOR INPUT $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	
	// MTYPE_PROGRAM ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&program);

	program.id = MTYPE_PROGRAM;
	program.current_state = 0;
	program.final_state[0] = 4;

	// TRANSITION TABLE --------------------------------------
	program.transition_table[0][MTTYPE_BEGIN] = 1;

	program.submachine_call[1][MTYPE_COMMAND] = 2;

	program.transition_table[2][MTTYPE_SEMICOLON] = 3;

	program.submachine_call[3][MTYPE_COMMAND] = 2;

	program.transition_table[3][MTTYPE_END] = 4;

	// MTYPE_COMMAND ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&command);

	command.id = MTYPE_COMMAND;
	command.current_state = 0;
	command.final_state[0] = 2;

	// TRANSITION TABLE --------------------------------------
	command.transition_table[0][MTTYPE_ID] = 1;

	command.submachine_call[0][MTYPE_DECLARATION] = 2;

	command.transition_table[0][MTTYPE_IF] = 3;
	command.transition_table[0][MTTYPE_WHILE] = 4;
	command.transition_table[0][MTTYPE_WHEN] = 5;
	command.transition_table[0][MTTYPE_SCAN] = 6;
	command.transition_table[0][MTTYPE_PRINT] = 7;
	command.transition_table[1][MTTYPE_LEFT_BRACKET] = 8;
	command.transition_table[3][MTTYPE_LEFT_PARENTHESIS] = 23;
	command.transition_table[4][MTTYPE_LEFT_PARENTHESIS] = 44;
	command.transition_table[5][MTTYPE_LEFT_PARENTHESIS] = 35;
	command.transition_table[6][MTTYPE_LEFT_PARENTHESIS] = 16;
	command.transition_table[7][MTTYPE_LEFT_PARENTHESIS] = 9;
	command.transition_table[8][MTTYPE_D] = 10;

	command.submachine_call[9][MTYPE_VALUE] = 11;

	command.transition_table[10][MTTYPE_D] = 10;
	command.transition_table[10][MTTYPE_RIGHT_BRACKET] = 12;
	command.transition_table[11][MTTYPE_RIGHT_PARENTHESIS] = 2;
	command.transition_table[11][MTTYPE_COMMA] = 9;
	command.transition_table[12][MTTYPE_LEFT_BRACKET] = 13;
	command.transition_table[12][MTTYPE_EQUAL] = 14;
	command.transition_table[13][MTTYPE_D] = 15;

	command.submachine_call[14][MTYPE_VALUE] = 2;

	command.transition_table[15][MTTYPE_D] = 15;
	command.transition_table[15][MTTYPE_RIGHT_BRACKET] = 17;
	command.transition_table[16][MTTYPE_ID] = 18;
	command.transition_table[17][MTTYPE_EQUAL] = 14;
	command.transition_table[18][MTTYPE_LEFT_BRACKET] = 19;
	command.transition_table[19][MTTYPE_D] = 20;
	command.transition_table[20][MTTYPE_D] = 20;
	command.transition_table[20][MTTYPE_RIGHT_BRACKET] = 21;
	command.transition_table[21][MTTYPE_LEFT_BRACKET] = 22;
	command.transition_table[21][MTTYPE_RIGHT_PARENTHESIS] = 2;
	command.transition_table[21][MTTYPE_COMMA] = 16;
	command.transition_table[22][MTTYPE_D] = 29;

	command.submachine_call[23][MTYPE_CONDITION] = 24;

	command.transition_table[24][MTTYPE_RIGHT_PARENTHESIS] = 25;
	command.transition_table[25][MTTYPE_DO] = 26;

	command.submachine_call[26][MTYPE_COMMAND] = 27;

	command.transition_table[27][MTTYPE_SEMICOLON] = 28;

	command.submachine_call[28][MTYPE_COMMAND] = 27;

	command.transition_table[28][MTTYPE_ELSIF] = 3;
	command.transition_table[28][MTTYPE_ELSE] = 30;
	command.transition_table[28][MTTYPE_ENDIF] = 2;
	command.transition_table[29][MTTYPE_D] = 29;
	command.transition_table[29][MTTYPE_RIGHT_BRACKET] = 31;
	command.transition_table[30][MTTYPE_DO] = 32;
	command.transition_table[31][MTTYPE_RIGHT_PARENTHESIS] = 2;
	command.transition_table[31][MTTYPE_COMMA] = 16;

	command.submachine_call[32][MTYPE_COMMAND] = 33;

	command.transition_table[33][MTTYPE_SEMICOLON] = 34;

	command.submachine_call[34][MTYPE_COMMAND] = 33;

	command.transition_table[34][MTTYPE_ENDIF] = 2;

	command.submachine_call[35][MTYPE_VALUE] = 36;

	command.transition_table[36][MTTYPE_RIGHT_PARENTHESIS] = 37;
	command.transition_table[37][MTTYPE_IS] = 38;
	command.transition_table[38][MTTYPE_LEFT_PARENTHESIS] = 39;

	command.submachine_call[39][MTYPE_VALUE] = 40;

	command.transition_table[40][MTTYPE_RIGHT_PARENTHESIS] = 41;
	command.transition_table[41][MTTYPE_DO] = 42;

	command.submachine_call[42][MTYPE_COMMAND] = 43;

	command.transition_table[43][MTTYPE_SEMICOLON] = 45;

	command.submachine_call[44][MTYPE_CONDITION] = 46;


	command.submachine_call[45][MTYPE_COMMAND] = 43;

	command.transition_table[45][MTTYPE_CONTINUE] = 47;
	command.transition_table[46][MTTYPE_RIGHT_PARENTHESIS] = 48;
	command.transition_table[47][MTTYPE_SEMICOLON] = 49;
	command.transition_table[48][MTTYPE_DO] = 50;
	command.transition_table[49][MTTYPE_IS] = 38;
	command.transition_table[49][MTTYPE_ENDWHEN] = 2;

	command.submachine_call[50][MTYPE_COMMAND] = 51;

	command.transition_table[51][MTTYPE_SEMICOLON] = 52;

	command.submachine_call[52][MTYPE_COMMAND] = 51;

	command.transition_table[52][MTTYPE_ENDWHILE] = 2;

	// MTYPE_DECLARATION ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&declaration);

	declaration.id = MTYPE_DECLARATION;
	declaration.current_state = 0;
	declaration.final_state[0] = 9;
	declaration.final_state[1] = 18;
	declaration.final_state[2] = 22;

	// TRANSITION TABLE --------------------------------------
	declaration.transition_table[0][MTTYPE_TYPE] = 1;
	declaration.transition_table[0][MTTYPE_FUNCTION] = 2;
	declaration.transition_table[1][MTTYPE_ID] = 3;
	declaration.transition_table[2][MTTYPE_TYPE] = 4;
	declaration.transition_table[3][MTTYPE_LEFT_BRACKET] = 5;
	declaration.transition_table[4][MTTYPE_ID] = 6;
	declaration.transition_table[5][MTTYPE_D] = 7;
	declaration.transition_table[6][MTTYPE_LEFT_PARENTHESIS] = 8;
	declaration.transition_table[7][MTTYPE_D] = 7;
	declaration.transition_table[7][MTTYPE_RIGHT_BRACKET] = 9;
	declaration.transition_table[8][MTTYPE_TYPE] = 10;
	declaration.transition_table[8][MTTYPE_RIGHT_PARENTHESIS] = 11;
	declaration.transition_table[9][MTTYPE_LEFT_BRACKET] = 12;
	declaration.transition_table[9][MTTYPE_COMMA] = 1;
	declaration.transition_table[10][MTTYPE_ID] = 23;
	declaration.transition_table[11][MTTYPE_DO] = 13;
	declaration.transition_table[12][MTTYPE_D] = 19;

	declaration.submachine_call[13][MTYPE_COMMAND] = 14;

	declaration.transition_table[14][MTTYPE_SEMICOLON] = 15;

	declaration.submachine_call[15][MTYPE_COMMAND] = 14;

	declaration.transition_table[15][MTTYPE_RETURN] = 16;
	declaration.transition_table[15][MTTYPE_ENDFUNCTION] = 17;
	declaration.transition_table[16][MTTYPE_SEMICOLON] = 20;

	declaration.submachine_call[16][MTYPE_VALUE] = 21;

	declaration.transition_table[17][MTTYPE_SEMICOLON] = 18;
	declaration.transition_table[19][MTTYPE_D] = 19;
	declaration.transition_table[19][MTTYPE_RIGHT_BRACKET] = 22;
	declaration.transition_table[20][MTTYPE_ENDFUNCTION] = 17;
	declaration.transition_table[21][MTTYPE_SEMICOLON] = 20;
	declaration.transition_table[22][MTTYPE_COMMA] = 1;
	declaration.transition_table[23][MTTYPE_COMMA] = 24;
	declaration.transition_table[23][MTTYPE_RIGHT_PARENTHESIS] = 11;
	declaration.transition_table[24][MTTYPE_TYPE] = 10;

	// MTYPE_CONDITION ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&condition);

	condition.id = MTYPE_CONDITION;
	condition.current_state = 0;
	condition.final_state[0] = 1;
	condition.final_state[1] = 13;

	// TRANSITION TABLE --------------------------------------
	condition.transition_table[0][MTTYPE_BOOL] = 1;

	condition.submachine_call[0][MTYPE_EXPRESSION_ARIT] = 2;


	condition.submachine_call[0][MTYPE_EXPRESSION_BOOL] = 3;

	condition.transition_table[0][MTTYPE_ID] = 4;
	condition.transition_table[2][MTTYPE_COMPARATOR] = 8;
	condition.transition_table[3][MTTYPE_COMPARATOR_BOOL] = 10;
	condition.transition_table[4][MTTYPE_LEFT_BRACKET] = 5;
	condition.transition_table[4][MTTYPE_LEFT_PARENTHESIS] = 6;
	condition.transition_table[4][MTTYPE_DOT] = 7;
	condition.transition_table[5][MTTYPE_D] = 12;

	condition.submachine_call[6][MTYPE_VALUE] = 9;

	condition.transition_table[6][MTTYPE_RIGHT_PARENTHESIS] = 1;
	condition.transition_table[7][MTTYPE_ID] = 1;

	condition.submachine_call[8][MTYPE_EXPRESSION_ARIT] = 1;

	condition.transition_table[9][MTTYPE_COMMA] = 11;
	condition.transition_table[9][MTTYPE_RIGHT_PARENTHESIS] = 1;

	condition.submachine_call[10][MTYPE_EXPRESSION_BOOL] = 1;


	condition.submachine_call[11][MTYPE_VALUE] = 9;

	condition.transition_table[12][MTTYPE_D] = 12;
	condition.transition_table[12][MTTYPE_RIGHT_BRACKET] = 13;
	condition.transition_table[13][MTTYPE_LEFT_BRACKET] = 14;
	condition.transition_table[14][MTTYPE_D] = 15;
	condition.transition_table[15][MTTYPE_D] = 15;
	condition.transition_table[15][MTTYPE_RIGHT_BRACKET] = 1;

	// MTYPE_EXPRESSION ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&expression);

	expression.id = MTYPE_EXPRESSION;
	expression.current_state = 0;
	expression.final_state[0] = 1;

	// TRANSITION TABLE --------------------------------------

	expression.submachine_call[0][MTYPE_EXPRESSION_BOOL] = 1;


	expression.submachine_call[0][MTYPE_EXPRESSION_ARIT] = 1;


	// MTYPE_EXPRESSION_ARIT ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&expression_arit);

	expression_arit.id = MTYPE_EXPRESSION_ARIT;
	expression_arit.current_state = 0;
	expression_arit.final_state[0] = 2;
	expression_arit.final_state[1] = 8;
	expression_arit.final_state[2] = 10;
	expression_arit.final_state[3] = 15;

	// TRANSITION TABLE --------------------------------------
	expression_arit.transition_table[0][MTTYPE_LEFT_PARENTHESIS] = 1;
	expression_arit.transition_table[0][MTTYPE_D] = 2;
	expression_arit.transition_table[0][MTTYPE_ID] = 3;

	expression_arit.submachine_call[1][MTYPE_EXPRESSION_ARIT] = 4;

	expression_arit.transition_table[2][MTTYPE_D] = 2;
	expression_arit.transition_table[2][MTTYPE_DOT] = 15;
	expression_arit.transition_table[2][MTTYPE_MULTIPLICATION] = 0;
	expression_arit.transition_table[2][MTTYPE_DIVISION] = 0;
	expression_arit.transition_table[2][MTTYPE_PLUS] = 0;
	expression_arit.transition_table[2][MTTYPE_MINUS] = 0;
	expression_arit.transition_table[3][MTTYPE_LEFT_PARENTHESIS] = 5;
	expression_arit.transition_table[3][MTTYPE_DOT] = 6;
	expression_arit.transition_table[3][MTTYPE_LEFT_BRACKET] = 7;
	expression_arit.transition_table[4][MTTYPE_RIGHT_PARENTHESIS] = 8;
	expression_arit.transition_table[5][MTTYPE_RIGHT_PARENTHESIS] = 8;

	expression_arit.submachine_call[5][MTYPE_VALUE] = 13;

	expression_arit.transition_table[6][MTTYPE_ID] = 8;
	expression_arit.transition_table[7][MTTYPE_D] = 9;
	expression_arit.transition_table[8][MTTYPE_MULTIPLICATION] = 0;
	expression_arit.transition_table[8][MTTYPE_DIVISION] = 0;
	expression_arit.transition_table[8][MTTYPE_PLUS] = 0;
	expression_arit.transition_table[8][MTTYPE_MINUS] = 0;
	expression_arit.transition_table[9][MTTYPE_D] = 9;
	expression_arit.transition_table[9][MTTYPE_RIGHT_BRACKET] = 10;
	expression_arit.transition_table[10][MTTYPE_LEFT_BRACKET] = 11;
	expression_arit.transition_table[10][MTTYPE_MULTIPLICATION] = 0;
	expression_arit.transition_table[10][MTTYPE_DIVISION] = 0;
	expression_arit.transition_table[10][MTTYPE_PLUS] = 0;
	expression_arit.transition_table[10][MTTYPE_MINUS] = 0;
	expression_arit.transition_table[11][MTTYPE_D] = 12;
	expression_arit.transition_table[12][MTTYPE_D] = 12;
	expression_arit.transition_table[12][MTTYPE_RIGHT_BRACKET] = 8;
	expression_arit.transition_table[13][MTTYPE_RIGHT_PARENTHESIS] = 8;
	expression_arit.transition_table[13][MTTYPE_COMMA] = 14;

	expression_arit.submachine_call[14][MTYPE_VALUE] = 13;

	expression_arit.transition_table[15][MTTYPE_D] = 15;
	expression_arit.transition_table[15][MTTYPE_MULTIPLICATION] = 0;
	expression_arit.transition_table[15][MTTYPE_DIVISION] = 0;
	expression_arit.transition_table[15][MTTYPE_PLUS] = 0;
	expression_arit.transition_table[15][MTTYPE_MINUS] = 0;

	// MTYPE_EXPRESSION_BOOL ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&expression_bool);

	expression_bool.id = MTYPE_EXPRESSION_BOOL;
	expression_bool.current_state = 0;
	expression_bool.final_state[0] = 2;
	expression_bool.final_state[1] = 9;

	// TRANSITION TABLE --------------------------------------
	expression_bool.transition_table[0][MTTYPE_LEFT_PARENTHESIS] = 1;
	expression_bool.transition_table[0][MTTYPE_BOOL] = 2;
	expression_bool.transition_table[0][MTTYPE_ID] = 3;

	expression_bool.submachine_call[1][MTYPE_EXPRESSION_BOOL] = 4;

	expression_bool.transition_table[2][MTTYPE_AND] = 0;
	expression_bool.transition_table[2][MTTYPE_OR] = 0;
	expression_bool.transition_table[3][MTTYPE_LEFT_PARENTHESIS] = 5;
	expression_bool.transition_table[3][MTTYPE_LEFT_BRACKET] = 6;
	expression_bool.transition_table[3][MTTYPE_DOT] = 7;
	expression_bool.transition_table[4][MTTYPE_RIGHT_PARENTHESIS] = 2;
	expression_bool.transition_table[5][MTTYPE_RIGHT_PARENTHESIS] = 2;

	expression_bool.submachine_call[5][MTYPE_VALUE] = 12;

	expression_bool.transition_table[6][MTTYPE_D] = 8;
	expression_bool.transition_table[7][MTTYPE_ID] = 2;
	expression_bool.transition_table[8][MTTYPE_D] = 8;
	expression_bool.transition_table[8][MTTYPE_RIGHT_BRACKET] = 9;
	expression_bool.transition_table[9][MTTYPE_LEFT_BRACKET] = 10;
	expression_bool.transition_table[9][MTTYPE_AND] = 0;
	expression_bool.transition_table[9][MTTYPE_OR] = 0;
	expression_bool.transition_table[10][MTTYPE_D] = 11;
	expression_bool.transition_table[11][MTTYPE_D] = 11;
	expression_bool.transition_table[11][MTTYPE_RIGHT_BRACKET] = 2;
	expression_bool.transition_table[12][MTTYPE_RIGHT_PARENTHESIS] = 2;
	expression_bool.transition_table[12][MTTYPE_COMMA] = 13;

	expression_bool.submachine_call[13][MTYPE_VALUE] = 12;


	// MTYPE_VALUE ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&value);

	value.id = MTYPE_VALUE;
	value.current_state = 0;
	value.final_state[0] = 1;
	value.final_state[1] = 4;
	value.final_state[2] = 6;
	value.final_state[3] = 13;

	// TRANSITION TABLE --------------------------------------
	value.transition_table[0][MTTYPE_D] = 1;
	value.transition_table[0][MTTYPE_DOUBLE_QUOTE] = 2;
	value.transition_table[0][MTTYPE_SINGLE_QUOTE] = 3;
	value.transition_table[0][MTTYPE_BOOL] = 4;
	value.transition_table[0][MTTYPE_ID] = 5;
	value.transition_table[1][MTTYPE_D] = 1;
	value.transition_table[1][MTTYPE_DOT] = 6;
	value.transition_table[2][MTTYPE_DOUBLE_QUOTE] = 4;
	value.transition_table[2][MTTYPE_ANY] = 2;
	value.transition_table[3][MTTYPE_ANY] = 3;
	value.transition_table[3][MTTYPE_SINGLE_QUOTE] = 4;
	value.transition_table[5][MTTYPE_DOT] = 7;
	value.transition_table[5][MTTYPE_LEFT_BRACKET] = 8;
	value.transition_table[5][MTTYPE_LEFT_PARENTHESIS] = 9;
	value.transition_table[6][MTTYPE_D] = 6;
	value.transition_table[7][MTTYPE_ID] = 4;
	value.transition_table[8][MTTYPE_D] = 12;

	value.submachine_call[9][MTYPE_VALUE] = 10;

	value.transition_table[9][MTTYPE_RIGHT_PARENTHESIS] = 4;
	value.transition_table[10][MTTYPE_COMMA] = 11;
	value.transition_table[10][MTTYPE_RIGHT_PARENTHESIS] = 4;

	value.submachine_call[11][MTYPE_VALUE] = 10;

	value.transition_table[12][MTTYPE_D] = 12;
	value.transition_table[12][MTTYPE_RIGHT_BRACKET] = 13;
	value.transition_table[13][MTTYPE_LEFT_BRACKET] = 14;
	value.transition_table[14][MTTYPE_D] = 15;
	value.transition_table[15][MTTYPE_D] = 15;
	value.transition_table[15][MTTYPE_RIGHT_BRACKET] = 4;

	// END MACHINE GENERATOR INPUT $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	machines[MTYPE_PROGRAM] = program;
	machines[MTYPE_COMMAND] = command;
	machines[MTYPE_DECLARATION] = declaration;
	machines[MTYPE_CONDITION] = condition;
	machines[MTYPE_EXPRESSION_ARIT] = expression_arit;
	machines[MTYPE_EXPRESSION_BOOL] = expression_bool;
	machines[MTYPE_EXPRESSION] = expression;
	machines[MTYPE_VALUE] = value;
}
