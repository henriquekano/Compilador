#ifndef SCOPE_H_INCLUDED
#define SCOPE_H_INCLUDED

#include <stdio.h>
#include "../utils/symbol_table.h"
#include "../utils/list.h"
#include "../utils/bool.h"

typedef struct Scope{
  struct Scope *father;
  struct List *children;
  SymbolTable symbol_table;
} Scope;

void scope_init(FILE *file);
void scope_destroy();
void scope_enter_new();
void scope_exit_scope();
void scope_add_var(char *symbolName, int symbolInfo[SYMBOL_TABLE_SYMBOL_INFO]);
bool scope_var_exists(char *var_name, bool recursive);

#endif