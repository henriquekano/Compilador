#include "symbol_table.h"
#include "bool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int *symbol_table_get_info(SymbolTable *stable, char *symbolName){

  //Recebe um symbol e um string
  bool symbol_table_symbol_comparator(void *original, void *compared){
    _symboltable_symbol *symbol = (_symboltable_symbol*)original;
    char *string = (char *)compared;

    if(strcmp(symbol->name, string) == 0){
      return TRUE;
    }else{
      return FALSE;
    }
  }

  _symboltable_symbol *symbol = (_symboltable_symbol*)list_get(&(stable->list), symbolName, symbol_table_symbol_comparator);

  return symbol->symbolInfo;
}

int symbol_table_get_position(SymbolTable *stable, char *symbolName){
  return symbol_table_get_info(stable, symbolName)[ST_POS];
}

Symbol_papel symbol_table_get_papel(SymbolTable *stable, char *symbolName){
  return symbol_table_get_info(stable, symbolName)[ST_PAPEL];
}

Symbol_type symbol_table_get_type(SymbolTable *stable, char *symbolName){
  return symbol_table_get_info(stable, symbolName)[ST_TYPE];
}

int symbol_table_get_dimension(SymbolTable *stable, char *symbolName){
  return symbol_table_get_info(stable, symbolName)[ST_DIMENSION];
}

int symbol_table_get_address(SymbolTable *stable, char *symbolName){
  return symbol_table_get_info(stable, symbolName)[ST_ADDRESS];
}