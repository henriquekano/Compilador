#ifndef SCOPE_H_INCLUDED
#define SCOPE_H_INCLUDED

#include "../utils/symbol_table.h"
#include "../utils/list.h"
#include "../utils/bool.h"

typedef struct Scope{
  struct Scope *father;
  SymbolTable symbol_table;
} Scope;

void scope_init();
void scope_destroy();
void scope_enter_new();
void scope_add_var(char *symbolName, int symbolInfo[SYMBOL_TABLE_SYMBOL_INFO]);
bool scope_var_exists();

#endif