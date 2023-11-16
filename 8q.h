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
#define EMPTY 'X'
#define STEP 1
#define F_ZERO 0
#define NULL_CHAR '\0'
#define END_STEP 1
#define TEN_CHAR 'A'
#define FIRST_INDEX 0
#define END_INDEX 1

typedef struct board {  
      int a[MAX_B_SIZE][MAX_B_SIZE];
   }board;

bool is_invalid_size(int n);
board make_board(int n, char str[MAX_B_SIZE*MAX_B_SIZE+1]);
void str_parent(int n, char str[MAX_STR_LEN]);
void board2str(board b, int n, char str2[MAX_B_SIZE*MAX_B_SIZE+1]);
int get_arg_n(int argc, char *argv[]); 
int get_arg_verbose(int argc, char *argv[]);
bool is_queen(board b, int row, int col, int n);
bool is_threat(board b, int row, int col, int n);
bool is_threat_row(board b, int row, int n);
bool is_threat_col(board b, int col, int n);
bool is_threat_diag(board b, int row, int col, int n);
bool is_threat_diag_br(board b, int row, int col, int n);
bool is_threat_diag_tr(board b, int row, int col, int n);
bool is_threat_diag_bl(board b, int row, int col, int n);
bool is_threat_diag_tl(board b, int row, int col, int n);
bool is_solution(board b, int n); 
board add_queen(board b, int row, int col, int n);
bool is_not_unique(board* b, board* list, int n);
int unique_count(board* b, board boards[MAX_LIST], int n, int end);
void copy_board(board* b, board* child, int n);
int row2rank(int row, int n);
void print_rank(int rank);
void print_sol(int n, int sol_cnt);
void test(void);
