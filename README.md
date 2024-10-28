Project for Programming in C MSc module. Solve the n-queens puzzle. 

For example, if n = 8 (standard chessboard), what is the maximum number of queens that can be placed on the board such that they do not threaten other queens? No two queens can share the same row, column or diagonal. 

We were required to use a brute-force algorithm to find all possible solutions. 

## Instructions for running on the command line
```
$ ./8q n 
n solutions
```

```
$ ./8q -verbose 6
362514
246135
531642
415263
4 solutions
```

Note: 1 <= n <= 10

## Extension  

I have adapted my code to find solutions for both the N-Queens problem and the related N-Bishops problem. The user can choose between these options on the command line by specifying either "-q" for N-Queens or "-b" for N-Bishops. The user can use the "-verbose" flag to print a summary of the solutions for both queens and bishops.  

### Command line syntax
For a board of size n, to find solutions for: 
- the N-Queens problem, type "./extension n -q" or "./extension n -q -verbose"
- the N-Bishops problem, type "./extension n -b" or "./extension n -b -verbose"

For more information see extension.txt 
