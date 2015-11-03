#include "symbol_table.h"
#include "bool.h"
#include <stdio.h>
#include <stdlib.h>

// void delete_string(void *string){

// }

SymbolTable symbol_table_create(){
  List l = {0};
  list_new(&l, sizeof(_symboltable_symbol), NULL);

  SymbolTable s;
  s.list = l;
  return s;
}

void symbol_table_destroy(SymbolTable *stable){
  list_destroy(&(stable->list));
}

void symbol_table_add(SymbolTable *stable, char *symbolName, int symbolInfo[SYMBOL_TABLE_SYMBOL_INFO]){
  _symboltable_symbol symbol;
  symbol.symbolInfo[ST_POS] = symbolInfo[ST_POS];
  symbol.symbolInfo[ST_PAPEL] = symbolInfo[ST_PAPEL];
  symbol.symbolInfo[ST_TYPE] = symbolInfo[ST_TYPE];
  symbol.symbolInfo[ST_DIMENSION] = symbolInfo[ST_DIMENSION];
  symbol.symbolInfo[ST_ADDRESS] = symbolInfo[ST_ADDRESS];
  symbol.name = symbolName;

  list_append(&(stable->list), &symbol);
}

void symbol_table_pretty_print(SymbolTable *stable){

  bool st_pretty_print(void *data){
    _symboltable_symbol *symbol = (_symboltable_symbol*)data;
    printf("%s: POS=%d - PAPEL=%d - TYPE=%d - DIMENSION=%d - ADDRESS=%d\n", 
            symbol->name, 
            symbol->symbolInfo[ST_POS],
            symbol->symbolInfo[ST_PAPEL],
            symbol->symbolInfo[ST_TYPE],
            symbol->symbolInfo[ST_DIMENSION],
            symbol->symbolInfo[ST_ADDRESS]);
    return TRUE;
  }

  list_for_each(&(stable->list), &st_pretty_print);
}