Programmer: Oliver Thompson

This code was compiled with the:

cl /EHsc main.cpp

command line in the Visual Studio developer command line.



It was run through the Visual Studio developer command line with:

main filename

where "filename" is the name of the .txt file that contains the
puzzle to be solved (running larger puzzles, such as Puzzle4 and
Puzzle 5, may cause the program to crash due to the amount of
memory required to compute the answer).



This code was created in a series of assignments that focused on
developing A.I. to play an interactive version of Conway's
Game of Life.

The rules for Conway's Game of Life are as follows:

1. Any occupied space with fewer than 2 neighbors becomes unoccupied.
2. Any occupied space with 2 or 3 neighbors remains occupied.
3. Any occupied space with more than 3 neighbors becomes unoccupied.
4. Any unoccupied space with exactly 3 neighbors becomes occupied.

In the modified version of the Game of Life, the A.I. controls a cell
that it can dictate what direction to move it with the objective to
survive while reaching a given goal space on the board.  The A.I.
controlled cell functions under the same rules as all other cells.



The program reads in a text file that specifies the initial board
state and the goal state for the A.I.

The first line has two numbers separated by a space which represents
the size of the board in x,y coordinates.

The second line has two numbers separated by a space which represents
the x,y coordinate of the goal space, with the coordinate 0,0 being
the lower left-hand corner.

The rest of the file is the initial board state with 0's representing
unoccupied spaces, 1's are non-A.I. occupied spaces, and 2 is the
A.I. controlled cell.

An example follows (This is Puzzle3.txt):

11 7
10 3
01110001000
20001111100
01000110110
01000110111
00011110110
00000111100
00000001000



The A.I. utilizes a breadth first tree search until it finds the first
branch that places the A.I.'s cell in the goal space.  Upon reaching
the goal the program prints each board state from the given initial
state to the goal and prints the number of moves required for the
solution.