#include "scope.h"
#include "../utils/symbol_table.h"
#include "../utils/list.h"
#include <stdio.h>
#include <stdlib.h>

static Scope *head;
static Scope *current_scope;
static FILE *scope_output_file;

void scope_destroy_recursive(void *scope){
  if(scope_output_file != NULL){
    symbol_table_fprintf(&(((Scope *)scope)->symbol_table), scope_output_file);
  }
  symbol_table_destroy(&(((Scope *)scope)->symbol_table));

  list_destroy(((Scope *)scope)->children);
}

void scope_destroy(){
  scope_destroy_recursive((void *)head);
}

void scope_list_destroy(void *scope){
  scope_destroy_recursive((void *)scope);
}

void scope_init(FILE *file){
  scope_output_file = file;
  current_scope = (Scope *)malloc(sizeof(struct Scope));
  current_scope->father = NULL;
  current_scope->children = (List *)malloc(sizeof(struct List));
  list_new(current_scope->children, sizeof(Scope), scope_list_destroy);
  current_scope->symbol_table = symbol_table_create();
  head = current_scope;
}

Scope *scope_create(){
  Scope *new_scope = (Scope *)malloc(sizeof(struct Scope));
  list_prepend(current_scope->children, new_scope);
  new_scope->father = current_scope;
  new_scope->children = (List *)malloc(sizeof(List));
  list_new(new_scope->children, sizeof(Scope), scope_list_destroy);
  new_scope->symbol_table = symbol_table_create();
  return new_scope;
}

void scope_enter_new(){
  current_scope = scope_create();
}

void scope_exit_scope(){
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
  } else{
    return TRUE;
  }
}

bool scope_var_exists(char *var_name, bool recursive){
  if(recursive){
    return scope_var_exists_recursive(current_scope, var_name);
  }else{
    int *var_info = symbol_table_get_info(&(current_scope->symbol_table), var_name);
    return var_info != NULL;
  }
}

void scope_add_var(char *symbolName, int symbolInfo[SYMBOL_TABLE_SYMBOL_INFO]){
  symbol_table_add(&(current_scope->symbol_table), symbolName, symbolInfo);
}