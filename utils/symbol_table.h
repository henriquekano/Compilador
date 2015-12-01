#ifndef SYMBOL_TABLE_H_DEFINED
#define SYMBOL_TABLE_H_DEFINED

#include "bool.h"
#include "list.h"

#define SYMBOL_TABLE_SYMBOL_INFO 5

typedef enum{
  ST_POS = 0,
  ST_PAPEL = 1,
  ST_TYPE = 2,
  ST_DIMENSION = 3,
  ST_ADDRESS = 4,
  ST_ROWS = 5,
  ST_COLUMNS = 6
}Table_info;

typedef enum{
  ST_TYPE_INT = 0,
  ST_TYPE_FLOAT = 1,
  ST_TYPE_STRING = 2,
  ST_TYPE_BOOL = 3
}Symbol_type;

typedef enum{
  ST_PAPEL_FUNCTION = 0,
  ST_PAPEL_VAR = 1,
  ST_PAPEL_STRUCT = 2
}Symbol_papel;

typedef struct _symboltable_symbol{
  char *name;
  int symbolInfo[SYMBOL_TABLE_SYMBOL_INFO];
}_symboltable_symbol;

typedef struct SymbolTable{
  List list;
} SymbolTable;

SymbolTable symbol_table_create();
void symbol_table_destroy(SymbolTable *stable); 

void symbol_table_add(SymbolTable *stable, char *symbolName, int symbolInfo[SYMBOL_TABLE_SYMBOL_INFO]);
void symbol_table_pretty_print(SymbolTable *stable);

int *symbol_table_get_info(SymbolTable *stable, char *symbolName);

int symbol_table_get_position(SymbolTable *stable, char *symbolName);

Symbol_papel symbol_table_get_papel(SymbolTable *stable, char *symbolName);
Symbol_type symbol_table_get_type(SymbolTable *stable, char *symbolName);
int symbol_table_get_dimension(SymbolTable *stable, char *symbolName);
int symbol_table_get_address(SymbolTable *stable, char *symbolName);

#endif