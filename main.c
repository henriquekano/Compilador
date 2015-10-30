#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./lexico/analisador.h"
#include "./utils/token.h"
#include "./lexico/transition_table.h"
#include "./sintatico/automataPE.h"
#include "./sintatico/machines.h"

#include "./utils/list.h"

#include "utils/automata2.h"
#include <limits.h>

#define FILENAME "ENTRADA.txt"


int main(){
	FILE *file = fopen(FILENAME, "r");
  Token t;
  Automata automata = automata_create(S0);

  printf("Changed!\n");

	if (file == NULL){
		printf("Arquivo não existe!!!");
  } else {
    do{
      t = find_possible_token(&automata, file);
      token_destroy(&t);
    }while(!reached_eof(file));
	}

  fclose(file);

  AutomataPE aPE;
  init_machines(&aPE);

  // int qualquercoisa = aPE->numberOfMachines;
  // printf("numberOfMachines: %d", qualquercoisa);

  // int i, j;
//   int table1[4][4] = 
//   {
//     {0, 1, 2, FINAL_STATE},
//     {0, 1, 2, ERROR_STATE},
//     {0, 1, 2, 3},
//     {0, 1, 2, 3} 
//   };

//   int table2[4][5] = 
//   {
//     {0, 1, 2, FINAL_STATE, 0},
//     {0, 1, 2, ERROR_STATE, 0},
//     {0, 1, 2, 3, 0},
//     {0, 1, 2, 3, 0} 
//   };
//   int table3[4][4] = 
//   {
//     {0, 1, 2, FINAL_STATE},
//     {0, 1, 2, ERROR_STATE},
//     {0, 1, 2, 3},
//     {0, 1, 2, 3} 
//   };

//   int table4[4][5] = 
//   {
//     {0, 1, 2, FINAL_STATE, 0},
//     {0, 1, 2, ERROR_STATE, 0},
//     {0, 1, 2, 3, 0},
//     {0, 1, 2, 3, 0} 
//   };
//   int table5[4][4] = 
//   {
//     {0, 1, 2, FINAL_STATE},
//     {0, 1, 2, ERROR_STATE},
//     {0, 1, 2, 3},
//     {0, 1, 2, 3} 
//   };

//   int table6[4][5] = 
//   {
//     {0, 1, 2, FINAL_STATE, 0},
//     {0, 1, 2, ERROR_STATE, 0},
//     {0, 1, 2, 3, 0},
//     {0, 1, 2, 3, 0} 
//   };

//   Table t1 = table_create(4, 4, table1);
//   Table t2 = table_create(5, 5, table2);

// Table t3 = table_create(4, 4, table3);
//   Table t4 = table_create(5, 5, table4);

// Table t5 = table_create(4, 4, table5);
//   Table t6 = table_create(5, 5, table6);


//   Table ts1[2] = {t1, t2};
//   Table ts2[2] = {t3, t4};
//   Table ts3[2] = {t5, t6};


  // table_print_table(&(ts[0]));
  // table_print_table(&(ts[1]));


  // List stack;
  // list_new(&stack, sizeof(Automata2), list_destroy_automata2);

  // Automata2 a1 = automata_create2(0, 4, 4, table1);
  // Automata2 a2 = automata_create2(0, 4, 5, table2);
    
  // list_prepend(&stack, &a1);
  // list_prepend(&stack, &a2);

  // Automata2 *a12 = list_get_first(&stack);
  // Automata2 *a22 = list_get_first(&stack);
  // Automata2 *yay = list_get_first(&stack);
  
  // automata_print_table(a12);
  // automata_print_table(a22);

  // printf("satack size: %d", list_size(&stack));
  // if(yay == NULL)
  //   printf("first == null?");
  
  // list_destroy(&stack);

  // table_destroy(&t1);
  // table_destroy(&t2);


  // automataPE_destroy(&aPe);
  
  // automata_print_table(&a);

  // automata_destroy2(&a);

  // if(0 == NULL)
  //   printf("Damn");

  return 0;
}