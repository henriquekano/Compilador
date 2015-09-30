#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "transition_table.h"
#include "utils/token.h"

const char *RESERVED_WORDS[] = {"begin", "do", "end", "if", "elsif", "endif", "while", "endwhile", "switch", "case", "endswitch", "struct", "endstruct", "function", "endfunction", "int", "string", "bool", "return", "break", "true", "false"};

const int STATE_TRANSITION_TABLE[NUMBER_STATES][NUMBER_INPUTS_TYPES] =
{										
//Input: 
	//Letter, number, arith.,d_quote,s_quote,  EOC  ,   =  	, comp  , underl, blank , sep   , unknown
	{	S2 	,	S5 	,	S6	,	S7 	,	S10 ,	S1 	,	S13	, 	S3 	,	S2 	,	S0 	,	S11 ,	S12	},	//S0 - inicial
	{	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	,	S0 	}, 	//S1 - ;
	{	S2 	,	S2 	,	S0	,	S12	,	S12	,	S0 	,	S0 	,	S0 	,	S2 	,	S0 	,	S0 	,	S12	}, 	//S2 - identificador
	{ 	S0 	, 	S0 	, 	S0	, 	S0	, 	S0	, 	S0	, 	S4 	, 	S12	, 	S0	, 	S0 	, 	S0 	, 	S0	}, 	//S3 - comparador 1 caracter
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0	, 	S12	, 	S12	, 	S0	, 	S0 	, 	S0 	, 	S0 	}, 	//S4 - comparador 2 caracteres
	{ 	S12	, 	S5 	, 	S0 	, 	S12	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S12	},	//S5 - num
	{ 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S12	, 	S12	, 	S0	, 	S0 	, 	S0 	, 	S0	},	//S6 - operador aritmetico
	{ 	S7 	, 	S7 	, 	S7 	, 	S8 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	},	//S7 - tudo exceto " *
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	},	//S8 - completa ""
	{ 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S10	,	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	},	//S9 - tudo exceto ' *
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	},	//S10 - completa ''
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0	, 	S0	, 	S0 	, 	S0 	, 	S0 	, 	S0 	},	//S11 - separadores
	{ 	S12	, 	S12	, 	S0	, 	S12	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S12	},	//S12 - desconhecidos
	{ 	S0 	, 	S0 	, 	S12	, 	S0 	, 	S0 	, 	S0	, 	S4 	, 	S12	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}	//S13 - atribuicao (=)
};

int input_converter_function(char character){
	if(isalpha((int)character)){
		return LETTER;
	}else if(isdigit((int)character)){
		return NUMBER;
	}else if(character == '+' || character == '-' || character == '/' || character == '*'){
		return ARITH_SYMBOL;
	}else if(character == '\"'){
		return DOUBLE_QUOTE;
	}else if(character == '\''){
		return SINGLE_QUOTE;
	}else if(character == ';'){
		return END_OF_COMMAND;
	}else if(character == '='){
		return EQUALS;
	}else if(character == '<' || character == '>' || character == '!' ){
		return COMPARATOR;
	}else if(character == '_'){
		return UNDERLINE;
	}else if(character == '\n'){
		return NEWLINE;
	}else if(isspace((int)character)){
		return BLANK;
	}else if(character == '(' || character == ')' || character == '[' || character == ']' || character == ','){
		return SEPARATOR;
	}else{
		return UNKNOWN;
	}
}

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
			return TT_NUMBER;
		case S6:
			return TT_ARITH_SYMBOL;
		case S8:
			return TT_STRING; 
		case S10:
			return TT_STRING;
		case S11:
			return TT_SEPARATOR;
		case S13:
			return TT_ASSIGNMENT;
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