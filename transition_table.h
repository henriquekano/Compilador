#ifndef TRANSITION_TABLE_H_INCLUDED
#define TRANSITION_TABLE_H_INCLUDED
#define NUMBER_STATES 14
#define NUMBER_INPUTS_TYPES 12

#include "utils/token.h"
//Tipos de entradas diferentes consideradas nas transicoes de estado
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
	S11 = 11, //separadores
	S12 = 12 //desconhecidos
}States;

extern const int STATE_TRANSITION_TABLE[NUMBER_STATES][NUMBER_INPUTS_TYPES];

//converte um char p/ um InputType
int input_converter_function(char character);
//Converte um States p/ o Token_type que o estado gera
Token_type state_converter_token_type(States state);

#endif //TRANSITION_TABLE_H_INCLUDED