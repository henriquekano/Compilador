
#ifndef TRANSITION_TABLE_H_INCLUDED
#define TRANSITION_TABLE_H_INCLUDED
#define NUMBER_STATES 14
#define NUMBER_INPUTS_TYPES 12

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
	SEPARATOR = 10,
	UNKNOWN = 11
}InputTypes;

//Ver no relatorio o que significa cada estado
typedef enum{
	S0 = 0, //inicial *
	S1 = 1, //ponto e virgula
	S2 = 2, //identificador
	S3 = 3, //comparador 1 caracter
	S4 = 4, //comparador 2 caracteres
	S5 = 5, //string
	S6 = 6, //operador aritmetico
	S7 = 7, //tudo exceto " *
	S8 = 8, //completa ""
	S9 = 9, //tudo exceto ' *
	S10 = 10, //completa ''
	S11 = 11, //espaco
	S12 = 12, //separadores
	S13 = 13, //desconhecidos
}States;

int state_transition_table[NUMBER_STATES][NUMBER_INPUTS_TYPES] =
{
//Input: 
	//Letter, number, arith.,d_quote,s_quote,  EOC 	, 	=	, comp 	, underl, blank , sep 	, unknown
	{	S2	,	S5	,	S6	,	S7	,	S10	,	S1	,	S3	,	S3	,	S2	,	S11	,	S12	,	S13	}, //S0
	{	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S1
	{	S2	,	S2	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S2	,	S0	,	S0	,	S0	}, //S2
	{	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S4	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S3
	{	S3	,	S3	,	S3	,	S3	,	S3	,	S3	,	S3	,	S3	,	S3	,	S3	,	S3	,	S3	}, //S4
	{	S0	,	S5	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S5
	{	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S6
	{	S7	,	S7	,	S7	,	S8	,	S7	,	S7	,	S7	,	S7	,	S7	,	S7	,	S7	,	S7	}, //S7
	{	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S8
	{	S9	,	S9	,	S9	,	S9	,	S10	,	S9	,	S9	,	S9	,	S9	,	S9	,	S9	,	S9	}, //S9
	{	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S10
	{	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S11
	{	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	,	S0	}, //S12
};

int input_converter_function(char character);

#endif //TRANSITION_TABLE_H_INCLUDED