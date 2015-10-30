#ifndef MACHINES_H_
#define MACHINES_H_

#include <stdlib.h>

#define MAX_FINAL_STATES 10
#define MAX_STATES 60
#define N_MACHINE_TOKEN_TYPES 40
#define N_MACHINE_TYPES 8

#define MINVALID_STATE -1

typedef enum{
	MTYPE_INVALID = -1,
	MTYPE_PROGRAM = 0,
	MTYPE_COMMAND = 1,
	MTYPE_DECLARATION = 2,
	MTYPE_CONDITION = 3,
	MTYPE_EXPRESSION = 4,
	MTYPE_EXPRESSION_ARIT = 5,
	MTYPE_EXPRESSION_BOOL = 6,
	MTYPE_VALUE = 7
} MachineTypes;

typedef enum{
	MTTYPE_INVALID 				= -1 	,// invalido
	MTTYPE_BEGIN 				= 0 	,// begin
	MTTYPE_END 					= 1 	,// end
	MTTYPE_DO 					= 2 	,// do
	MTTYPE_IF 					= 3		,// if
	MTTYPE_ELSIF 				= 4 	,// elsif
	MTTYPE_ENDIF 				= 5 	,// endif
	MTTYPE_ELSE 				= 6 	,// else
	MTTYPE_WHILE 				= 7 	,// while
	MTTYPE_ENDWHILE 			= 8 	,// endwhile
	MTTYPE_WHEN 				= 9 	,// when
	MTTYPE_ENDWHEN 				= 10 	,// endwhen
	MTTYPE_IS 					= 11 	,// is
	MTTYPE_CONTINUE 			= 12 	,// continue
	MTTYPE_FUNCTION 			= 13 	,// function
	MTTYPE_RETURN 				= 13 	,// return
	MTTYPE_ENDFUNCTION 			= 14 	,// endfunction
	MTTYPE_SCAN 				= 15 	,// scan
	MTTYPE_PRINT 				= 16 	,// print
	MTTYPE_SEMICOLON 			= 17 	,// ;
	MTTYPE_COMMA 				= 18 	,// ,
	MTTYPE_DOT 					= 19 	,// .
	MTTYPE_LEFT_BRACKET 		= 20 	,// [
	MTTYPE_RIGHT_BRACKET 		= 21 	,// ]
	MTTYPE_LEFT_PARENTHESIS 	= 22 	,// (
	MTTYPE_RIGHT_PARENTHESIS 	= 23 	,// )
	MTTYPE_EQUAL 				= 24 	,// =
	MTTYPE_PLUS 				= 25 	,// +
	MTTYPE_MINUS 				= 26 	,// -
	MTTYPE_MULTIPLICATION 		= 27 	,// *
	MTTYPE_DIVISION 			= 28 	,// /
	MTTYPE_AND 					= 29 	,// &&
	MTTYPE_OR 					= 30 	,// || 
	MTTYPE_SINGLE_QUOTE 		= 31 	,// '
	MTTYPE_DOUBLE_QUOTE 		= 32 	,// "
	MTTYPE_ID 					= 33 	,// identificador
	MTTYPE_INT 					= 34 	,// inteiro
	MTTYPE_FLOAT				= 35 	,// float
	MTTYPE_STRING 				= 36 	,// string
	MTTYPE_VECTOR 				= 37 	,// vetor
	MTTYPE_ARRAY 				= 38 	,// ARRAY
	MTTYPE_TYPE 				= 39 	,// int, float, string, bool
	MTTYPE_BOOL 				= 40 	,// true, false
	MTTYPE_COMPARATOR 			= 41 	// <, >, <=, >=, ==, !=
} MachineTokenTypes;

// typedef struct machine {
// 	int id;
// 	int current_state;
// 	int final_state[MAX_FINAL_STATES];
// 	int transition_table[MAX_STATES][N_MACHINE_TOKEN_TYPES];
// 	int submachine_call[MAX_STATES][N_MACHINE_TYPES];
// } Machine;

// Machine machines[8];

void init_machines(AutomataPE *automata);
// void machine_in_final_state(int machineId);

#endif /* MACHINES_H_ */
