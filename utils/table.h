#ifndef TABLE_H_DEFINED
#define TABLE_H_DEFINED
 
typedef int (*converterFunction)(void *);
 
typedef struct Table {
  int rows;
  int columns;
  int **table;
  converterFunction converterFn;
} Table;
 
Table table_create(int rows, int columns, int table[rows][columns]);
void table_destroy(Table *t);

int table_rows_size(Table *t);
int table_columns_size(Table *t);

int table_get(Table *t, int row, int column);
int table_convert_to_index(Table *t, void *input);
void table_print_table(Table *t);
 
#endif