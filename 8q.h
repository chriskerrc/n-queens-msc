#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define MAX_B_SIZE 10 
#define MAX_STR_LEN 100+1
#define MAX_LIST 1000000
#define QUEEN 'Q'
#define BLANK 'X'

typedef struct board {  
      int a[MAX_B_SIZE][MAX_B_SIZE];
      char str[MAX_B_SIZE*MAX_B_SIZE+1];
      int numqueens;
      int index;
      int issolution;
   }board;
