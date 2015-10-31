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
		}
		for(i=0; i < MAX_STATES; i++){
			rawSubmachineCallTables[n][i] = MTYPE_INVALID;
			for(j=0; j < N_MACHINE_TOKEN_TYPES; j++){
				rawTransitionTables[n][i][j] = MINVALID_STATE;
				rawAfterCallTables[n][i][j] = MINVALID_STATE;
			}
		}
	}
	
	
	
	// MTYPE_PROGRAM ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_PROGRAM][0] = 3;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_PROGRAM][0][MTTYPE_BEGIN] = 1;
	rawSubmachineCallTables[MTYPE_PROGRAM][1] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_PROGRAM][1][MTYPE_COMMAND] = 2;

	rawSubmachineCallTables[MTYPE_PROGRAM][2] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_PROGRAM][2][MTYPE_COMMAND] = 2;

	rawTransitionTables[MTYPE_PROGRAM][2][MTTYPE_END] = 3;

	// MTYPE_COMMAND ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_COMMAND][0] = 2;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_ID] = 1;
	rawSubmachineCallTables[MTYPE_COMMAND][0] = MTYPE_DECLARATION;
	rawAfterCallTables[MTYPE_COMMAND][0][MTYPE_DECLARATION] = 2;

	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_IF] = 3;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_WHILE] = 4;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_WHEN] = 5;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_SCAN] = 6;
	rawTransitionTables[MTYPE_COMMAND][0][MTTYPE_PRINT] = 7;
	rawTransitionTables[MTYPE_COMMAND][1][MTTYPE_LEFT_BRACKET] = 8;
	rawTransitionTables[MTYPE_COMMAND][1][MTTYPE_EQUAL] = 9;
	rawTransitionTables[MTYPE_COMMAND][3][MTTYPE_LEFT_PARENTHESIS] = 23;
	rawTransitionTables[MTYPE_COMMAND][4][MTTYPE_LEFT_PARENTHESIS] = 39;
	rawTransitionTables[MTYPE_COMMAND][5][MTTYPE_LEFT_PARENTHESIS] = 36;
	rawTransitionTables[MTYPE_COMMAND][6][MTTYPE_LEFT_PARENTHESIS] = 20;
	rawTransitionTables[MTYPE_COMMAND][7][MTTYPE_LEFT_PARENTHESIS] = 10;
	rawTransitionTables[MTYPE_COMMAND][8][MTTYPE_INT] = 14;
	rawSubmachineCallTables[MTYPE_COMMAND][9] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_COMMAND][9][MTYPE_EXPRESSION] = 11;

	rawSubmachineCallTables[MTYPE_COMMAND][10] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_COMMAND][10][MTYPE_EXPRESSION] = 12;

	rawTransitionTables[MTYPE_COMMAND][10][MTTYPE_STRING] = 13;
	rawTransitionTables[MTYPE_COMMAND][11][MTTYPE_SEMICOLON] = 2;
	rawTransitionTables[MTYPE_COMMAND][12][MTTYPE_RIGHT_PARENTHESIS] = 11;
	rawTransitionTables[MTYPE_COMMAND][12][MTTYPE_COMMA] = 16;
	rawTransitionTables[MTYPE_COMMAND][13][MTTYPE_RIGHT_PARENTHESIS] = 11;
	rawTransitionTables[MTYPE_COMMAND][14][MTTYPE_RIGHT_BRACKET] = 15;
	rawTransitionTables[MTYPE_COMMAND][15][MTTYPE_LEFT_BRACKET] = 17;
	rawTransitionTables[MTYPE_COMMAND][15][MTTYPE_EQUAL] = 9;
	rawSubmachineCallTables[MTYPE_COMMAND][16] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_COMMAND][16][MTYPE_EXPRESSION] = 12;

	rawTransitionTables[MTYPE_COMMAND][17][MTTYPE_INT] = 18;
	rawTransitionTables[MTYPE_COMMAND][18][MTTYPE_RIGHT_BRACKET] = 19;
	rawTransitionTables[MTYPE_COMMAND][19][MTTYPE_EQUAL] = 9;
	rawTransitionTables[MTYPE_COMMAND][20][MTTYPE_ID] = 21;
	rawTransitionTables[MTYPE_COMMAND][21][MTTYPE_LEFT_BRACKET] = 22;
	rawTransitionTables[MTYPE_COMMAND][21][MTTYPE_RIGHT_PARENTHESIS] = 11;
	rawTransitionTables[MTYPE_COMMAND][21][MTTYPE_COMMA] = 20;
	rawTransitionTables[MTYPE_COMMAND][22][MTTYPE_INT] = 26;
	rawSubmachineCallTables[MTYPE_COMMAND][23] = MTYPE_CONDITION;
	rawAfterCallTables[MTYPE_COMMAND][23][MTYPE_CONDITION] = 24;

	rawTransitionTables[MTYPE_COMMAND][24][MTTYPE_RIGHT_PARENTHESIS] = 25;
	rawTransitionTables[MTYPE_COMMAND][25][MTTYPE_DO] = 27;
	rawTransitionTables[MTYPE_COMMAND][26][MTTYPE_RIGHT_BRACKET] = 28;
	rawSubmachineCallTables[MTYPE_COMMAND][27] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][27][MTYPE_COMMAND] = 29;

	rawTransitionTables[MTYPE_COMMAND][28][MTTYPE_LEFT_BRACKET] = 30;
	rawTransitionTables[MTYPE_COMMAND][28][MTTYPE_RIGHT_PARENTHESIS] = 11;
	rawTransitionTables[MTYPE_COMMAND][28][MTTYPE_COMMA] = 20;
	rawSubmachineCallTables[MTYPE_COMMAND][29] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][29][MTYPE_COMMAND] = 29;

	rawTransitionTables[MTYPE_COMMAND][29][MTTYPE_ELSIF] = 3;
	rawTransitionTables[MTYPE_COMMAND][29][MTTYPE_ELSE] = 31;
	rawTransitionTables[MTYPE_COMMAND][29][MTTYPE_ENDIF] = 2;
	rawTransitionTables[MTYPE_COMMAND][30][MTTYPE_INT] = 32;
	rawTransitionTables[MTYPE_COMMAND][31][MTTYPE_DO] = 34;
	rawTransitionTables[MTYPE_COMMAND][32][MTTYPE_RIGHT_BRACKET] = 33;
	rawTransitionTables[MTYPE_COMMAND][33][MTTYPE_RIGHT_PARENTHESIS] = 11;
	rawTransitionTables[MTYPE_COMMAND][33][MTTYPE_COMMA] = 20;
	rawSubmachineCallTables[MTYPE_COMMAND][34] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][34][MTYPE_COMMAND] = 35;

	rawSubmachineCallTables[MTYPE_COMMAND][35] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][35][MTYPE_COMMAND] = 35;

	rawTransitionTables[MTYPE_COMMAND][35][MTTYPE_ENDIF] = 2;
	rawSubmachineCallTables[MTYPE_COMMAND][36] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_COMMAND][36][MTYPE_EXPRESSION] = 37;

	rawTransitionTables[MTYPE_COMMAND][37][MTTYPE_RIGHT_PARENTHESIS] = 38;
	rawTransitionTables[MTYPE_COMMAND][38][MTTYPE_IS] = 40;
	rawSubmachineCallTables[MTYPE_COMMAND][39] = MTYPE_CONDITION;
	rawAfterCallTables[MTYPE_COMMAND][39][MTYPE_CONDITION] = 41;

	rawTransitionTables[MTYPE_COMMAND][40][MTTYPE_LEFT_PARENTHESIS] = 42;
	rawTransitionTables[MTYPE_COMMAND][41][MTTYPE_RIGHT_PARENTHESIS] = 43;
	rawSubmachineCallTables[MTYPE_COMMAND][42] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_COMMAND][42][MTYPE_EXPRESSION] = 44;

	rawTransitionTables[MTYPE_COMMAND][43][MTTYPE_DO] = 45;
	rawTransitionTables[MTYPE_COMMAND][44][MTTYPE_RIGHT_PARENTHESIS] = 46;
	rawSubmachineCallTables[MTYPE_COMMAND][45] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][45][MTYPE_COMMAND] = 47;

	rawTransitionTables[MTYPE_COMMAND][46][MTTYPE_DO] = 48;
	rawSubmachineCallTables[MTYPE_COMMAND][47] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][47][MTYPE_COMMAND] = 47;

	rawTransitionTables[MTYPE_COMMAND][47][MTTYPE_ENDWHILE] = 2;
	rawSubmachineCallTables[MTYPE_COMMAND][48] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][48][MTYPE_COMMAND] = 49;

	rawSubmachineCallTables[MTYPE_COMMAND][49] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_COMMAND][49][MTYPE_COMMAND] = 49;

	rawTransitionTables[MTYPE_COMMAND][49][MTTYPE_CONTINUE] = 50;
	rawTransitionTables[MTYPE_COMMAND][50][MTTYPE_SEMICOLON] = 51;
	rawTransitionTables[MTYPE_COMMAND][51][MTTYPE_IS] = 40;
	rawTransitionTables[MTYPE_COMMAND][51][MTTYPE_ENDWHEN] = 2;

	// MTYPE_DECLARATION ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_DECLARATION][0] = 6;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_DECLARATION][0][MTTYPE_TYPE] = 1;
	rawTransitionTables[MTYPE_DECLARATION][0][MTTYPE_FUNCTION] = 2;
	rawTransitionTables[MTYPE_DECLARATION][1][MTTYPE_ID] = 3;
	rawTransitionTables[MTYPE_DECLARATION][2][MTTYPE_TYPE] = 4;
	rawTransitionTables[MTYPE_DECLARATION][3][MTTYPE_LEFT_BRACKET] = 5;
	rawTransitionTables[MTYPE_DECLARATION][3][MTTYPE_COMMA] = 1;
	rawTransitionTables[MTYPE_DECLARATION][3][MTTYPE_SEMICOLON] = 6;
	rawTransitionTables[MTYPE_DECLARATION][4][MTTYPE_ID] = 7;
	rawTransitionTables[MTYPE_DECLARATION][5][MTTYPE_INT] = 12;
	rawTransitionTables[MTYPE_DECLARATION][7][MTTYPE_LEFT_PARENTHESIS] = 8;
	rawTransitionTables[MTYPE_DECLARATION][8][MTTYPE_TYPE] = 9;
	rawTransitionTables[MTYPE_DECLARATION][8][MTTYPE_RIGHT_PARENTHESIS] = 10;
	rawTransitionTables[MTYPE_DECLARATION][9][MTTYPE_ID] = 20;
	rawTransitionTables[MTYPE_DECLARATION][10][MTTYPE_DO] = 11;
	rawSubmachineCallTables[MTYPE_DECLARATION][11] = MTYPE_COMMAND;
	rawAfterCallTables[MTYPE_DECLARATION][11][MTYPE_COMMAND] = 11;

	rawTransitionTables[MTYPE_DECLARATION][11][MTTYPE_RETURN] = 13;
	rawTransitionTables[MTYPE_DECLARATION][11][MTTYPE_ENDFUNCTION] = 6;
	rawTransitionTables[MTYPE_DECLARATION][12][MTTYPE_RIGHT_BRACKET] = 14;
	rawTransitionTables[MTYPE_DECLARATION][13][MTTYPE_SEMICOLON] = 16;
	rawSubmachineCallTables[MTYPE_DECLARATION][13] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_DECLARATION][13][MTYPE_EXPRESSION] = 17;

	rawTransitionTables[MTYPE_DECLARATION][14][MTTYPE_LEFT_BRACKET] = 15;
	rawTransitionTables[MTYPE_DECLARATION][14][MTTYPE_COMMA] = 1;
	rawTransitionTables[MTYPE_DECLARATION][14][MTTYPE_SEMICOLON] = 6;
	rawTransitionTables[MTYPE_DECLARATION][15][MTTYPE_INT] = 18;
	rawTransitionTables[MTYPE_DECLARATION][16][MTTYPE_ENDFUNCTION] = 6;
	rawTransitionTables[MTYPE_DECLARATION][17][MTTYPE_SEMICOLON] = 16;
	rawTransitionTables[MTYPE_DECLARATION][18][MTTYPE_RIGHT_BRACKET] = 19;
	rawTransitionTables[MTYPE_DECLARATION][19][MTTYPE_COMMA] = 1;
	rawTransitionTables[MTYPE_DECLARATION][19][MTTYPE_SEMICOLON] = 6;
	rawTransitionTables[MTYPE_DECLARATION][20][MTTYPE_COMMA] = 21;
	rawTransitionTables[MTYPE_DECLARATION][20][MTTYPE_RIGHT_PARENTHESIS] = 10;
	rawTransitionTables[MTYPE_DECLARATION][21][MTTYPE_TYPE] = 9;

	// MTYPE_CONDITION ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_CONDITION][0] = 1;
	rawFinalStatesTables[MTYPE_CONDITION][1] = 3;

	// TRANSITION TABLE --------------------------------------
	rawSubmachineCallTables[MTYPE_CONDITION][0] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_CONDITION][0][MTYPE_EXPRESSION] = 1;

	rawTransitionTables[MTYPE_CONDITION][1][MTTYPE_COMPARATOR] = 2;
	rawSubmachineCallTables[MTYPE_CONDITION][2] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_CONDITION][2][MTYPE_EXPRESSION] = 3;


	// MTYPE_EXPRESSION ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_EXPRESSION][0] = 2;
	rawFinalStatesTables[MTYPE_EXPRESSION][1] = 3;
	rawFinalStatesTables[MTYPE_EXPRESSION][2] = 11;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_LEFT_PARENTHESIS] = 1;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_INT] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_FLOAT] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_BOOL] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][0][MTTYPE_ID] = 3;
	rawSubmachineCallTables[MTYPE_EXPRESSION][1] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_EXPRESSION][1][MTYPE_EXPRESSION] = 4;

	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_MULTIPLICATION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_DIVISION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_AND] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_PLUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_MINUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][2][MTTYPE_OR] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_LEFT_PARENTHESIS] = 5;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_LEFT_BRACKET] = 6;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_DOT] = 7;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_MULTIPLICATION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_DIVISION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_AND] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_PLUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_MINUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][3][MTTYPE_OR] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][4][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawSubmachineCallTables[MTYPE_EXPRESSION][5] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_EXPRESSION][5][MTYPE_EXPRESSION] = 8;

	rawTransitionTables[MTYPE_EXPRESSION][5][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][6][MTTYPE_INT] = 9;
	rawTransitionTables[MTYPE_EXPRESSION][7][MTTYPE_ID] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][8][MTTYPE_RIGHT_PARENTHESIS] = 2;
	rawTransitionTables[MTYPE_EXPRESSION][8][MTTYPE_COMMA] = 10;
	rawTransitionTables[MTYPE_EXPRESSION][9][MTTYPE_RIGHT_BRACKET] = 11;
	rawSubmachineCallTables[MTYPE_EXPRESSION][10] = MTYPE_EXPRESSION;
	rawAfterCallTables[MTYPE_EXPRESSION][10][MTYPE_EXPRESSION] = 8;

	rawTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_LEFT_BRACKET] = 12;
	rawTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_MULTIPLICATION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_DIVISION] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_AND] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_PLUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_MINUS] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][11][MTTYPE_OR] = 0;
	rawTransitionTables[MTYPE_EXPRESSION][12][MTTYPE_INT] = 13;
	rawTransitionTables[MTYPE_EXPRESSION][13][MTTYPE_RIGHT_BRACKET] = 2;

	
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