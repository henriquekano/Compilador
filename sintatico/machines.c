#include "machines.h"
#include "automataPE.h"

void init_machines(AutomataPE *automata) {
	int initialMachine = MTYPE_PROGRAM;
	int n, i, j	
	int rawTransitionTables[N_MACHINE_TYPES][MAX_STATES][N_MACHINE_TOKEN_TYPES];
	int rawFinalStatesTables[N_MACHINE_TYPES][MAX_FINAL_STATES];
	int rawSubmachineCallTables[N_MACHINE_TYPES][MAX_STATES][N_MACHINE_TOKEN_TYPES];
	int rawAfterCallTables[N_MACHINE_TYPES][MAX_STATES][N_MACHINE_TOKEN_TYPES];

	for (n = 0; n < N_MACHINE_TYPES; n++) {
		for(i = 0; i < MAX_FINAL_STATES; i++) {
			rawFinalStatesTables[n][i] = MINVALID_STATE;
		}
		for(i=0; i < MAX_STATES; i++){
			for(j=0; j < N_MACHINE_TOKEN_TYPES; j++){
				rawTransitionTables[n][i][j] = MINVALID_STATE;
				rawSubmachineCallTables[n][i][j] = MINVALID_STATE;
				rawAfterCallTables[n][i][j] = MINVALID_STATE;
			}
		}
	}
	
	// MTYPE_PROGRAM ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_PROGRAM][0] = 4;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_PROGRAM][0][MTTYPE_BEGIN] = 1;
	rawSubmachineCallTables[MTYPE_PROGRAM][1] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_PROGRAM][1][MTYPE_COMMAND] = 2;

	rawTransitionTables[MTYPE_PROGRAM][2][MTTYPE_SEMICOLON] = 3;
	rawSubmachineCallTables[MTYPE_PROGRAM][3] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_PROGRAM][3][MTYPE_COMMAND] = 2;

	rawTransitionTables[MTYPE_PROGRAM][3][MTTYPE_END] = 4;

	// MTYPE_COMMAND ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_COMMAND][0] = 2;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_ID] = 1;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_ARRAY] = 1;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_MATRIX] = 1;
	rawSubmachineCallTables[MTYPE_COMMAND][0] = MTYPE_DECLARATION;
	rawAfterCallTables[MTYPE_COMMAND][0][MTYPE_DECLARATION] = 2;

	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_IF] = 3;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_WHILE] = 4;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_WHEN] = 5;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_SCAN] = 6;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_PRINT] = 7;
	rawTransitionTables[MTYPE_COMMAND][1][MTTYPE_EQUAL] = 8;
	rawTransitionTables[MTYPE_COMMAND][3][MTTYPE_LEFT_PARENTHESIS] = 11;
	rawTransitionTables[MTYPE_COMMAND][4][MTTYPE_LEFT_PARENTHESIS] = 35;
	rawTransitionTables[MTYPE_COMMAND][5][MTTYPE_LEFT_PARENTHESIS] = 23;
	rawTransitionTables[MTYPE_COMMAND][6][MTTYPE_LEFT_PARENTHESIS] = 12;
	rawTransitionTables[MTYPE_COMMAND][7][MTTYPE_LEFT_PARENTHESIS] = 9;
	rawSubmachineCallTables[MTYPE_COMMAND][8] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_COMMAND][8][MTYPE_VALUE] = 2;

	rawSubmachineCallTables[MTYPE_COMMAND][9] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_COMMAND][9][MTYPE_VALUE] = 10;

	rawTransitionTables[MTYPE_COMMAND][10][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawTransitionTables[MTYPE_COMMAND][10][MTTYPE_COMMA] = 9;
	rawSubmachineCallTables[MTYPE_COMMAND][11] = MTYPE_CONDITION;
	rawAfterCallTables[MTYPE_COMMAND][11][MTYPE_CONDITION] = 13;

	rawTransitionTables[MTYPE_COMMAND][12][MTTYPE_ID] = 14;
	rawTransitionTables[MTYPE_COMMAND][12][MTTYPE_ARRAY] = 14;
	rawTransitionTables[MTYPE_COMMAND][12][MTTYPE_MATRIX] = 14;
	rawTransitionTables[MTYPE_COMMAND][13][MTTYPE_RIGHT_PARENTHESIS] = 15;
	rawTransitionTables[MTYPE_COMMAND][14][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawTransitionTables[MTYPE_COMMAND][14][MTTYPE_COMMA] = 12;
	rawTransitionTables[MTYPE_COMMAND][15][MTTYPE_DO] = 16;
	rawSubmachineCallTables[MTYPE_COMMAND][16] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][16][MTYPE_COMMAND] = 17;

	rawTransitionTables[MTYPE_COMMAND][17][MTTYPE_SEMICOLON] = 18;
	rawSubmachineCallTables[MTYPE_COMMAND][18] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][18][MTYPE_COMMAND] = 17;

	rawTransitionTables[MTYPE_COMMAND][18][MTTYPE_ELSIF] = 3;
	rawTransitionTables[MTYPE_COMMAND][18][MTTYPE_ELSE] = 19;
	rawTransitionTables[MTYPE_COMMAND][18][MTTYPE_ENDIF] = 2;
	rawTransitionTables[MTYPE_COMMAND][19][MTTYPE_DO] = 20;
	rawSubmachineCallTables[MTYPE_COMMAND][20] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][20][MTYPE_COMMAND] = 21;

	rawTransitionTables[MTYPE_COMMAND][21][MTTYPE_SEMICOLON] = 22;
	rawSubmachineCallTables[MTYPE_COMMAND][22] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][22][MTYPE_COMMAND] = 21;

	rawTransitionTables[MTYPE_COMMAND][22][MTTYPE_ENDIF] = 2;
	rawSubmachineCallTables[MTYPE_COMMAND][23] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_COMMAND][23][MTYPE_VALUE] = 24;

	rawTransitionTables[MTYPE_COMMAND][24][MTTYPE_RIGHT_PARENTHESIS] = 25;
	rawTransitionTables[MTYPE_COMMAND][25][MTTYPE_IS] = 26;
	rawTransitionTables[MTYPE_COMMAND][26][MTTYPE_LEFT_PARENTHESIS] = 27;
	rawSubmachineCallTables[MTYPE_COMMAND][27] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_COMMAND][27][MTYPE_VALUE] = 28;

	rawTransitionTables[MTYPE_COMMAND][28][MTTYPE_RIGHT_PARENTHESIS] = 29;
	rawTransitionTables[MTYPE_COMMAND][29][MTTYPE_DO] = 30;
	rawSubmachineCallTables[MTYPE_COMMAND][30] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][30][MTYPE_COMMAND] = 31;

	rawTransitionTables[MTYPE_COMMAND][31][MTTYPE_SEMICOLON] = 32;
	rawSubmachineCallTables[MTYPE_COMMAND][32] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][32][MTYPE_COMMAND] = 31;

	rawTransitionTables[MTYPE_COMMAND][32][MTTYPE_CONTINUE] = 33;
	rawTransitionTables[MTYPE_COMMAND][33][MTTYPE_SEMICOLON] = 34;
	rawTransitionTables[MTYPE_COMMAND][34][MTTYPE_IS] = 26;
	rawTransitionTables[MTYPE_COMMAND][34][MTTYPE_ENDWHEN] = 2;
	rawSubmachineCallTables[MTYPE_COMMAND][35] = MTYPE_CONDITION;
	rawAfterCallTables[MTYPE_COMMAND][35][MTYPE_CONDITION] = 36;

	rawTransitionTables[MTYPE_COMMAND][36][MTTYPE_RIGHT_PARENTHESIS] = 37;
	rawTransitionTables[MTYPE_COMMAND][37][MTTYPE_DO] = 38;
	rawSubmachineCallTables[MTYPE_COMMAND][38] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][38][MTYPE_COMMAND] = 39;

	rawTransitionTables[MTYPE_COMMAND][39][MTTYPE_SEMICOLON] = 40;
	rawSubmachineCallTables[MTYPE_COMMAND][40] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][40][MTYPE_COMMAND] = 39;

	rawTransitionTables[MTYPE_COMMAND][40][MTTYPE_ENDWHILE] = 2;

	// MTYPE_DECLARATION ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_DECLARATION][0] = 3;
	rawFinalStatesTables[MTYPE_DECLARATION][1] = 15;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_DECLARATION][0][MTTYPE_TYPE] = 1;
	rawTransitionTables[MTYPE_DECLARATION][0][MTTYPE_FUNCTION] = 2;
	rawTransitionTables[MTYPE_DECLARATION][1][MTTYPE_ID] = 3;
	rawTransitionTables[MTYPE_DECLARATION][1][MTTYPE_ARRAY] = 3;
	rawTransitionTables[MTYPE_DECLARATION][1][MTTYPE_MATRIX] = 3;
	rawTransitionTables[MTYPE_DECLARATION][2][MTTYPE_TYPE] = 4;
	rawTransitionTables[MTYPE_DECLARATION][3][MTTYPE_COMMA] = 1;
	rawTransitionTables[MTYPE_DECLARATION][4][MTTYPE_ID] = 5;
	rawTransitionTables[MTYPE_DECLARATION][5][MTTYPE_LEFT_PARENTHESIS] = 6;
	rawTransitionTables[MTYPE_DECLARATION][6][MTTYPE_TYPE] = 7;
	rawTransitionTables[MTYPE_DECLARATION][6][MTTYPE_RIGHT_PARENTHESIS] = 8;
	rawTransitionTables[MTYPE_DECLARATION][7][MTTYPE_ID] = 14;
	rawTransitionTables[MTYPE_DECLARATION][8][MTTYPE_DO] = 9;
	rawSubmachineCallTables[MTYPE_DECLARATION][9] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_DECLARATION][9][MTYPE_COMMAND] = 10;

	rawTransitionTables[MTYPE_DECLARATION][10][MTTYPE_SEMICOLON] = 11;
	rawSubmachineCallTables[MTYPE_DECLARATION][11] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_DECLARATION][11][MTYPE_COMMAND] = 10;

	rawTransitionTables[MTYPE_DECLARATION][11][MTTYPE_RETURN] = 12;
	rawTransitionTables[MTYPE_DECLARATION][11][MTTYPE_ENDFUNCTION] = 13;
	rawTransitionTables[MTYPE_DECLARATION][12][MTTYPE_SEMICOLON] = 17;
	rawSubmachineCallTables[MTYPE_DECLARATION][12] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_DECLARATION][12][MTYPE_VALUE] = 18;

	rawTransitionTables[MTYPE_DECLARATION][13][MTTYPE_SEMICOLON] = 15;
	rawTransitionTables[MTYPE_DECLARATION][14][MTTYPE_COMMA] = 16;
	rawTransitionTables[MTYPE_DECLARATION][14][MTTYPE_RIGHT_PARENTHESIS] = 8;
	rawTransitionTables[MTYPE_DECLARATION][16][MTTYPE_TYPE] = 7;
	rawTransitionTables[MTYPE_DECLARATION][17][MTTYPE_ENDFUNCTION] = 13;
	rawTransitionTables[MTYPE_DECLARATION][18][MTTYPE_SEMICOLON] = 17;

	// MTYPE_CONDITION ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_CONDITION][0] = 1;
	rawFinalStatesTables[MTYPE_CONDITION][1] = 3;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_CONDITION][0][MTTYPE_BOOL] = 1;
	rawSubmachineCallTables[MTYPE_CONDITION][0] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_CONDITION][0][MTYPE_EXPRESSION] = 2;

	rawTransitionTables[MTYPE_CONDITION][0][MTTYPE_ID] = 3;
	rawTransitionTables[MTYPE_CONDITION][0][MTTYPE_ARRAY] = 1;
	rawTransitionTables[MTYPE_CONDITION][0][MTTYPE_MATRIX] = 1;
	rawTransitionTables[MTYPE_CONDITION][2][MTTYPE_COMPARATOR] = 4;
	rawTransitionTables[MTYPE_CONDITION][3][MTTYPE_LEFT_PARENTHESIS] = 5;
	rawTransitionTables[MTYPE_CONDITION][3][MTTYPE_DOT] = 6;
	rawSubmachineCallTables[MTYPE_CONDITION][4] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_CONDITION][4][MTYPE_EXPRESSION] = 1;

	rawSubmachineCallTables[MTYPE_CONDITION][5] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_CONDITION][5][MTYPE_VALUE] = 7;

	rawTransitionTables[MTYPE_CONDITION][5][MTTYPE_RIGHT_PARENTHESIS] = 1;
	rawTransitionTables[MTYPE_CONDITION][6][MTTYPE_ID] = 1;
	rawTransitionTables[MTYPE_CONDITION][7][MTTYPE_COMMA] = 8;
	rawTransitionTables[MTYPE_CONDITION][7][MTTYPE_RIGHT_PARENTHESIS] = 1;
	rawSubmachineCallTables[MTYPE_CONDITION][8] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_CONDITION][8][MTYPE_VALUE] = 7;


	// MTYPE_EXPRESSION ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_EXPRESSION][0] = 2;
	rawFinalStatesTables[MTYPE_EXPRESSION][1] = 3;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_LEFT_PARENTHESIS] = 1;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_INT] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_FLOAT] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_BOOL] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_ID] = 3;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_ARRAY] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_MATRIX] = 2;
	rawSubmachineCallTables[MTYPE_EXPRESSION][1] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_EXPRESSION][1][MTYPE_EXPRESSION] = 4;

	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_MULTIPLICATION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_DIVISION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_AND] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_PLUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_MINUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_OR] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_LEFT_PARENTHESIS] = 5;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_DOT] = 6;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_MULTIPLICATION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_DIVISION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_AND] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_PLUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_MINUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_OR] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][4][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][5][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawSubmachineCallTables[MTYPE_EXPRESSION][5] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_EXPRESSION][5][MTYPE_VALUE] = 7;

	rawTransitionTables[MTYPE_EXPRESSION][6][MTTYPE_ID] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][7][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][7][MTTYPE_COMMA] = 8;
	rawSubmachineCallTables[MTYPE_EXPRESSION][8] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_EXPRESSION][8][MTYPE_VALUE] = 7;


	// MTYPE_VALUE ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_VALUE][0] = 1;
	rawFinalStatesTables[MTYPE_VALUE][1] = 2;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_VALUE][0][MTTYPE_INT] = 1;
	rawTransitionTables[MTYPE_VALUE][0][MTTYPE_FLOAT] = 1;
	rawTransitionTables[MTYPE_VALUE][0][MTTYPE_STRING] = 1;
	rawTransitionTables[MTYPE_VALUE][0][MTTYPE_BOOL] = 1;
	rawTransitionTables[MTYPE_VALUE][0][MTTYPE_ID] = 2;
	rawTransitionTables[MTYPE_VALUE][0][MTTYPE_ARRAY] = 1;
	rawTransitionTables[MTYPE_VALUE][0][MTTYPE_MATRIX] = 1;
	rawTransitionTables[MTYPE_VALUE][2][MTTYPE_LEFT_PARENTHESIS] = 3;
	rawTransitionTables[MTYPE_VALUE][2][MTTYPE_DOT] = 4;
	rawSubmachineCallTables[MTYPE_VALUE][3] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_VALUE][3][MTYPE_VALUE] = 5;

	rawTransitionTables[MTYPE_VALUE][3][MTTYPE_RIGHT_PARENTHESIS] = 1;
	rawTransitionTables[MTYPE_VALUE][4][MTTYPE_ID] = 1;
	rawTransitionTables[MTYPE_VALUE][5][MTTYPE_COMMA] = 6;
	rawTransitionTables[MTYPE_VALUE][5][MTTYPE_RIGHT_PARENTHESIS] = 1;
	rawSubmachineCallTables[MTYPE_VALUE][6] = MTYPE_VALUE;
	rawAfterCallTables[MTYPE_VALUE][6][MTYPE_VALUE] = 5;

	Table allTransitionsTables[N_MACHINE_TYPES];
	Table allSubMachineCallTables[N_MACHINE_TYPES];
	Table allAfterCallTables[N_MACHINE_TYPES];
	Table allFinalStatesTables[N_MACHINE_TYPES];

	for (n = 0; n < N_MACHINE_TYPES; n++) {
		allTransitionsTables[n] = table_create(MAX_STATES, N_MACHINE_TOKEN_TYPES, rawTransitionTables[n]);
		allSubMachineCallTables[n] = table_create(MAX_STATES, 1, rawSubmachineCallTables[n]);
		allAfterCallTables[n] = table_create(MAX_STATES, N_MACHINE_TOKEN_TYPES, rawAfterCallTables[n]);
		allFinalStatesTables[n] = table_create(MAX_STATES, 1, rawFinalStatesTables[n]);
	}

	AutomataPE automataPE_create(initialMachine, N_MACHINE_TYPES, allTransitionsTables, allSubMachineCallTables, allAfterCallTables)
}
