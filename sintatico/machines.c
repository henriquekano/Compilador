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
	command.transition_table[0][MTTYPE_ARRAY] = 1;
	command.transition_table[0][MTTYPE_MATRIX] = 1;

	command.submachine_call[0][MTYPE_DECLARATION] = 2;

	command.transition_table[0][MTTYPE_IF] = 3;
	command.transition_table[0][MTTYPE_WHILE] = 4;
	command.transition_table[0][MTTYPE_WHEN] = 5;
	command.transition_table[0][MTTYPE_SCAN] = 6;
	command.transition_table[0][MTTYPE_PRINT] = 7;
	command.transition_table[1][MTTYPE_EQUAL] = 8;
	command.transition_table[3][MTTYPE_LEFT_PARENTHESIS] = 11;
	command.transition_table[4][MTTYPE_LEFT_PARENTHESIS] = 35;
	command.transition_table[5][MTTYPE_LEFT_PARENTHESIS] = 23;
	command.transition_table[6][MTTYPE_LEFT_PARENTHESIS] = 12;
	command.transition_table[7][MTTYPE_LEFT_PARENTHESIS] = 9;

	command.submachine_call[8][MTYPE_VALUE] = 2;


	command.submachine_call[9][MTYPE_VALUE] = 10;

	command.transition_table[10][MTTYPE_RIGHT_PARENTHESIS] = 2;
	command.transition_table[10][MTTYPE_COMMA] = 9;

	command.submachine_call[11][MTYPE_CONDITION] = 13;

	command.transition_table[12][MTTYPE_ID] = 14;
	command.transition_table[12][MTTYPE_ARRAY] = 14;
	command.transition_table[12][MTTYPE_MATRIX] = 14;
	command.transition_table[13][MTTYPE_RIGHT_PARENTHESIS] = 15;
	command.transition_table[14][MTTYPE_RIGHT_PARENTHESIS] = 2;
	command.transition_table[14][MTTYPE_COMMA] = 12;
	command.transition_table[15][MTTYPE_DO] = 16;

	command.submachine_call[16][MTYPE_COMMAND] = 17;

	command.transition_table[17][MTTYPE_SEMICOLON] = 18;

	command.submachine_call[18][MTYPE_COMMAND] = 17;

	command.transition_table[18][MTTYPE_ELSIF] = 3;
	command.transition_table[18][MTTYPE_ELSE] = 19;
	command.transition_table[18][MTTYPE_ENDIF] = 2;
	command.transition_table[19][MTTYPE_DO] = 20;

	command.submachine_call[20][MTYPE_COMMAND] = 21;

	command.transition_table[21][MTTYPE_SEMICOLON] = 22;

	command.submachine_call[22][MTYPE_COMMAND] = 21;

	command.transition_table[22][MTTYPE_ENDIF] = 2;

	command.submachine_call[23][MTYPE_VALUE] = 24;

	command.transition_table[24][MTTYPE_RIGHT_PARENTHESIS] = 25;
	command.transition_table[25][MTTYPE_IS] = 26;
	command.transition_table[26][MTTYPE_LEFT_PARENTHESIS] = 27;

	command.submachine_call[27][MTYPE_VALUE] = 28;

	command.transition_table[28][MTTYPE_RIGHT_PARENTHESIS] = 29;
	command.transition_table[29][MTTYPE_DO] = 30;

	command.submachine_call[30][MTYPE_COMMAND] = 31;

	command.transition_table[31][MTTYPE_SEMICOLON] = 32;

	command.submachine_call[32][MTYPE_COMMAND] = 31;

	command.transition_table[32][MTTYPE_CONTINUE] = 33;
	command.transition_table[33][MTTYPE_SEMICOLON] = 34;
	command.transition_table[34][MTTYPE_IS] = 26;
	command.transition_table[34][MTTYPE_ENDWHEN] = 2;

	command.submachine_call[35][MTYPE_CONDITION] = 36;

	command.transition_table[36][MTTYPE_RIGHT_PARENTHESIS] = 37;
	command.transition_table[37][MTTYPE_DO] = 38;

	command.submachine_call[38][MTYPE_COMMAND] = 39;

	command.transition_table[39][MTTYPE_SEMICOLON] = 40;

	command.submachine_call[40][MTYPE_COMMAND] = 39;

	command.transition_table[40][MTTYPE_ENDWHILE] = 2;

	// MTYPE_DECLARATION ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&declaration);

	declaration.id = MTYPE_DECLARATION;
	declaration.current_state = 0;
	declaration.final_state[0] = 3;
	declaration.final_state[1] = 15;

	// TRANSITION TABLE --------------------------------------
	declaration.transition_table[0][MTTYPE_TYPE] = 1;
	declaration.transition_table[0][MTTYPE_FUNCTION] = 2;
	declaration.transition_table[1][MTTYPE_ID] = 3;
	declaration.transition_table[1][MTTYPE_ARRAY] = 3;
	declaration.transition_table[1][MTTYPE_MATRIX] = 3;
	declaration.transition_table[2][MTTYPE_TYPE] = 4;
	declaration.transition_table[3][MTTYPE_COMMA] = 1;
	declaration.transition_table[4][MTTYPE_ID] = 5;
	declaration.transition_table[5][MTTYPE_LEFT_PARENTHESIS] = 6;
	declaration.transition_table[6][MTTYPE_TYPE] = 7;
	declaration.transition_table[6][MTTYPE_RIGHT_PARENTHESIS] = 8;
	declaration.transition_table[7][MTTYPE_ID] = 14;
	declaration.transition_table[8][MTTYPE_DO] = 9;

	declaration.submachine_call[9][MTYPE_COMMAND] = 10;

	declaration.transition_table[10][MTTYPE_SEMICOLON] = 11;

	declaration.submachine_call[11][MTYPE_COMMAND] = 10;

	declaration.transition_table[11][MTTYPE_RETURN] = 12;
	declaration.transition_table[11][MTTYPE_ENDFUNCTION] = 13;
	declaration.transition_table[12][MTTYPE_SEMICOLON] = 17;

	declaration.submachine_call[12][MTYPE_VALUE] = 18;

	declaration.transition_table[13][MTTYPE_SEMICOLON] = 15;
	declaration.transition_table[14][MTTYPE_COMMA] = 16;
	declaration.transition_table[14][MTTYPE_RIGHT_PARENTHESIS] = 8;
	declaration.transition_table[16][MTTYPE_TYPE] = 7;
	declaration.transition_table[17][MTTYPE_ENDFUNCTION] = 13;
	declaration.transition_table[18][MTTYPE_SEMICOLON] = 17;

	// MTYPE_CONDITION ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&condition);

	condition.id = MTYPE_CONDITION;
	condition.current_state = 0;
	condition.final_state[0] = 1;
	condition.final_state[1] = 4;

	// TRANSITION TABLE --------------------------------------
	condition.transition_table[0][MTTYPE_BOOL] = 1;

	condition.submachine_call[0][MTYPE_EXPRESSION_ARIT] = 2;


	condition.submachine_call[0][MTYPE_EXPRESSION_BOOL] = 3;

	condition.transition_table[0][MTTYPE_ID] = 4;
	condition.transition_table[0][MTTYPE_ARRAY] = 1;
	condition.transition_table[0][MTTYPE_MATRIX] = 1;
	condition.transition_table[2][MTTYPE_COMPARATOR] = 5;
	condition.transition_table[3][MTTYPE_COMPARATOR_BOOL] = 8;
	condition.transition_table[4][MTTYPE_LEFT_PARENTHESIS] = 6;
	condition.transition_table[4][MTTYPE_DOT] = 7;

	condition.submachine_call[5][MTYPE_EXPRESSION_ARIT] = 1;


	condition.submachine_call[6][MTYPE_VALUE] = 9;

	condition.transition_table[6][MTTYPE_RIGHT_PARENTHESIS] = 1;
	condition.transition_table[7][MTTYPE_ID] = 1;

	condition.submachine_call[8][MTYPE_EXPRESSION_BOOL] = 1;

	condition.transition_table[9][MTTYPE_COMMA] = 10;
	condition.transition_table[9][MTTYPE_RIGHT_PARENTHESIS] = 1;

	condition.submachine_call[10][MTYPE_VALUE] = 9;


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
	expression_arit.final_state[1] = 3;

	// TRANSITION TABLE --------------------------------------
	expression_arit.transition_table[0][MTTYPE_LEFT_PARENTHESIS] = 1;
	expression_arit.transition_table[0][MTTYPE_INT] = 2;
	expression_arit.transition_table[0][MTTYPE_FLOAT] = 2;
	expression_arit.transition_table[0][MTTYPE_ID] = 3;
	expression_arit.transition_table[0][MTTYPE_ARRAY] = 2;
	expression_arit.transition_table[0][MTTYPE_MATRIX] = 2;

	expression_arit.submachine_call[1][MTYPE_EXPRESSION_ARIT] = 4;

	expression_arit.transition_table[2][MTTYPE_MULTIPLICATION] = 0;
	expression_arit.transition_table[2][MTTYPE_DIVISION] = 0;
	expression_arit.transition_table[2][MTTYPE_PLUS] = 0;
	expression_arit.transition_table[2][MTTYPE_MINUS] = 0;
	expression_arit.transition_table[3][MTTYPE_LEFT_PARENTHESIS] = 5;
	expression_arit.transition_table[3][MTTYPE_DOT] = 6;
	expression_arit.transition_table[3][MTTYPE_MULTIPLICATION] = 0;
	expression_arit.transition_table[3][MTTYPE_DIVISION] = 0;
	expression_arit.transition_table[3][MTTYPE_PLUS] = 0;
	expression_arit.transition_table[3][MTTYPE_MINUS] = 0;
	expression_arit.transition_table[4][MTTYPE_RIGHT_PARENTHESIS] = 2;
	expression_arit.transition_table[5][MTTYPE_RIGHT_PARENTHESIS] = 2;

	expression_arit.submachine_call[5][MTYPE_VALUE] = 7;

	expression_arit.transition_table[6][MTTYPE_ID] = 2;
	expression_arit.transition_table[7][MTTYPE_RIGHT_PARENTHESIS] = 2;
	expression_arit.transition_table[7][MTTYPE_COMMA] = 8;

	expression_arit.submachine_call[8][MTYPE_VALUE] = 7;


	// MTYPE_EXPRESSION_BOOL ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&expression_bool);

	expression_bool.id = MTYPE_EXPRESSION_BOOL;
	expression_bool.current_state = 0;
	expression_bool.final_state[0] = 2;
	expression_bool.final_state[1] = 3;

	// TRANSITION TABLE --------------------------------------
	expression_bool.transition_table[0][MTTYPE_LEFT_PARENTHESIS] = 1;
	expression_bool.transition_table[0][MTTYPE_BOOL] = 2;
	expression_bool.transition_table[0][MTTYPE_ID] = 3;
	expression_bool.transition_table[0][MTTYPE_ARRAY] = 2;
	expression_bool.transition_table[0][MTTYPE_MATRIX] = 2;

	expression_bool.submachine_call[1][MTYPE_EXPRESSION_BOOL] = 4;

	expression_bool.transition_table[2][MTTYPE_AND] = 0;
	expression_bool.transition_table[2][MTTYPE_OR] = 0;
	expression_bool.transition_table[3][MTTYPE_LEFT_PARENTHESIS] = 5;
	expression_bool.transition_table[3][MTTYPE_DOT] = 6;
	expression_bool.transition_table[3][MTTYPE_AND] = 0;
	expression_bool.transition_table[3][MTTYPE_OR] = 0;
	expression_bool.transition_table[4][MTTYPE_RIGHT_PARENTHESIS] = 2;
	expression_bool.transition_table[5][MTTYPE_RIGHT_PARENTHESIS] = 2;

	expression_bool.submachine_call[5][MTYPE_VALUE] = 7;

	expression_bool.transition_table[6][MTTYPE_ID] = 2;
	expression_bool.transition_table[7][MTTYPE_RIGHT_PARENTHESIS] = 2;
	expression_bool.transition_table[7][MTTYPE_COMMA] = 8;

	expression_bool.submachine_call[8][MTYPE_VALUE] = 7;


	// MTYPE_VALUE ||||||||||||||||||||||||||||||||||||||||
	setup_machine(&value);

	value.id = MTYPE_VALUE;
	value.current_state = 0;
	value.final_state[0] = 1;
	value.final_state[1] = 2;

	// TRANSITION TABLE --------------------------------------
	value.transition_table[0][MTTYPE_INT] = 1;
	value.transition_table[0][MTTYPE_FLOAT] = 1;
	value.transition_table[0][MTTYPE_STRING] = 1;
	value.transition_table[0][MTTYPE_BOOL] = 1;
	value.transition_table[0][MTTYPE_ID] = 2;
	value.transition_table[0][MTTYPE_ARRAY] = 1;
	value.transition_table[0][MTTYPE_MATRIX] = 1;
	value.transition_table[2][MTTYPE_LEFT_PARENTHESIS] = 3;
	value.transition_table[2][MTTYPE_DOT] = 4;

	value.submachine_call[3][MTYPE_VALUE] = 5;

	value.transition_table[3][MTTYPE_RIGHT_PARENTHESIS] = 1;
	value.transition_table[4][MTTYPE_ID] = 1;
	value.transition_table[5][MTTYPE_COMMA] = 6;
	value.transition_table[5][MTTYPE_RIGHT_PARENTHESIS] = 1;

	value.submachine_call[6][MTYPE_VALUE] = 5;

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
