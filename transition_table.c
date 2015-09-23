#include <stdio.h>
#include <ctype.h>
#include "transition_table.h"

const int STATE_TRANSITION_TABLE[NUMBER_STATES][NUMBER_INPUTS_TYPES] =
{
//Input: 
	//Letter, number, arith.,d_quote,s_quote,  EOC  ,   =  	, comp  , underl, blank , sep   , unknown
	{		S2 	,		S5 	,		S6	,		S7 	,		S10 ,		S1 	,		S3 	, 	S3 	,		S2 	, 	S0 	,		S11 ,		S12	}, //S0
	{		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	}, //S1
	{		S2 	,		S2 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S0 	,		S2 	,		S0 	,		S0 	,		S0 	}, //S2
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S4 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S3
	{ 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	, 	S3 	}, //S4
	{ 	S0 	, 	S5 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S5
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S6
	{ 	S7 	, 	S7 	, 	S7 	, 	S8 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	, 	S7 	}, //S7
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S8
	{ 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S1 	,		S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	, 	S9 	}, //S9
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S10
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}, //S11
	{ 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	, 	S0 	}  //S12
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
	}else{
		return UNKNOWN;
	}
}


