#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "transition_table.h"

// "end" must come after every reserved word beginning with "end"
const char *RESERVED_WORDS[] = {"begin", "do", "if", "elsif", "endif", "while", "endwhile", "switch", 
"case", "endswitch", "struct", "endstruct", "function", "endfunction", "int", "string", "float", "bool", "return", 
"break", "true", "false", "end"};

const int STATE_TRANSITION_TABLE[NUMBER_STATES][NUMBER_INPUTS_TYPES] =
{										
//Input: 
	//Letter, number, arith.,d_quote,s_quote,  EOC  ,   =  	, comp  , underl, blank , sep   , unknown 	,	NEWLINE ,	HASHTAG, 	point 	, [		,	]	
	{	S2 	,	S5 	,	S6	,	S7 	,	S10 ,	S1 	,	S13	, 	S3 	,	S2 	,	S0 	,	S11 ,	S12 	,	S0  	,	S16		,	S12		,	S11	, 	S11	},	//S0 - inicial
	{	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 		,	S0		,	S0		,	S0		,	S0	, 	S0	}, 	//S1 - ;
	{	S2 	,	S2 	,	S0	,	S12	,	S12	,	S0 	,	S0 	,	S0 	,	S2 	,	S0 	,	S0 	,	S12		,	S0		,	S0		,	S0		,	S0	, 	S12	}, 	//S2 - identificador
	{ 	S0 	, 	S0 	, 	S0	, 	S0	, 	S0	, 	S0	, 	S4 	, 	S12	, 	S0	, 	S0 	, 	S0 	, 	S0		,	S0		,	S0		,	S0		,	S12	, 	S12	}, 	//S3 - comparador 1 caracter
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0	, 	S12	, 	S12	, 	S0	, 	S0 	, 	S0 	, 	S0 		,	S0		,	S0		,	S0		,	S12	, 	S12	}, 	//S4 - comparador 2 caracteres
	{ 	S12	, 	S5 	, 	S0 	, 	S12	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S12		,	S0		,	S0		,	S14		,	S0	, 	S0	},	//S5 - num
	{ 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S12	, 	S12	, 	S0	, 	S0 	, 	S0 	, 	S0		,	S0		,	S0		,	S0		,	S12	, 	S12	},	//S6 - operador aritmetico
	{ 	S7 	, 	S7 	, 	S7 	, 	S8 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 		,	S7		,	S7		,	S7		,	S7	, 	S7	},	//S7 - tudo exceto "
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 		,	S0		,	S0		,	S0		,	S0	, 	S0	},	//S8 - completa ""
	{ 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S10	,	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 		,	S9		,	S9		,	S9		,	S9	, 	S9	},	//S9 - tudo exceto '
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 		,	S0		,	S0		,	S0		,	S0	, 	S0	},	//S10 - completa ''
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0	, 	S0	, 	S0 	, 	S0 	, 	S0 	, 	S0 		,	S0		,	S0		,	S0		,	S0	, 	S0	},	//S11 - separadores (, ), ,
	{ 	S12	, 	S12	, 	S0	, 	S12	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S12		,	S0		,	S0		,	S12		,	S12	, 	S12	},	//S12 - desconhecidos
	{ 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S0	, 	S4 	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S0 		,	S0		,	S0		,	S0		,	S0	, 	S0	},	//S13 - atribuicao (=)

	{ 	S12	, 	S14	, 	S0 	, 	S12	, 	S12	,	S0 	, 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S12		,	S0		,	S0		,	S12		,	S12	, 	S12	},	//S14 - float
	{ 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15		,	S24		,	S15		,	S15		,	S15	, 	S15	},	//S15 - line comment
	{ 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15	, 	S15 , 	S15	, 	S15	, 	S15	, 	S15	, 	S15		,	S0		,	S17		,	S15		,	S15	, 	S15	},	//S16 - block comment?
	{ 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17		,	S17		,	S18		,	S17		,	S17	, 	S17	},	//S17 - block comment begin
	{ 	S17	, 	S17	, 	S17	, 	S17 , 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17	, 	S17		,	S17		,	S23		,	S17		,	S17	, 	S17	},	//S18 - block comment end?
	{   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0      ,   S0      ,   S0      ,   S0      ,	S0	, 	S0	},   //S23 - fecho de comentario bloco
	{   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0  ,   S0      ,   S0      ,   S0      ,   S0      ,	S0	, 	S0	}   //S24 - fecho de comentario de linha
};

int input_converter_function(char character){
	if(isalpha((int)character)){
		return IT_LETTER;
	}else if(isdigit((int)character)){
		return IT_NUMBER;
	}else if(character == '+' || character == '-' || character == '/' || character == '*'){
		return IT_ARITH_SYMBOL;
	}else if(character == '\"'){
		return IT_DOUBLE_QUOTE;
	}else if(character == '\''){
		return IT_SINGLE_QUOTE;
	}else if(character == ';'){
		return IT_END_OF_COMMAND;
	}else if(character == '='){
		return IT_EQUALS;
	}else if(character == '<' || character == '>' || character == '!' ){
		return IT_COMPARATOR;
	}else if(character == '_'){
		return IT_UNDERLINE;
	}else if(character == '\n'){
		return IT_NEWLINE;
	}else if(character == '#'){
		return IT_HASHTAG;
	}else if(character == '.'){
		return IT_POINT;
	}else if(character == ' ' || character == '\t' || character == '\v' || character == '\f' || character == '\r'){
		return IT_BLANK;
	}else if(character == '(' || character == ')' || character == ','){
		return IT_SEPARATOR;
	}else if(character == '['){
		return IT_L_SQ_BRACKET;
	}else if(character == ']'){
		return IT_R_SQ_BRACKET;
	}else{
		return IT_UNKNOWN;
	}
}

//relacao estado e o token que ele gera
Token_type state_converter_token_type(States state, char buffer[50]){
	switch(state){
		case S1:
			return TT_END_OF_COMMAND;
		case S2:
			if (is_reserved(buffer) == 0){
				return TT_RESERVED;
			} else {
				return TT_IDENTIFIER;
			}
		case S3:
			return TT_COMPARATOR;
		case S4:
			return TT_COMPARATOR;
		case S5:
			return TT_INT;
		case S6:
			return TT_ARITH_SYMBOL;
		case S8:
			return TT_STRING; 
		case S10:
			return TT_STRING;
		case S11:
			if(strcmp(buffer, "]")){
				return TT_R_SQ_BRACKET;
			}else if(strcmp(buffer, "[")){
				return TT_L_SQ_BRACKET;
			}else if(strcmp(buffer, ")")){
				return TT_R_PARENTHESIS;
			}else if(strcmp(buffer, "(")){
				return TT_L_PARENTHESIS;
			}
		case S13:
			return TT_ASSIGNMENT;
		case S14:
			return TT_FLOAT;
		case S23:
			return TT_IGNORE;
		case S24:
			return TT_IGNORE;
		default:
			return TT_UNKNOWN;
	}
}

int is_reserved(char string[50]){
	int result = -1;
	int i = 0;

	while(RESERVED_WORDS[i]) {
		if(strcmp(RESERVED_WORDS[i], string) == 0) {
			result = 0;
			break;
		}
		i++;
	}
	return result;
}