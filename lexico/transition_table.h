#ifndef TRANSITION_TABLE_H_INCLUDED
#define TRANSITION_TABLE_H_INCLUDED
#define NUMBER_STATES 25
#define NUMBER_INPUTS_TYPES 17

#include "../utils/token.h"
//Tipos de entradas diferentes consideradas nas transicoes de estado
typedef enum{
	TOKEN_TYPE_LETTER = 0,
	TOKEN_TYPE_NUMBER = 1,
	TOKEN_TYPE_ARITH_SYMBOL = 2,
	TOKEN_TYPE_DOUBLE_QUOTE = 3,
	TOKEN_TYPE_SINGLE_QUOTE = 4,
	TOKEN_TYPE_END_OF_COMMAND = 5,
	TOKEN_TYPE_EQUALS = 6,
	TOKEN_TYPE_COMPARATOR = 7,
	TOKEN_TYPE_UNDERLINE = 8,
	TOKEN_TYPE_BLANK = 9,
	TOKEN_TYPE_SEPARATOR = 10,
	TOKEN_TYPE_UNKNOWN = 11,
	TOKEN_TYPE_NEWLINE = 12,
	TOKEN_TYPE_HASHTAG = 13,
	TOKEN_TYPE_POINT = 14, 
	TOKEN_TYPE_L_SQ_BRACKET = 15,
	TOKEN_TYPE_R_SQ_BRACKET = 16
}TokenTypes;

//Ver no relatorio o que significa cada estado
typedef enum{
	S0 = 0, //inicial *
	S1 = 1, //ponto e virgula
	S2 = 2, //identificador
	S3 = 3, //comparador 1 caracter
	S4 = 4, //comparador 2 caracteres
	S5 = 5, //numero
	S6 = 6, //operador aritmetico
	S7 = 7, //tudo exceto " *
	S8 = 8, //completa ""
	S9 = 9, //tudo exceto ' *
	S10 = 10, //completa ''
	S11 = 11, //separadores
	S12 = 12, //desconhecidos
	S13 = 13, //atribuicao
	S14 = 14, //float
	S15 = 15, //line comment
	S16 = 16, //block comment?
	S17 = 17, //block comment begin
	S18 = 18, //block comment end?
	S19 = 19, //primeiro [
	S20 = 20, //vetor
	S21 = 21, //segundo [
	S22 = 22, //matriz
	S23 = 23, //fecho de comentario bloco
	S24 = 24 //fecho de comentario de linha 
}States;

extern const int STATE_TRANSITION_TABLE[NUMBER_STATES][NUMBER_INPUTS_TYPES];

extern const char *RESERVED_WORDS[];

//converte um char p/ um InputType
int input_converter_function(char character);
//Converte um States p/ o Token_type que o estado gera
Token_type state_converter_token_type(States state, char buffer[50]);
//retorna 0 se string for uma palavra reservada, senão -1
int is_reserved(char string[50]);

#endif //TRANSITION_TABLE_H_INCLUDED