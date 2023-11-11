#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define MAX_B_SIZE 10 
#define MAX_STR_LEN 100+1
#define QUEEN 'Q'
#define BLANK 'X'

typedef struct board {  
      int cells[MAX_B_SIZE][MAX_B_SIZE];
      int numqueens;
      int index;
      int issolution;
   }board;
