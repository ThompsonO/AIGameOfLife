/*
  Oliver Thompson
  Puzzle1
  board.h

  Function: void read_in_board(TN& root, int goalx, int goaly)
  Reads in the Maze of Life board from a text file specified in the command line.

    Parameters:
    root - A tree node that will be the starting position of the board.
    goalx - Will store the x-coordinate of the goal in the passed variable.
    goaly - Will store the y-coordinate of the goal in the passed variable.
*/

#ifndef BFS_H
#define BFS_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "tn.h"


void read_in_board(TN& root, int& goalx, int& goaly, int& xmax, 
                   int& ymax, ifstream& inFile);

#endif
