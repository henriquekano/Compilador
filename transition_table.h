
#ifndef TRANSITION_TABLE_H_INCLUDED
#define TRANSITION_TABLE_H_INCLUDED
#define NUMBER_STATES = 20;
#define NUMBER_INPUTS_TYPES = 9;

typedef enum{
	LETTER = 0,
	NUMBER = 1,
	ARITH_SYMBOL = 2,
	DOUBLE_QUOTE = 3,
	SINGLE_QUOTE = 4,
	END_OF_COMMAND = 5,
	EQUALS = 6,
	COMPARATOR = 7,
	UNDERLINE = 8,
	BLANK = 9,
	UNKNOWN = 10
}InputTypes;

//Ver no relatorio o que significa cada estado
typedef enum{
	S0 = 0, 
	S1 = 1, 
	S2 = 2, 
	S3 = 3, 
	S4 = 4,
	S5 = 5,
	S6 = 6,
	S7 = 7,
	S8 = 8,
	S9 = 9,
	S10 = 0,
	S11 = 11
}States;

int transition_table[NUMBER_STATES][NUMBER_INPUTS_TYPES] =
{
//Input: 
	//Letter, number, arith.,d_quote,s_quote,  EOC 	, 	=	, comp 	, underl, blank , unkno
	{		,		,		,		,		,		,		,		,		,		,		}, //S0
	{		,		,		,		,		,		,		,		,		,		,		}, //S1
	{		,		,		,		,		,		,		,		,		,		,		}, //S2
	{		,		,		,		,		,		,		,		,		,		,		}, //S3
	{		,		,		,		,		,		,		,		,		,		,		}, //S4
	{		,		,		,		,		,		,		,		,		,		,		}, //S5
	{		,		,		,		,		,		,		,		,		,		,		}, //S6
	{		,		,		,		,		,		,		,		,		,		,		}, //S7
	{		,		,		,		,		,		,		,		,		,		,		}, //S8
	{		,		,		,		,		,		,		,		,		,		,		}, //S9
	{		,		,		,		,		,		,		,		,		,		,		}, //S10
	{		,		,		,		,		,		,		,		,		,		,		}  //S11
}

int char_to_table_input(char character);

#endif //TRANSITION_TABLE_H_INCLUDED