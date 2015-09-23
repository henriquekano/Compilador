#include "analisador.h"
#include "transition_table.h"

// Lista tokenize(char *file){

//   FILE *oFile = fopen(file, "r");

//   fclose(oFile);
//   return 0;
// }

char tokenizer(token token, int previous_state, int current_state){
  if(current_state == S0 && previous_state != S0){
    return 
  }
}