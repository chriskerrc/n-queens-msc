#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define MAX_B_SIZE 10 
#define MAX_STR_LEN 100+1
#define MAX_SOL_LEN 10+1
#define MAX_LIST 1000000
#define QUEEN 'Q'
#define BLANK 'X'
#define STEP 1
#define F_ZERO 0

typedef struct board {  
      int a[MAX_B_SIZE][MAX_B_SIZE];
   }board;
