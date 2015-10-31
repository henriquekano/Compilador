#ifndef MACHINES_H_
#define MACHINES_H_

#include <stdlib.h>
#include "automataPE.h"

#define MAX_FINAL_STATES 10
#define MAX_STATES 60
#define N_MACHINE_TOKEN_TYPES 46
#define N_MACHINE_TYPES 7

#define MINVALID_STATE -1

typedef enum{
	MTYPE_INVALID = -1,
	MTYPE_PROGRAM = 0,
	MTYPE_COMMAND = 1,
	MTYPE_DECLARATION = 2,
	MTYPE_CONDITION = 3,
	MTYPE_EXPRESSION = 4,
	MTYPE_VALUE = 5
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
	MTTYPE_STRUCT 				= 12 	,// continue
	MTTYPE_ENDSTRUCT 			= 13 	,// continue
	MTTYPE_CONTINUE 			= 13 	,// continue
	MTTYPE_FUNCTION 			= 14 	,// function
	MTTYPE_RETURN 				= 15 	,// return
	MTTYPE_ENDFUNCTION 			= 16 	,// endfunction
	MTTYPE_SCAN 				= 17 	,// scan
	MTTYPE_PRINT 				= 18 	,// print
	MTTYPE_SEMICOLON 			= 19 	,// ;
	MTTYPE_COMMA 				= 20 	,// ,
	MTTYPE_DOT 					= 21 	,// .
	MTTYPE_LEFT_BRACKET 		= 22 	,// [
	MTTYPE_RIGHT_BRACKET 		= 23 	,// ]
	MTTYPE_LEFT_PARENTHESIS 	= 24 	,// (
	MTTYPE_RIGHT_PARENTHESIS 	= 25 	,// )
	MTTYPE_EQUAL 				= 26 	,// =
	MTTYPE_PLUS 				= 27 	,// +
	MTTYPE_MINUS 				= 28 	,// -
	MTTYPE_MULTIPLICATION 		= 29 	,// *
	MTTYPE_DIVISION 			= 30 	,// /
	MTTYPE_NOT 					= 31 	,// not
	MTTYPE_AND 					= 32 	,// and
	MTTYPE_OR 					= 33 	,// or
	MTTYPE_SINGLE_QUOTE 		= 34 	,// '
	MTTYPE_DOUBLE_QUOTE 		= 35 	,// "
	MTTYPE_ID 					= 36 	,// identificador
	MTTYPE_INT 					= 37 	,// inteiro
	MTTYPE_FLOAT				= 38 	,// float
	MTTYPE_STRING 				= 39 	,// string
	MTTYPE_ARRAY 				= 40 	,// array
	MTTYPE_MATRIX 				= 41 	,// matriz
	MTTYPE_TYPE 				= 42 	,// int, float, string, bool
	MTTYPE_BOOL 				= 43 	,// true, false
	MTTYPE_COMPARATOR 			= 44 	 // <, >, <=, >=, ==, !=
} MachineTokenTypes;

AutomataPE init_machines();
int convert_token_to_machine_type(Token *token);
char *machineid_to_name(int machineId);
#endif /* MACHINES_H_ */
