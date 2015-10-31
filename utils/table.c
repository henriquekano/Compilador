#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "../sintatico/machines.h"

Table table_create(int rows, int columns, int table[rows][columns]){
  int **new_table = (int **)malloc(sizeof(int *) * rows);
  int i = 0, j = 0;

  for(i = 0; i < rows; i++){
    new_table[i] = (int *)malloc(sizeof(int) * columns);

    for(j = 0; j < columns; j++){
      new_table[i][j] = table[i][j];
    }
  }

  Table t = {rows, columns, new_table};
  return t;
}
void table_destroy(Table *t){
  int i = 0;
  for(i = 0; i < t->rows; i++){
    free(t->table[i]);
  }
}

int table_rows_size(Table *t){
  return t->rows;
}

int table_columns_size(Table *t){
  return t->columns;
}

// int table_convert_to_index(Table *t, void *input){
//   return t->converterFn(input);
// }

int table_get(Table *t, int row, int column){
  return t->table[row][column];
}

void table_print_table(Table *t){
  int i = 0, j =0;
  int rows = table_rows_size(t);
  int columns = table_columns_size(t);

  for(i = 0; i < rows; i++){
    for(j = 0; j < columns; j++){
      printf("%d ", t->table[i][j]);
    }
    printf("\n");
  }
}

bool is_value_in_array(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return TRUE;
    }
    return FALSE;
}