#ifndef MACHINES_H_
#define MACHINES_H_

#include <stdlib.h>
#include "automataPE.h"

#define MAX_FINAL_STATES 2
#define MAX_STATES 7
#define N_MACHINE_TOKEN_TYPES 12
#define N_MACHINE_TYPES 3

#define MINVALID_STATE -1

typedef enum{
	MTYPE_INVALID = -1,
	MTYPE_PROGRAM = 0,
	MTYPE_EXPR = 1
	MTYPE_IOTAEXPR = 2,
} MachineTypes;

typedef enum{
	MTTYPE_INVALID 				= -1, // invalido
	MTTYPE_S 					= 0;
	MTTYPE_s 					= 1;
	MTTYPE_K 					= 2;
	MTTYPE_k 					= 3;
	MTTYPE_I 					= 4;
	MTTYPE_i 					= 5;
	MTTYPE_1 					= 6;
	MTTYPE_0 					= 7;
	MTTYPE_S_QUOTE 				= 8;
	MTTYPE_ASTERISK 			= 9;
	MTTYPE_L_PARENTHESIS 		= 10;
	MTTYPE_R_PARENTHESIS 		= 11;
} MachineTokenTypes;

AutomataPE init_machines();
int convert_token_to_machine_type(Token *token);
char *machineid_to_name(int machineId);
#endif /* MACHINES_H_ */
