/* -make empty board based on argument on command line (subset of 10x10)
-add empty board to very start of list
-add child board to end of list
-calculate+print solution e.g. 362514 (for verbose option)
-compare boards with others in list: is identical? - boolean function (use string compare?)
-add queen to given square, without threatening other queens? 
-is board a solution i.e. does n Qs = w = h? 
-standard or verbose (check command line input)?
   -only allow numbers 1-10 and separate verbose flag 
-is there a queen already in a given square?
-are we at the end of the list?
-board to string
-string only contains valid characters
*/

#include "8q.h"

bool is_invalid_size(int n);
board board_parent(int n, char str[MAX_B_SIZE*MAX_B_SIZE+1]);
char *str_parent(int n);
//bool is_queen(board b, int row, int col, int n);
char *board2str(board b, int n);
void test(void);

int main(void)//int main(int argc, char *argv[])
{  
   test();
   int n = 3; //will get this from command line later

   board static boards[MAX_LIST];
   
   if(is_invalid_size(n) == true){
      printf("Invalid board size provided. Enter a size between 1-10 (inclusive).\n");
      exit(EXIT_FAILURE); //have I used EXIT_FAILURE correctly? i.e. how is it different to returning 1?
   }
   board b;
   
   char *string = str_parent(n);

   b = board_parent(n, string);
   for(int row = 0; row < n; row++){    //remove print later
      for(int col = 0; col < n; col++){ 
         printf("%c", b.a[row][col]);
      }
      printf("\n");
   }
   printf("\n");

   char *string2 = board2str(b,n);
   printf("String 2:%s\n", string2);
   strcpy(boards[0].str, string2); //add string to board 0
   
   for(int i=0; i<n*n; i++){
      printf("%c", boards[0].str[i]);
   }

   return EXIT_SUCCESS;
}

char *str_parent(int n)
{   
   static char str[MAX_STR_LEN]; 
   for(int i=0; i<n*n; i++){
      str[i] = BLANK;
   }
   printf("%s\n", str); //remove print later
   return str;
}


board board_parent(int n, char str[MAX_B_SIZE*MAX_B_SIZE+1])
{
   board b;
   b.numqueens = 0;
   b.index = 0;
   b.issolution = 0; 
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

char *board2str(board b, int n)
{
   int str_index = 0; 
   static char str2[MAX_B_SIZE*MAX_B_SIZE+1];
   for(int row = 0; row < n; row++){   
      for(int col = 0; col < n; col++){ 
         str2[str_index] = b.a[(str_index-col)/n][str_index - row * n]; //convert 2D array to string
         str_index++;
      }
   }
   return str2;
}

void test(void)
{  
   //add assert testing for all written functions
   
   //is_invalid_size 
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

   //str_parent

   //board_parent

}


