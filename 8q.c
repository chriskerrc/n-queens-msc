/*
   
   Scan for user's arguments on command line: 
   -Standard? - only print number of solutions
   -Verbose? - print number of solutions + numerical summary of solutions
   Create a big list of hash defined length (big enough to handle 10x10 case) 
       This list is an array of structures, each structure containing data for a board 
       Structure contains: 
       -width and height (w=h always)
       -board (2D array of chars in of width w and height h) 
       -pointer 

   Create an empty board of 10x10 (then use a subset of this board) 
   
   Add the empty board to the front of the list at f=0

   Find the resulting child boards of this parent
      Create a child board somewhere (outside of list) 
      Place queen in top left
      Is this board unique? If yes, add board to end of list at location e. Update location e. If no, do nothing
      Is this board a solution? If yes, pass summary to print summary function and increment counter. If no, do nothing 
      Create 2nd child board
      Place queen in next square
      Ask questions again
      Keep creating child boards until no more queens can be added 
    
   Add one to f, if there are more boards in list (check this with a function), loop to finding child boards
     
   When finished (what is finish condition), print according to command line argument

[create 10 x 10 2D array by default in your board structure, then fill some of it. This way, you don't need to malloc space] 


LIST OF FUNCTIONS

-make empty board based on argument on command line (subset of 10x10)
-add empty board to very start of list
-add child board to end of list
-print solution e.g. 362514 (for verbose option)
-compare boards with others in list: is identical? - boolean function (use string compare?)
-add queen to given square, without threatening other queens? 
-is board a solution i.e. does n Qs = w = h? 
-standard or verbose (check command line input)?
   -only allow numbers 1-10 and separate verbose flag 
-is there a queen already in a given square?
-are we at the end of the list?
-board to string 
-value is other than 1-10? 



NUMBER OF SOLUTIONS

n=1 sol=1
n=2 sol=0
n=3 sol=0
n=4 sol=2
n=5 sol=10
n=6 sol=4
n=7 sol=40
n=8 sol=92
n=9 sol=352
n=10 sol=724

*/

#include "8q.h"

board board_parent(int n, const char str[MAX_B_SIZE*MAX_B_SIZE+1]);
const char *str_parent(int n);

int main(void)//int main(int argc, char *argv[])
{  
   int n = 8; //will get this from command line later
   board b;
   
   const char *string = str_parent(n);

   b = board_parent(n, string);
   for(int row = 0; row < n; row++){    //remove print later
      for(int col = 0; col < n; col++){ 
         printf("%c", b.cells[row][col]);
      }
      printf("\n");
   }
   printf("\n");
}

const char *str_parent(int n) // stop this function accepting values other than 1-10
{   
   static char str[MAX_STR_LEN]; 
   for(int i=0; i<n*n; i++){
      str[i] = BLANK;
   }
   printf("%s\n", str); //remove print later
   return str;
}


board board_parent(int n, const char str[MAX_B_SIZE*MAX_B_SIZE+1]) // stop this function accepting values other than 1-10
{
   board b;
   b.numqueens = 0;
   b.index = 0;
   b.issolution = 0; 
   int str_index = 0; 

   for(int row = 0; row < n; row++){   
      for(int col = 0; col < n; col++){ 
         b.cells[(str_index - col)/n][str_index - row * n] = str[str_index]; //convert 1D   string into 2D array
         str_index++;
      }
   }
   return b;
}

