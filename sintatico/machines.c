#include <string.h>
#include "machines.h"
#include "automataPE.h"
#include "../utils/token.h"
#include <string.h>

AutomataPE init_machines() {
	int initialMachine = MTYPE_PROGRAM;
	int n, i, j;
	int rawTransitionTables[N_MACHINE_TYPES][MAX_STATES][N_MACHINE_TOKEN_TYPES];
	int rawFinalStatesTables[N_MACHINE_TYPES][MAX_FINAL_STATES];
	int rawSubmachineCallTables[N_MACHINE_TYPES][MAX_STATES];
	int rawAfterCallTables[N_MACHINE_TYPES][MAX_STATES][N_MACHINE_TOKEN_TYPES];

	for (n = 0; n < N_MACHINE_TYPES; n++) {
		for(i = 0; i < MAX_FINAL_STATES; i++) {
			rawFinalStatesTables[n][i] = MINVALID_STATE;
			rawSubmachineCallTables[n][i] = MINVALID_STATE;
		}
		for(i=0; i < MAX_STATES; i++){
			for(j=0; j < N_MACHINE_TOKEN_TYPES; j++){
				rawTransitionTables[n][i][j] = MINVALID_STATE;
				rawAfterCallTables[n][i][j] = MINVALID_STATE;
			}
		}
	}
	
	
	// MTYPE_PROGRAM ||||||||||||||||||||||||||||||||||||||||
	allFinalStatesTables[MTYPE_PROGRAM][0] = 4;

	// TRANSITION TABLE --------------------------------------
	allTransitionTables[MTYPE_PROGRAM][0][MTTYPE_BEGIN] = 1;
	allSubmachineCallTables[MTYPE_PROGRAM][1] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_PROGRAM][1][MTYPE_COMMAND] = 2;

	allTransitionTables[MTYPE_PROGRAM][2][MTTYPE_SEMICOLON] = 3;
	allSubmachineCallTables[MTYPE_PROGRAM][3] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_PROGRAM][3][MTYPE_COMMAND] = 2;

	allTransitionTables[MTYPE_PROGRAM][3][MTTYPE_END] = 4;

	// MTYPE_COMMAND ||||||||||||||||||||||||||||||||||||||||
	allFinalStatesTables[MTYPE_COMMAND][0] = 2;

	// TRANSITION TABLE --------------------------------------
	allTransitionTables[MTYPE_COMMAND][0][MTTYPE_ID] = 1;
	allSubmachineCallTables[MTYPE_COMMAND][0] = MTYPE_DECLARATION;
	allAfterCallTables[MTYPE_COMMAND][0][MTYPE_DECLARATION] = 2;

	allTransitionTables[MTYPE_COMMAND][0][MTTYPE_IF] = 3;
	allTransitionTables[MTYPE_COMMAND][0][MTTYPE_WHILE] = 4;
	allTransitionTables[MTYPE_COMMAND][0][MTTYPE_WHEN] = 5;
	allTransitionTables[MTYPE_COMMAND][0][MTTYPE_SCAN] = 6;
	allTransitionTables[MTYPE_COMMAND][0][MTTYPE_PRINT] = 7;
	allTransitionTables[MTYPE_COMMAND][1][MTTYPE_LEFT_BRACKET] = 8;
	allTransitionTables[MTYPE_COMMAND][1][MTTYPE_EQUAL] = 9;
	allTransitionTables[MTYPE_COMMAND][3][MTTYPE_LEFT_PARENTHESIS] = 20;
	allTransitionTables[MTYPE_COMMAND][4][MTTYPE_LEFT_PARENTHESIS] = 46;
	allTransitionTables[MTYPE_COMMAND][5][MTTYPE_LEFT_PARENTHESIS] = 35;
	allTransitionTables[MTYPE_COMMAND][6][MTTYPE_LEFT_PARENTHESIS] = 16;
	allTransitionTables[MTYPE_COMMAND][7][MTTYPE_LEFT_PARENTHESIS] = 10;
	allTransitionTables[MTYPE_COMMAND][8][MTTYPE_INT] = 12;
	allSubmachineCallTables[MTYPE_COMMAND][9] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_COMMAND][9][MTYPE_VALUE] = 2;

	allSubmachineCallTables[MTYPE_COMMAND][10] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_COMMAND][10][MTYPE_VALUE] = 11;

	allTransitionTables[MTYPE_COMMAND][11][MTTYPE_RIGHT_PARENTHESIS] = 2;
	allTransitionTables[MTYPE_COMMAND][11][MTTYPE_COMMA] = 10;
	allTransitionTables[MTYPE_COMMAND][12][MTTYPE_RIGHT_BRACKET] = 13;
	allTransitionTables[MTYPE_COMMAND][13][MTTYPE_LEFT_BRACKET] = 14;
	allTransitionTables[MTYPE_COMMAND][13][MTTYPE_EQUAL] = 9;
	allTransitionTables[MTYPE_COMMAND][14][MTTYPE_INT] = 15;
	allTransitionTables[MTYPE_COMMAND][15][MTTYPE_RIGHT_BRACKET] = 17;
	allTransitionTables[MTYPE_COMMAND][16][MTTYPE_ID] = 18;
	allTransitionTables[MTYPE_COMMAND][17][MTTYPE_EQUAL] = 9;
	allTransitionTables[MTYPE_COMMAND][18][MTTYPE_LEFT_BRACKET] = 19;
	allTransitionTables[MTYPE_COMMAND][18][MTTYPE_RIGHT_PARENTHESIS] = 2;
	allTransitionTables[MTYPE_COMMAND][18][MTTYPE_COMMA] = 16;
	allTransitionTables[MTYPE_COMMAND][19][MTTYPE_INT] = 22;
	allSubmachineCallTables[MTYPE_COMMAND][20] = MTYPE_CONDITION;
	allAfterCallTables[MTYPE_COMMAND][20][MTYPE_CONDITION] = 21;

	allTransitionTables[MTYPE_COMMAND][21][MTTYPE_RIGHT_PARENTHESIS] = 23;
	allTransitionTables[MTYPE_COMMAND][22][MTTYPE_RIGHT_BRACKET] = 24;
	allTransitionTables[MTYPE_COMMAND][23][MTTYPE_DO] = 25;
	allTransitionTables[MTYPE_COMMAND][24][MTTYPE_LEFT_BRACKET] = 26;
	allTransitionTables[MTYPE_COMMAND][24][MTTYPE_RIGHT_PARENTHESIS] = 2;
	allTransitionTables[MTYPE_COMMAND][24][MTTYPE_COMMA] = 16;
	allSubmachineCallTables[MTYPE_COMMAND][25] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][25][MTYPE_COMMAND] = 27;

	allTransitionTables[MTYPE_COMMAND][26][MTTYPE_INT] = 28;
	allTransitionTables[MTYPE_COMMAND][27][MTTYPE_SEMICOLON] = 29;
	allTransitionTables[MTYPE_COMMAND][28][MTTYPE_RIGHT_BRACKET] = 30;
	allSubmachineCallTables[MTYPE_COMMAND][29] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][29][MTYPE_COMMAND] = 27;

	allTransitionTables[MTYPE_COMMAND][29][MTTYPE_ELSIF] = 3;
	allTransitionTables[MTYPE_COMMAND][29][MTTYPE_ELSE] = 31;
	allTransitionTables[MTYPE_COMMAND][29][MTTYPE_ENDIF] = 2;
	allTransitionTables[MTYPE_COMMAND][30][MTTYPE_RIGHT_PARENTHESIS] = 2;
	allTransitionTables[MTYPE_COMMAND][30][MTTYPE_COMMA] = 16;
	allTransitionTables[MTYPE_COMMAND][31][MTTYPE_DO] = 32;
	allSubmachineCallTables[MTYPE_COMMAND][32] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][32][MTYPE_COMMAND] = 33;

	allTransitionTables[MTYPE_COMMAND][33][MTTYPE_SEMICOLON] = 34;
	allSubmachineCallTables[MTYPE_COMMAND][34] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][34][MTYPE_COMMAND] = 33;

	allTransitionTables[MTYPE_COMMAND][34][MTTYPE_ENDIF] = 2;
	allSubmachineCallTables[MTYPE_COMMAND][35] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_COMMAND][35][MTYPE_VALUE] = 36;

	allTransitionTables[MTYPE_COMMAND][36][MTTYPE_RIGHT_PARENTHESIS] = 37;
	allTransitionTables[MTYPE_COMMAND][37][MTTYPE_IS] = 38;
	allTransitionTables[MTYPE_COMMAND][38][MTTYPE_LEFT_PARENTHESIS] = 39;
	allSubmachineCallTables[MTYPE_COMMAND][39] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_COMMAND][39][MTYPE_VALUE] = 40;

	allTransitionTables[MTYPE_COMMAND][40][MTTYPE_RIGHT_PARENTHESIS] = 41;
	allTransitionTables[MTYPE_COMMAND][41][MTTYPE_DO] = 42;
	allSubmachineCallTables[MTYPE_COMMAND][42] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][42][MTYPE_COMMAND] = 43;

	allTransitionTables[MTYPE_COMMAND][43][MTTYPE_SEMICOLON] = 44;
	allSubmachineCallTables[MTYPE_COMMAND][44] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][44][MTYPE_COMMAND] = 43;

	allTransitionTables[MTYPE_COMMAND][44][MTTYPE_CONTINUE] = 45;
	allTransitionTables[MTYPE_COMMAND][45][MTTYPE_SEMICOLON] = 47;
	allSubmachineCallTables[MTYPE_COMMAND][46] = MTYPE_CONDITION;
	allAfterCallTables[MTYPE_COMMAND][46][MTYPE_CONDITION] = 48;

	allTransitionTables[MTYPE_COMMAND][47][MTTYPE_IS] = 38;
	allTransitionTables[MTYPE_COMMAND][47][MTTYPE_ENDWHEN] = 2;
	allTransitionTables[MTYPE_COMMAND][48][MTTYPE_RIGHT_PARENTHESIS] = 49;
	allTransitionTables[MTYPE_COMMAND][49][MTTYPE_DO] = 50;
	allSubmachineCallTables[MTYPE_COMMAND][50] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][50][MTYPE_COMMAND] = 51;

	allTransitionTables[MTYPE_COMMAND][51][MTTYPE_SEMICOLON] = 52;
	allSubmachineCallTables[MTYPE_COMMAND][52] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_COMMAND][52][MTYPE_COMMAND] = 51;

	allTransitionTables[MTYPE_COMMAND][52][MTTYPE_ENDWHILE] = 2;

	// MTYPE_DECLARATION ||||||||||||||||||||||||||||||||||||||||
	allFinalStatesTables[MTYPE_DECLARATION][0] = 3;
	allFinalStatesTables[MTYPE_DECLARATION][1] = 12;
	allFinalStatesTables[MTYPE_DECLARATION][2] = 19;
	allFinalStatesTables[MTYPE_DECLARATION][3] = 20;

	// TRANSITION TABLE --------------------------------------
	allTransitionTables[MTYPE_DECLARATION][0][MTTYPE_TYPE] = 1;
	allTransitionTables[MTYPE_DECLARATION][0][MTTYPE_FUNCTION] = 2;
	allTransitionTables[MTYPE_DECLARATION][1][MTTYPE_ID] = 3;
	allTransitionTables[MTYPE_DECLARATION][2][MTTYPE_TYPE] = 4;
	allTransitionTables[MTYPE_DECLARATION][3][MTTYPE_LEFT_BRACKET] = 5;
	allTransitionTables[MTYPE_DECLARATION][3][MTTYPE_COMMA] = 1;
	allTransitionTables[MTYPE_DECLARATION][4][MTTYPE_ID] = 6;
	allTransitionTables[MTYPE_DECLARATION][5][MTTYPE_INT] = 10;
	allTransitionTables[MTYPE_DECLARATION][6][MTTYPE_LEFT_PARENTHESIS] = 7;
	allTransitionTables[MTYPE_DECLARATION][7][MTTYPE_TYPE] = 8;
	allTransitionTables[MTYPE_DECLARATION][7][MTTYPE_RIGHT_PARENTHESIS] = 9;
	allTransitionTables[MTYPE_DECLARATION][8][MTTYPE_ID] = 23;
	allTransitionTables[MTYPE_DECLARATION][9][MTTYPE_DO] = 11;
	allTransitionTables[MTYPE_DECLARATION][10][MTTYPE_RIGHT_BRACKET] = 12;
	allSubmachineCallTables[MTYPE_DECLARATION][11] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_DECLARATION][11][MTYPE_COMMAND] = 13;

	allTransitionTables[MTYPE_DECLARATION][12][MTTYPE_LEFT_BRACKET] = 14;
	allTransitionTables[MTYPE_DECLARATION][12][MTTYPE_COMMA] = 1;
	allTransitionTables[MTYPE_DECLARATION][13][MTTYPE_SEMICOLON] = 15;
	allTransitionTables[MTYPE_DECLARATION][14][MTTYPE_INT] = 16;
	allSubmachineCallTables[MTYPE_DECLARATION][15] = MTYPE_COMMAND;
	allAfterCallTables[MTYPE_DECLARATION][15][MTYPE_COMMAND] = 13;

	allTransitionTables[MTYPE_DECLARATION][15][MTTYPE_RETURN] = 17;
	allTransitionTables[MTYPE_DECLARATION][15][MTTYPE_ENDFUNCTION] = 18;
	allTransitionTables[MTYPE_DECLARATION][16][MTTYPE_RIGHT_BRACKET] = 19;
	allTransitionTables[MTYPE_DECLARATION][17][MTTYPE_SEMICOLON] = 21;
	allSubmachineCallTables[MTYPE_DECLARATION][17] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_DECLARATION][17][MTYPE_VALUE] = 22;

	allTransitionTables[MTYPE_DECLARATION][18][MTTYPE_SEMICOLON] = 20;
	allTransitionTables[MTYPE_DECLARATION][19][MTTYPE_COMMA] = 1;
	allTransitionTables[MTYPE_DECLARATION][21][MTTYPE_ENDFUNCTION] = 18;
	allTransitionTables[MTYPE_DECLARATION][22][MTTYPE_SEMICOLON] = 21;
	allTransitionTables[MTYPE_DECLARATION][23][MTTYPE_COMMA] = 24;
	allTransitionTables[MTYPE_DECLARATION][23][MTTYPE_RIGHT_PARENTHESIS] = 9;
	allTransitionTables[MTYPE_DECLARATION][24][MTTYPE_TYPE] = 8;

	// MTYPE_CONDITION ||||||||||||||||||||||||||||||||||||||||
	allFinalStatesTables[MTYPE_CONDITION][0] = 1;
	allFinalStatesTables[MTYPE_CONDITION][1] = 2;
	allFinalStatesTables[MTYPE_CONDITION][2] = 3;
	allFinalStatesTables[MTYPE_CONDITION][3] = 10;

	// TRANSITION TABLE --------------------------------------
	allTransitionTables[MTYPE_CONDITION][0][MTTYPE_BOOL] = 1;
	allSubmachineCallTables[MTYPE_CONDITION][0] = MTYPE_EXPRESSION;
	allAfterCallTables[MTYPE_CONDITION][0][MTYPE_EXPRESSION] = 2;

	allTransitionTables[MTYPE_CONDITION][0][MTTYPE_ID] = 3;
	allTransitionTables[MTYPE_CONDITION][2][MTTYPE_COMPARATOR] = 7;
	allTransitionTables[MTYPE_CONDITION][3][MTTYPE_LEFT_BRACKET] = 4;
	allTransitionTables[MTYPE_CONDITION][3][MTTYPE_LEFT_PARENTHESIS] = 5;
	allTransitionTables[MTYPE_CONDITION][3][MTTYPE_DOT] = 6;
	allTransitionTables[MTYPE_CONDITION][4][MTTYPE_INT] = 9;
	allSubmachineCallTables[MTYPE_CONDITION][5] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_CONDITION][5][MTYPE_VALUE] = 8;

	allTransitionTables[MTYPE_CONDITION][5][MTTYPE_RIGHT_PARENTHESIS] = 1;
	allTransitionTables[MTYPE_CONDITION][6][MTTYPE_ID] = 1;
	allSubmachineCallTables[MTYPE_CONDITION][7] = MTYPE_EXPRESSION;
	allAfterCallTables[MTYPE_CONDITION][7][MTYPE_EXPRESSION] = 1;

	allTransitionTables[MTYPE_CONDITION][8][MTTYPE_COMMA] = 11;
	allTransitionTables[MTYPE_CONDITION][8][MTTYPE_RIGHT_PARENTHESIS] = 1;
	allTransitionTables[MTYPE_CONDITION][9][MTTYPE_RIGHT_BRACKET] = 10;
	allTransitionTables[MTYPE_CONDITION][10][MTTYPE_LEFT_BRACKET] = 12;
	allSubmachineCallTables[MTYPE_CONDITION][11] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_CONDITION][11][MTYPE_VALUE] = 8;

	allTransitionTables[MTYPE_CONDITION][12][MTTYPE_INT] = 13;
	allTransitionTables[MTYPE_CONDITION][13][MTTYPE_RIGHT_BRACKET] = 1;

	// MTYPE_EXPRESSION ||||||||||||||||||||||||||||||||||||||||
	allFinalStatesTables[MTYPE_EXPRESSION][0] = 2;
	allFinalStatesTables[MTYPE_EXPRESSION][1] = 3;
	allFinalStatesTables[MTYPE_EXPRESSION][2] = 11;

	// TRANSITION TABLE --------------------------------------
	allTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_LEFT_PARENTHESIS] = 1;
	allSubmachineCallTables[MTYPE_EXPRESSION][0] = MTYPE_EXPRESSION;
	allAfterCallTables[MTYPE_EXPRESSION][0][MTYPE_EXPRESSION] = 2;

	allTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_INT] = 2;
	allTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_FLOAT] = 2;
	allTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_BOOL] = 2;
	allTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_ID] = 3;
	allSubmachineCallTables[MTYPE_EXPRESSION][1] = MTYPE_EXPRESSION;
	allAfterCallTables[MTYPE_EXPRESSION][1][MTYPE_EXPRESSION] = 4;

	allTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_MULTIPLICATION] = 0;
	allTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_DIVISION] = 0;
	allTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_AND] = 0;
	allTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_PLUS] = 0;
	allTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_MINUS] = 0;
	allTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_OR] = 0;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_LEFT_PARENTHESIS] = 5;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_LEFT_BRACKET] = 6;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_DOT] = 7;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_MULTIPLICATION] = 0;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_DIVISION] = 0;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_AND] = 0;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_PLUS] = 0;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_MINUS] = 0;
	allTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_OR] = 0;
	allTransitionTables[MTYPE_EXPRESSION][4][MTTYPE_RIGHT_PARENTHESIS] = 2;
	allTransitionTables[MTYPE_EXPRESSION][5][MTTYPE_RIGHT_PARENTHESIS] = 2;
	allSubmachineCallTables[MTYPE_EXPRESSION][5] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_EXPRESSION][5][MTYPE_VALUE] = 8;

	allTransitionTables[MTYPE_EXPRESSION][6][MTTYPE_INT] = 9;
	allTransitionTables[MTYPE_EXPRESSION][7][MTTYPE_ID] = 2;
	allTransitionTables[MTYPE_EXPRESSION][8][MTTYPE_RIGHT_PARENTHESIS] = 2;
	allTransitionTables[MTYPE_EXPRESSION][8][MTTYPE_COMMA] = 10;
	allTransitionTables[MTYPE_EXPRESSION][9][MTTYPE_RIGHT_BRACKET] = 11;
	allSubmachineCallTables[MTYPE_EXPRESSION][10] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_EXPRESSION][10][MTYPE_VALUE] = 8;

	allTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_LEFT_BRACKET] = 12;
	allTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_MULTIPLICATION] = 0;
	allTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_DIVISION] = 0;
	allTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_AND] = 0;
	allTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_PLUS] = 0;
	allTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_MINUS] = 0;
	allTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_OR] = 0;
	allTransitionTables[MTYPE_EXPRESSION][12][MTTYPE_INT] = 13;
	allTransitionTables[MTYPE_EXPRESSION][13][MTTYPE_RIGHT_BRACKET] = 2;

	// MTYPE_VALUE ||||||||||||||||||||||||||||||||||||||||
	allFinalStatesTables[MTYPE_VALUE][0] = 1;
	allFinalStatesTables[MTYPE_VALUE][1] = 2;
	allFinalStatesTables[MTYPE_VALUE][2] = 8;

	// TRANSITION TABLE --------------------------------------
	allTransitionTables[MTYPE_VALUE][0][MTTYPE_INT] = 1;
	allTransitionTables[MTYPE_VALUE][0][MTTYPE_FLOAT] = 1;
	allTransitionTables[MTYPE_VALUE][0][MTTYPE_STRING] = 1;
	allTransitionTables[MTYPE_VALUE][0][MTTYPE_BOOL] = 1;
	allTransitionTables[MTYPE_VALUE][0][MTTYPE_ID] = 2;
	allSubmachineCallTables[MTYPE_VALUE][0] = MTYPE_EXPRESSION;
	allAfterCallTables[MTYPE_VALUE][0][MTYPE_EXPRESSION] = 1;

	allTransitionTables[MTYPE_VALUE][2][MTTYPE_LEFT_BRACKET] = 3;
	allTransitionTables[MTYPE_VALUE][2][MTTYPE_LEFT_PARENTHESIS] = 4;
	allTransitionTables[MTYPE_VALUE][2][MTTYPE_DOT] = 5;
	allTransitionTables[MTYPE_VALUE][3][MTTYPE_INT] = 6;
	allSubmachineCallTables[MTYPE_VALUE][4] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_VALUE][4][MTYPE_VALUE] = 7;

	allTransitionTables[MTYPE_VALUE][4][MTTYPE_RIGHT_PARENTHESIS] = 1;
	allTransitionTables[MTYPE_VALUE][5][MTTYPE_ID] = 1;
	allTransitionTables[MTYPE_VALUE][6][MTTYPE_RIGHT_BRACKET] = 8;
	allTransitionTables[MTYPE_VALUE][7][MTTYPE_COMMA] = 10;
	allTransitionTables[MTYPE_VALUE][7][MTTYPE_RIGHT_PARENTHESIS] = 1;
	allTransitionTables[MTYPE_VALUE][8][MTTYPE_LEFT_BRACKET] = 9;
	allTransitionTables[MTYPE_VALUE][9][MTTYPE_INT] = 11;
	allSubmachineCallTables[MTYPE_VALUE][10] = MTYPE_VALUE;
	allAfterCallTables[MTYPE_VALUE][10][MTYPE_VALUE] = 7;

	allTransitionTables[MTYPE_VALUE][11][MTTYPE_RIGHT_BRACKET] = 1;

	Table allTransitionsTables[N_MACHINE_TYPES];
	Table allSubMachineCallTables[N_MACHINE_TYPES];
	Table allAfterCallTables[N_MACHINE_TYPES];
	Table allFinalStatesTables[N_MACHINE_TYPES];

	for (n = 0; n < N_MACHINE_TYPES; n++) {
		allTransitionsTables[n] = table_create(MAX_STATES, N_MACHINE_TOKEN_TYPES, rawTransitionTables[n]);
		allSubMachineCallTables[n] = table_create(MAX_STATES, 1, &rawSubmachineCallTables[n]);
		allAfterCallTables[n] = table_create(MAX_STATES, N_MACHINE_TOKEN_TYPES, rawAfterCallTables[n]);
		allFinalStatesTables[n] = table_create(MAX_STATES, 1, &rawFinalStatesTables[n]);
	}

	return automataPE_create(initialMachine, N_MACHINE_TYPES, allTransitionsTables, allSubMachineCallTables, allAfterCallTables, allFinalStatesTables);
}

int convert_token_to_machine_type(Token *token) {
	switch (token->type) {
		case TT_RESERVED:
			if(strcmp(token->string, "begin") == 0) return MTTYPE_BEGIN; 		
			if(strcmp(token->string, "end") == 0) return MTTYPE_END; 			
			if(strcmp(token->string, "do") == 0) return MTTYPE_DO; 			
			if(strcmp(token->string, "if") == 0) return MTTYPE_IF; 			
			if(strcmp(token->string, "elsif") == 0) return MTTYPE_ELSIF; 		
			if(strcmp(token->string, "endif") == 0) return MTTYPE_ENDIF; 		
			if(strcmp(token->string, "else") == 0) return MTTYPE_ELSE; 		
			if(strcmp(token->string, "while") == 0) return MTTYPE_WHILE; 		
			if(strcmp(token->string, "endwhile") == 0) return MTTYPE_ENDWHILE; 	
			if(strcmp(token->string, "when") == 0) return MTTYPE_WHEN; 		
			if(strcmp(token->string, "endwhen") == 0) return MTTYPE_ENDWHEN; 		
			if(strcmp(token->string, "is") == 0) return MTTYPE_IS; 			
			if(strcmp(token->string, "continue") == 0) return MTTYPE_CONTINUE; 	
			if(strcmp(token->string, "function") == 0) return MTTYPE_FUNCTION; 	
			if(strcmp(token->string, "return") == 0) return MTTYPE_RETURN; 		
			if(strcmp(token->string, "endfunction") == 0) return MTTYPE_ENDFUNCTION; 	
			if(strcmp(token->string, "scan") == 0) return MTTYPE_SCAN; 		
			if(strcmp(token->string, "print") == 0) return MTTYPE_PRINT; 
			if(strcmp(token->string, "string") == 0) return MTTYPE_TYPE; 
			if(strcmp(token->string, "bool") == 0) return MTTYPE_TYPE; 
			if(strcmp(token->string, "int") == 0) return MTTYPE_TYPE; 
			if(strcmp(token->string, "float") == 0) return MTTYPE_TYPE; 
			if(strcmp(token->string, "and") == 0) return MTTYPE_AND; 			
			if(strcmp(token->string, "or") == 0) return MTTYPE_OR; 		
			if(strcmp(token->string, "true") == 0) return MTTYPE_BOOL; 		
			if(strcmp(token->string, "false") == 0) return MTTYPE_BOOL;		
		case TT_STRING:
			return MTTYPE_STRING;
		case TT_ARITH_SYMBOL:
			if(strcmp(token->string, "+") == 0) return MTTYPE_PLUS; 		
			if(strcmp(token->string, "-") == 0) return MTTYPE_MINUS; 		
			if(strcmp(token->string, "*") == 0) return MTTYPE_MULTIPLICATION; 
			if(strcmp(token->string, "/") == 0) return MTTYPE_DIVISION; 	
		case TT_INT:
			return MTTYPE_INT;
		case TT_COMPARATOR:
			return MTTYPE_COMPARATOR;
		case TT_IDENTIFIER:
			return MTTYPE_ID;
		case TT_SEPARATOR:
			if(strcmp(token->string, ",") == 0) return MTTYPE_COMMA; 		
			if(strcmp(token->string, ".") == 0) return MTTYPE_DOT; 			
		case TT_END_OF_COMMAND:
			if(strcmp(token->string, ";") == 0) return MTTYPE_SEMICOLON; 	
		case TT_UNKNOWN:
			return MTTYPE_INVALID;
		case TT_ASSIGNMENT:
			return MTTYPE_EQUAL;
		case TT_FLOAT:
			return MTTYPE_FLOAT;
		case TT_ARRAY:
			return MTTYPE_ARRAY;
		case TT_MATRIX:
			return MTTYPE_MATRIX;
		case TT_R_SQ_BRACKET:
			if(strcmp(token->string, "]") == 0) return MTTYPE_RIGHT_BRACKET; 
		case TT_L_SQ_BRACKET:
			if(strcmp(token->string, "[") == 0) return MTTYPE_LEFT_BRACKET; 
		case TT_R_PARENTHESIS:
			if(strcmp(token->string, ")") == 0) return MTTYPE_RIGHT_PARENTHESIS;
		case TT_L_PARENTHESIS:
			if(strcmp(token->string, "(") == 0) return MTTYPE_LEFT_PARENTHESIS;
		default:
			break;
	}
	return MTTYPE_INVALID;
}

char *machineid_to_name(int machineId){
	switch(machineId){
		case MTYPE_INVALID:
			return "INVALID";
		case MTYPE_PROGRAM:
			return "PROGRAM";
		case MTYPE_COMMAND:
			return "COMMAND";
		case MTYPE_DECLARATION:
			return "DECLARATION";
		case MTYPE_CONDITION:
			return "CONDITION";
		case MTYPE_EXPRESSION:
			return "EXPRESSION";
		case MTYPE_VALUE:
			return "VALUE";
	}
	return "";
}