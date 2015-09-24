#include <stdio.h>
#include <ctype.h>
#include "transition_table.h"
#include "utils/token.h"

const int STATE_TRANSITION_TABLE[NUMBER_STATES][NUMBER_INPUTS_TYPES] =
{
//Input: 
	//Letter, number, arith.,d_quote,s_quote,  EOC  ,   =  	, comp  , underl, blank , sep   , unknown
	{		S2 	,		S5 	,		S6	,		S7 	,		S10 ,		S1 	,		S3 	, 	S3 	,		S2 	, 	S0 	,		S11 ,		S12	}, //S0 - inicial
	{		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	}, //S1 - ;
	{		S2 	,		S2 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S2 	,		S0 	,		S0 	,		S0 	}, //S2 - identificador
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S4 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S3 - comparador 1 caracter
	{ 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	}, //S4 - comparador 2 caracteres
	{ 	S0 	, 	S5 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S5 - string
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S6 - operador aritmetico
	{ 	S7 	, 	S7 	, 	S7 	, 	S8 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	}, //S7 - tudo exceto " *
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S8 - completa ""
	{ 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S1 	,		S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	}, //S9 - tudo exceto ' *
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S10 - completa ''
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S11 - separadores
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}  //S12 - desconhecidos
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
	}else if(isspace((int)character)){
		return BLANK;
	}else if(character == '(' || character == ')' || character == '[' || character == ']'){
		return SEPARATOR;
	}else{
		return UNKNOWN;
	}
}

Token_type state_converter_token_type(States state){
	switch(state){
		case S1:
			return TT_END_OF_COMMAND;
		case S2:
			return TT_IDENT_RESERVED;
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
		default:
			return TT_UNKNOWN;
	}
}