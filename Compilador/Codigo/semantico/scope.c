#include "scope.h"
#include "../utils/symbol_table.h"
#include "../utils/list.h"
#include <stdio.h>
#include <stdlib.h>

static Scope *current_scope;

void scope_destroy_recursive(Scope *scope){
  symbol_table_pretty_print(&(scope->symbol_table));
  symbol_table_destroy(&(scope->symbol_table));
  if(scope->father != NULL){
    scope_destroy_recursive(scope->father);
  }
}

void scope_destroy(){
  scope_destroy_recursive(current_scope);
}

void scope_init(){
  current_scope = (Scope *)malloc(sizeof(struct Scope));
  current_scope->father = NULL;
  current_scope->symbol_table = symbol_table_create();
}

Scope *scope_create(){
  Scope *new_scope = (Scope *)malloc(sizeof(struct Scope));
  new_scope->father = current_scope;
  new_scope->symbol_table = symbol_table_create();
  return new_scope;
}

void scope_enter_new(){
  Scope *new_scope = scope_create();
  new_scope->symbol_table = symbol_table_create();
  new_scope->father = current_scope;
  current_scope = new_scope;
}

void scope_exit_scope(){
  symbol_table_destroy(&(current_scope->symbol_table));
  current_scope = current_scope->father;
}

bool scope_var_exists_recursive(Scope *scope, char *var_name){
  int *var_info = symbol_table_get_info(&(current_scope->symbol_table), var_name);
  if(var_info == NULL && scope->father != NULL){
    return scope_var_exists_recursive(scope->father, var_name) ;
  }else if(var_info == NULL && scope->father == NULL){
    return FALSE;
  }else if(var_info != NULL){
    return TRUE;
  }
}

bool scope_var_exists(char *var_name){
  return scope_var_exists_recursive(current_scope, var_name);
}

void scope_add_var(char *symbolName, int symbolInfo[SYMBOL_TABLE_SYMBOL_INFO]){
  symbol_table_add(&(current_scope->symbol_table), symbolName, symbolInfo);
}