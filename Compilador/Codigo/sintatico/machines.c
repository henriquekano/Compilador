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
	rawFinalStatesTables[MTYPE_PROGRAM][0] = 1;

	// TRANSITION TABLE --------------------------------------
	rawSubmachineCallTables[MTYPE_PROGRAM][0] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_PROGRAM][0][MTYPE_EXPR] = 1;

	rawSubmachineCallTables[MTYPE_PROGRAM][1] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_PROGRAM][1][MTYPE_EXPR] = 1;


	// MTYPE_EXPR ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_EXPR][0] = 1;
	rawFinalStatesTables[MTYPE_EXPR][1] = 2;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_i] = 1;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_I] = 1;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_k] = 1;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_K] = 1;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_S] = 1;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_s] = 1;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_0] = 2;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_1] = 2;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_S_QUOTE] = 3;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_ASTERISK] = 4;
	rawTransitionTables[MTYPE_EXPR][0][MTTYPE_L_PARENTHESIS] = 5;
	rawTransitionTables[MTYPE_EXPR][2][MTTYPE_0] = 2;
	rawTransitionTables[MTYPE_EXPR][2][MTTYPE_1] = 2;
	rawSubmachineCallTables[MTYPE_EXPR][3] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_EXPR][3][MTYPE_EXPR] = 7;

	rawSubmachineCallTables[MTYPE_EXPR][4] = MTYPE_IOTAEXPR;
	rawAfterCallTables[MTYPE_EXPR][4][MTYPE_IOTAEXPR] = 6;

	rawSubmachineCallTables[MTYPE_EXPR][5] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_EXPR][5][MTYPE_EXPR] = 5;

	rawTransitionTables[MTYPE_EXPR][5][MTTYPE_R_PARENTHESIS] = 1;
	rawSubmachineCallTables[MTYPE_EXPR][6] = MTYPE_IOTAEXPR;
	rawAfterCallTables[MTYPE_EXPR][6][MTYPE_IOTAEXPR] = 1;

	rawSubmachineCallTables[MTYPE_EXPR][7] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_EXPR][7][MTYPE_EXPR] = 1;


	// MTYPE_IOTAEXPR ||||||||||||||||||||||||||||||||||||||||
	rawFinalStatesTables[MTYPE_IOTAEXPR][0] = 1;
	rawFinalStatesTables[MTYPE_IOTAEXPR][1] = 2;

	// TRANSITION TABLE --------------------------------------
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_i] = 1;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_I] = 1;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_k] = 1;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_K] = 1;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_S] = 1;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_s] = 1;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_0] = 2;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_1] = 2;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_S_QUOTE] = 3;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_ASTERISK] = 4;
	rawTransitionTables[MTYPE_IOTAEXPR][0][MTTYPE_L_PARENTHESIS] = 5;
	rawTransitionTables[MTYPE_IOTAEXPR][2][MTTYPE_0] = 2;
	rawTransitionTables[MTYPE_IOTAEXPR][2][MTTYPE_1] = 2;
	rawSubmachineCallTables[MTYPE_IOTAEXPR][3] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_IOTAEXPR][3][MTYPE_EXPR] = 7;

	rawSubmachineCallTables[MTYPE_IOTAEXPR][4] = MTYPE_IOTAEXPR;
	rawAfterCallTables[MTYPE_IOTAEXPR][4][MTYPE_IOTAEXPR] = 6;

	rawSubmachineCallTables[MTYPE_IOTAEXPR][5] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_IOTAEXPR][5][MTYPE_EXPR] = 5;

	rawTransitionTables[MTYPE_IOTAEXPR][5][MTTYPE_R_PARENTHESIS] = 1;
	rawSubmachineCallTables[MTYPE_IOTAEXPR][6] = MTYPE_IOTAEXPR;
	rawAfterCallTables[MTYPE_IOTAEXPR][6][MTYPE_IOTAEXPR] = 1;

	rawSubmachineCallTables[MTYPE_IOTAEXPR][7] = MTYPE_EXPR;
	rawAfterCallTables[MTYPE_IOTAEXPR][7][MTYPE_EXPR] = 1;
	
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
		case TT_S:
			return MTTYPE_S;
		case TT_s:
			return MTTYPE_s;
		case TT_K:
			return MTTYPE_K;
		case TT_k:
			return MTTYPE_k;
		case TT_I:
			return MTTYPE_I;
		case TT_i:
			return MTTYPE_i;
		case TT_1:
			return MTTYPE_1;
		case TT_0:
			return MTTYPE_0;
		case TT_S_QUOTE:
			return MTTYPE_S_QUOTE;
		case TT_ASTERISK:
			return MTTYPE_ASTERISK;
		case TT_L_PARENTHESIS:
			return MTTYPE_L_PARENTHESIS;
		case TT_R_PARENTHESIS:
			return MTTYPE_R_PARENTHESIS;
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
		case MTYPE_EXPR:
			return "EXPR";
		case MTYPE_IOTAEXPR:
			return "IOTAEXPR";
	}
	return "";
}