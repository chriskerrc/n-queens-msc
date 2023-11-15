
//remember to adjust makefile according to instructions

#include "8q.h"

//move function definitions to header 
bool is_invalid_size(int n);
board make_board(int n, char str[MAX_B_SIZE*MAX_B_SIZE+1]);
void str_parent(int n, char str[MAX_STR_LEN]);
void board2str(board b, int n, char str2[MAX_B_SIZE*MAX_B_SIZE+1]);
int arg_n(int argc, char *argv[]); //get n from command line and return it 
int arg_verbose(int argc, char *argv[]); //check for -verbose flag
bool is_queen(board b, int row, int col, int n);
bool is_threat_row(board b, int row, int n);
bool is_threat_col(board b, int col, int n);
bool is_threat(board b, int row, int col, int n); //wrapper function for threat functions
bool is_threat_diag(board b, int row, int col, int n);
bool is_threat_diag_br(board b, int row, int col, int n);
bool is_threat_diag_tr(board b, int row, int col, int n);
bool is_threat_diag_bl(board b, int row, int col, int n);
bool is_threat_diag_tl(board b, int row, int col, int n);
bool is_solution(board b, int n); 
board add_queen(board b, int row, int col, int n);
bool is_not_unique(board* b, board* l, int n);
int unique_count(board* b, board boards[MAX_LIST], int n, int e);
void copy_board(board* b, board* c, int n);
int rank_conv(int row, int n);
void print_sol(int n, int sol_cnt);
void test(void);

int main(int argc, char *argv[])
{  
   test();
   int n = arg_n(argc, argv);
   int v = arg_verbose(argc, argv);
   
   static board boards[MAX_LIST];
   
   if(is_invalid_size(n) == true){
      printf("Invalid board size provided. Enter a size between 1-10 (inclusive).\n");
      exit(EXIT_FAILURE);
   }
   board par;
   char str[MAX_STR_LEN]; 
   str_parent(n, str);
   par = make_board(n, str); //create parent board
   
   //add parent board to the front of the list
   copy_board(&par, &boards[F_ZERO], n);
   
   int f = 0;
   int e = 1;
   static int sol_cnt = 0;
   board c;
   int rank = 0;

   while(f<e){ 
      for(int row = 0; row < n; row++){    
         for(int col = 0; col < n; col++){
            //copy parent board to child
            copy_board(&boards[f], &c, n); 
            //print child copy
            c = add_queen(c, row, col, n); //add queen to child
            if(unique_count(&c, boards, n, e)==0){
               copy_board(&c, &boards[e], n);
                  if(is_solution(c, n)==1){
                     sol_cnt++;
                        if(v==1){  
                        for(int col = 0; col < n; col++){ //consider changing this so it prints by string, not int
                           for(int row = 0; row < n; row++){   
                              if(is_queen(c, row, col, n)==1){ 
                                 rank = rank_conv(row, n);
                                 printf("%i", rank);
                              }
                           }
                        } 
                        printf("\n");
                        }        
                  }
                  e++; 
            }   
         }
      }
   f++;
}  
   print_sol(n, sol_cnt);
}

void str_parent(int n, char str[MAX_STR_LEN])
{   
   for(int i=0; i<n*n; i++){
      str[i] = BLANK;
      str[n*n] = '\0';
   }
}


board make_board(int n, char str[MAX_B_SIZE*MAX_B_SIZE+1])
{
   board b;
   int str_index = 0; 

   for(int row = 0; row < n; row++){   
      for(int col = 0; col < n; col++){ 
         b.a[(str_index - col)/n][str_index - row * n] = str[str_index]; //convert 1D string into 2D array
         str_index++;
      }
   }
   return b;
}

bool is_invalid_size(int n)
{
   if(n<1 || n>10){
      return true;
   }
   else{
      return false;
   }
}

void board2str(board b, int n, char str2[MAX_B_SIZE*MAX_B_SIZE+1])
{
   int str_index = 0; 
   for(int row = 0; row < n; row++){   
      for(int col = 0; col < n; col++){ 
         str2[str_index] = b.a[(str_index-col)/n][str_index - row * n]; //convert 2D array to string
         str_index++;
      }
   }
   str2[n*n] = '\0';
}

int arg_n(int argc, char *argv[])
{  
   int n = 0;
   if(argc == 2){
      n = atoi(argv[1]); 
   }
   if(argc == 3){
      n = atoi(argv[2]);
   }
   if(argc != 2 && argc != 3){
      printf("Incorrect number of command line arguments");
      exit(EXIT_FAILURE);
   }
   return n; 
}

int arg_verbose(int argc, char *argv[])
{  
   int v = 0;
   if(argc == 3){
      if(strcmp(argv[1],"-verbose")==0){
         v = 1;
      }
      else{
         printf("If there are three arguments, \"-verbose\" is expected as the 2nd argument");
         v = 0;
         exit(EXIT_FAILURE);
      }
   }
   else{
      return 0;
   }

   return v; 
}

bool is_queen(board b, int row, int col, int n)
{
   if(row >= 0 && col >= 0 && row < n && col < n){
      if(b.a[row][col] == QUEEN){
         return true;
      }
      else{
         return false;
      }
   } 
  return 0;
}

bool is_threat_row(board b, int row, int n) //combine row/col functions?
{
   //check row
   //increment through cols
   for(int c=0; c<n; c++){
      if(is_queen(b, row, c, n)==1){
         return 1; 
      } 
   }
return 0;
}

bool is_threat_col(board b, int col, int n)
{
   //check col 
   //increment through rows 
   for(int r=0; r<n; r++){
      if(is_queen(b, r, col, n)==1){
         return 1;
      }
   }
return 0;
}

bool is_threat_diag(board b, int row, int col, int n)
{
   int br_flag = is_threat_diag_br(b, row, col, n);
   int tr_flag = is_threat_diag_tr(b, row, col, n);
   int bl_flag = is_threat_diag_bl(b, row, col, n);
   int tl_flag = is_threat_diag_tl(b, row, col, n);

   if(br_flag == 1 || tr_flag == 1 || bl_flag == 1 || tl_flag == 1){
      return true;
   }
   else{
      return false;
   }
} 

bool is_threat_diag_br(board b, int row, int col, int n)
{  
   int cnt = 0;
   int j = row;
   int i = col;

   //bottom right diag
   while(i < n && j < n){
      i++;
      j++; 
      if(is_queen(b, j, i, n)==1){
                cnt++;
      } 
   }
   if(cnt > 0){
      return 1;
   }
   else{
      return 0;
   }
}

bool is_threat_diag_tr(board b, int row, int col, int n)
{  
   int cnt = 0;
   int j = row;
   int i = col;

   //bottom right diag
   while(i < n && j >= 0){
      i++;
      j--; 
      if(is_queen(b, j, i, n)==1){
                cnt++;
      } 
   }
   if(cnt > 0){
      return 1;
   }
   else{
      return 0;
   }
}

bool is_threat_diag_tl(board b, int row, int col, int n)
{
   int cnt = 0;
   int j = row;
   int i = col;
   //top left diag
   while(i >= 0 && j >= 0){
      i--; 
      j--;
      if(is_queen(b, j, i, n)==1){
                cnt++;
      } 
   }
   if(cnt > 0){
      return 1;
   }
   else{
      return 0;
   }
}

bool is_threat_diag_bl(board b, int row, int col, int n)
{  
   int cnt = 0;
   int j = row;
   int i = col;
   //bottom left diag 
   while(i >= 0 && j < n){
      i--; 
      j++;
      if(is_queen(b, j, i, n)==1){
                cnt++;
      } 
   }
   if(cnt > 0){
      return 1;
   }
   else{
      return 0;
   }
}


bool is_threat(board b, int row, int col, int n)
{
   int row_flag = is_threat_row(b, row, n);
   int col_flag = is_threat_col(b, col, n);
   int diag_flag = is_threat_diag(b, row, col, n);

   if(row_flag == true || col_flag == true || diag_flag == true){
      return true; 
   }
   else{
      return false;
   }
}

bool is_solution(board b, int n)
{
   int cnt = 0;
   for(int row = 0; row < n; row++){   
      for(int col = 0; col < n; col++){ 
         if(is_queen(b, row, col, n)==1){
            cnt++;
         }
      }
   }
   if(cnt == n){
      return 1; 
   }
   else{
      return 0;
   }
}

board add_queen(board b, int row, int col, int n)
{
   if(is_threat(b, row, col, n)==false && is_queen(b, row, col, n)==false){
      b.a[row][col] = QUEEN;
   }
   return b;
}

void copy_board(board* b, board* c, int n)
{
   for(int row = 0; row < n; row++){   
      for(int col = 0; col < n; col++){
         c->a[row][col] = b->a[row][col];
      }
   }
}

bool is_not_unique(board* b, board* l, int n)
{   
   int cnt = 0;
   for(int row = 0; row < n; row++){   
      for(int col = 0; col < n; col++){ 
         if(l->a[row][col] == b->a[row][col]){
            cnt++;
            if(cnt==n*n){
               return 1;
            }
         }
      }
   }
   return 0;
}

int unique_count(board* b, board boards[MAX_LIST], int n, int e)
{  
   int unique_counter = 0;
   int check = e-1;
     while(check >= 0){ //true
        if(is_not_unique(b, &boards[check], n)==1){    //compare with every other board in list so far back to f0 - better to replace this with a function      
                     unique_counter++;
                     //printf("not unique counter %i\n", unique_counter);
                  }
               check--; 
               }
   return unique_counter;
}

int rank_conv(int row, int n)//maybe store this string in big list
{  
   int rank = 0;
   rank = n-row;
   return rank; 
}

void print_sol(int n, int sol_cnt)
{
   if(n==1){
      printf("%i solution\n", sol_cnt); 
   }
   else{
      printf("%i solutions\n", sol_cnt);
   } 
}
   
void test(void)
{  
   //add assert testing for all written functions
   
   //IS_INVALID_SIZE
   assert(is_invalid_size(-1)==true);
   assert(is_invalid_size(0)==true); //check that '0' size case handled correctly
   assert(is_invalid_size(1)==false); 
   assert(is_invalid_size(2)==false);
   assert(is_invalid_size(3)==false);
   assert(is_invalid_size(4)==false);
   assert(is_invalid_size(5)==false);
   assert(is_invalid_size(6)==false);
   assert(is_invalid_size(7)==false);
   assert(is_invalid_size(8)==false);
   assert(is_invalid_size(9)==false);
   assert(is_invalid_size(10)==false);
   assert(is_invalid_size(11)==true);
  
   //STR_PARENT 
   char str[MAX_STR_LEN];
   str_parent(1, str);
   assert(strcmp(str, "X")==0);
   str_parent(2, str);
   assert(strcmp(str, "XXXX")==0);
   str_parent(3, str);
   assert(strcmp(str, "XXXXXXXXX")==0);
   str_parent(4, str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXX")==0);
   str_parent(5, str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXXXXXXXXXXX")==0);
   str_parent(6, str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")==0);
   str_parent(7, str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")==0);
   str_parent(8, str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")==0);
   str_parent(9, str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")==0);
   str_parent(10, str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")==0);

   //BOARD2STR & MAKE_BOARD
   board b;
   //n=6
   strcpy(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"); //might be a more concise way of testing this
   str_parent(6, str);
   //printf("string after str_parent:%s\n", str);
   b = make_board(6, str);
   board2str(b, 6, str);
   //printf("string after board2str:%s\n", str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")==0);
   
   //n=4
   strcpy(str, "XXXXXXXXXXXXXXXX"); //might be a more concise way of testing this
   str_parent(4, str);
   //printf("string after str_parent:%s\n", str);
   b = make_board(4, str);
   board2str(b, 4, str);
   //printf("string after board2str:%s\n", str);
   assert(strcmp(str, "XXXXXXXXXXXXXXXX")==0);
   
   //IS_QUEEN
   
   //queen
   strcpy(str, "XXQXXXXXX");
   b = make_board(3, str);
   assert(is_queen(b, 0, 2, 3)==1);
   
   //no queen
   strcpy(str, "XXXXXXXXX");
   b = make_board(3, str);
   assert(is_queen(b, 0, 2, 3)==0);
   
   //IS_THREAT_ROW
   
   //threat
   strcpy(str, "XXQXXXXXX");
   b = make_board(3, str); 
   assert(is_threat_row(b, 0, 3)==1);
   
   //no threat
   strcpy(str, "XXQXXXXXX");
   b = make_board(3, str); 
   assert(is_threat_row(b, 1, 3)==0);

   //IS_THREAT_COL

   //threat
   strcpy(str, "XXXXXXXXXQXXXXXX");
   b = make_board(4, str); 
   assert(is_threat_col(b, 1, 4)==1);
   
   //no threat
   strcpy(str, "XXXXXXXXXQXXXXXX");
   b = make_board(4, str); 
   assert(is_threat_col(b, 3, 4)==0);
 
   //IS_THREAT_DIAG_BR

   //threat
   strcpy(str, "XXXXXXXXXQXXXXXX");
   b = make_board(4, str); 
   assert(is_threat_diag_br(b, 1, 0, 4)==1); 

   //no threat 
   strcpy(str, "XXXXXXXXXQXXXXXX");
   b = make_board(4, str); 
   assert(is_threat_diag_br(b, 0, 0, 4)==0); 

   //IS_THREAT_DIAG_TR
  
   //threat
   strcpy(str, "XXXXXXXXXQXXXXXX");
   b = make_board(4, str); 
   assert(is_threat_diag_tr(b, 0, 0, 4)==0); 

   //no threat 
   
   strcpy(str, "XXQXXXXXX");  
   b = make_board(3, str); 
   assert(is_threat_diag_tr(b, 1, 0, 3)==0); 

   //strcpy(str, "XQXX"); 
   //b = make_board(2, str); 
   //assert(is_threat_diag_tr(b, 1, 0, 2)==1); 
   
   
   //IS_THREAT_DIAG_BL
   
   //threat
   strcpy(str, "XXXXXXXXXQXXXXXX");  
   b = make_board(4, str); 
   assert(is_threat_diag_bl(b, 1, 2, 4)==1); 

   //no threat 
   strcpy(str, "XXXXXXXXXQXXXXXX");  
   b = make_board(4, str); 
   assert(is_threat_diag_bl(b, 2, 3, 4)==0); 

   //IS_THREAT_DIAG_TL
   
   //threat 
   
   strcpy(str, "XXXXXXXXXQXXXXXX");  
   b = make_board(4, str); 
   assert(is_threat_diag_tl(b, 3, 2, 4)==1);  

   //no threat 

   strcpy(str, "XXXXXXXXXQXXXXXX");  
   b = make_board(4, str); 
   assert(is_threat_diag_tl(b, 1, 2, 4)==0);  

   //IS_THREAT_DIAG

   //threat 
   strcpy(str, "XXXXXQXXXQXXXXXQXXXQXXXXX"); 
   b = make_board(5, str); 
   assert(is_threat_diag(b, 2, 1, 5)==1); 
   
   //no threat 
   strcpy(str, "XXXXXQXXXQXXXXXQXXXQXXXXX"); 
   b = make_board(5, str); 
   assert(is_threat_diag(b, 4, 2, 5)==0); 

   //add more tests TO DO

   //IS_THREAT
   
   //threat
   strcpy(str, "XXXXXQXXXQXXXXXQXXXQXXXXX"); 
   b = make_board(5, str); 
   assert(is_threat(b, 2, 1, 5)==1); 
   
   strcpy(str, "XXQX"); 
   b = make_board(2, str); 
   assert(is_threat(b, 0, 1, 2)==1); 
   
   //strcpy(str, "XQXX"); 
   //b = make_board(2, str); 
   //assert(is_threat(b, 1, 0, 2)==1); 
   
   //no threat 
   strcpy(str, "XXXXXQXXXQXXXXXQXXXQXXXXX"); 
   b = make_board(5, str); 
   assert(is_threat(b, 4, 2, 5)==0); 
   
   //add more tests TO DO

   //IS_SOLUTION
   
   //solution n = 4
   strcpy(str, "XQXXXXXQQXXXXXQX"); 
   b = make_board(4, str); 
   assert(is_solution(b, 4)==1); 

   //solution n = 8
   strcpy(str, "QXXXXXXXXXXXXXQXXXXXQXXXXXXXXXXQXQXXXXXXXXXQXXXXXXXXQXXXXQXXXXX"); 
   b = make_board(8, str); 
   assert(is_solution(b, 8)==1); 

   //not solution n = 8
   strcpy(str, "QXXXXXXXXXXXXXXXXXXXQXXXXXXXXXXQXQXXXXXXXXXQXXXXXXXXQXXXXQXXXXX"); 
   b = make_board(8, str); 
   assert(is_solution(b, 8)==0); 

   //solution n = 4
   strcpy(str, "XQXXXXXQQXXXXXXX"); 
   b = make_board(4, str); 
   assert(is_solution(b, 4)==0); 
   
   //BOARD_ADD_QUEEN
   
   //add queen to empty board
   strcpy(str, "XXXXXXXXXXXXXXXX"); 
   b = make_board(4, str); 
   b = add_queen(b, 0, 0, 4);
   board2str(b, 4, str);
   assert(strcmp(str, "QXXXXXXXXXXXXXXX")==0);

   //add queen to board with other queens in non-threatening position
   strcpy(str, "XXXXXQXXX"); 
   b = make_board(3, str); 
   b = add_queen(b, 2, 0, 3);
   board2str(b, 3, str);
   assert(strcmp(str, "XXXXXQQXX")==0);

   //try to add queen on top of other queen
   strcpy(str, "XXXXXQXXX"); 
   b = make_board(3, str); 
   b = add_queen(b, 1, 2, 3);
   board2str(b, 3, str);
   assert(strcmp(str, "XXXXXQXXX")==0);
   
   //try to add queen in threatening position
   strcpy(str, "XXXXXQXXX"); 
   b = make_board(3, str); 
   b = add_queen(b, 1, 0, 3);
   board2str(b, 3, str);
   assert(strcmp(str, "XXXXXQXXX")==0);
   
   //NOT_UNIQUE
   board c;

   //two identical boards
   strcpy(str, "QXQXXQXXQ"); 
   b = make_board(3, str); 
   strcpy(str, "QXQXXQXXQ"); 
   c = make_board(3, str); 
   assert(is_not_unique(&b, &c, 3)==1); 
   
   //two different boards n = 4
   strcpy(str, "QXQXXXXXXXXXXXXX"); 
   b = make_board(4, str); 
   strcpy(str, "QXQXXXXXXXXXQXXX"); 
   c = make_board(4, str); 
   assert(is_not_unique(&b, &c, 4)==0); 

   //two different boards n = 8 different last char
   strcpy(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"); 
   b = make_board(8, str); 
   strcpy(str, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXQ"); 
   c = make_board(8, str); 
   assert(is_not_unique(&b, &c, 8)==0); 

   //COPY BOARD 
   //n=3
   strcpy(str, "QXQXXQXXQ"); 
   b = make_board(3, str); 
   copy_board(&b, &c, 3); 
   board2str(c, 3, str);
   assert(strcmp(str, "QXQXXQXXQ")==0);

   //ARG_N
   //HOW DO I TEST THIS FUNCTION? 
   
}


