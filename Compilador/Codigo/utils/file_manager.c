#include "file_manager.h"

void write(FILE *file, char *stuff){
  fprintf(file, "%s", stuff);
}