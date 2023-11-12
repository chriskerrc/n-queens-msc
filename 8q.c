/*

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
-string only contains valid characters (this function is not essential)

*/

#include "8q.h"

bool is_invalid_size(int n);
board make_board(int n, char str[MAX_B_SIZE*MAX_B_SIZE+1], int ind); //make parent (ind = 0) or child board from string
char *str_parent(int n);
//bool is_queen(board b, int row, int col, int n);
char *board2str(board b, int n);
void str2board(int index, char inp[MAX_B_SIZE*MAX_B_SIZE+1], board a[MAX_LIST]); //add str to board at index i 
int arg_n(int argc, char *argv[]); //get n from command line and return it 
void test(void);

int main(int argc, char *argv[])
{  
   test();
   int n = arg_n(argc, argv);
   //need to account for verbose flag
   //also test that argv[1] is either an int or the string -verbose: nothing else
 
   static board boards[MAX_LIST];
   
   if(is_invalid_size(n) == true){
      printf("Invalid board size provided. Enter a size between 1-10 (inclusive).\n");
      exit(EXIT_FAILURE); //have I used EXIT_FAILURE correctly? i.e. how is it different to returning 1?
   }
   board p;
   
   char *string1 = str_parent(n);

   p = make_board(n, string1, 0); //create parent board
   for(int row = 0; row < n; row++){    //remove print later
      for(int col = 0; col < n; col++){ 
         printf("%c", p.a[row][col]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Parent board index: %i", p.index);

   char *string2 = board2str(p,n); //get string from parent board 2D array
   printf("String 2:%s\n", string2);
   str2board(0, string2, boards); //add string to parent board (struct) 
   for(int i=0; i<n*n; i++){
      printf("%c", boards[0].str[i]);
   }
   char string3[MAX_B_SIZE*MAX_B_SIZE+1];
   strcpy(string3, string2); //copy string in preparation for creating child board
   printf("String 3: %s\n", string3);
   
   //create child board from string3
   board c;
   c = make_board(n, string3, 1);
   for(int row = 0; row < n; row++){    //remove print later
      for(int col = 0; col < n; col++){ 
         printf("%c", c.a[row][col]);
      }
      printf("\n");
   }
   printf("\n");
   printf("Child board index: %i", c.index);
   
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


board make_board(int n, char str[MAX_B_SIZE*MAX_B_SIZE+1], int ind)
{
   board b;
   b.numqueens = 0;
   b.index = ind;
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

void str2board(int index, char inp[MAX_B_SIZE*MAX_B_SIZE+1], board a[MAX_LIST])
{  
   strcpy(a[index].str, inp); //add string to board at index i  
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
      printf("Incorrect number of command line arguments\n");
      exit(EXIT_FAILURE);
   }
   return n; 
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

   //make_board

   //arg_n
   //HOW DO I TEST THIS FUNCTION? 

}


