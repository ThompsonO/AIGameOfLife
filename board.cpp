/*
  Oliver Thompson
  Puzzle1
  board.cpp
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "board.h"

using namespace std;

void read_in_board(TN& root, int& goalx, int& goaly, int& xmax,
                   int& ymax, ifstream& inFile)
{
  char buffer;

  string line;
  int size =0;

  //Gets the first line for the board dimension
  getline(inFile, line);
  for(unsigned int i=0; i<line.length(); i++)
  {
    buffer = line[i];

    //Once the line index hits a space it will assign the accumulated value to
    // the xmax variable for creating the game board
    if(buffer == ' ')
    {
      xmax = size;
      root.xmax = xmax;
      size=0;

      for(unsigned int k=i+1; k<line.length(); k++)
      {
        buffer = line[k];
      	size = size*10;

        if(buffer == '1')
        {
          size += 1;
        }
        if(buffer == '2')
        {
          size += 2;
        }
        if(buffer == '3')
        {
          size += 3;
        }
        if(buffer == '4')
        {
          size += 4;
        }
        if(buffer == '5')
        {
          size += 5;
        }
        if(buffer == '6')
        {
          size += 6;
        }
        if(buffer == '7')
        {
          size += 7;
        }
      	if(buffer == '8')
        {
          size += 8;
        }
      	if(buffer == '9')
        {
          size += 9;
        }
        if(buffer == '0')
        {
          size += 0;
        }

        //Stores the accumulated value in ymax once the line index reaches the
        // end of the line
        if(k == (line.length()-1))
        {
          ymax = size;
          root.ymax = ymax;
        }

        i=k;
      }
    }

    //Makes a left shift by multiplying by 10 until the line index references
    // a space and then stores the accumulated value in xmax
    else
    {
      size = size*10;

      if(buffer == '1')
      {
        size += 1;
      }
      if(buffer == '2')
      {
        size += 2;
      }
      if(buffer == '3')
      {
        size += 3;
      }
      if(buffer == '4')
      {
        size += 4;
      }
      if(buffer == '5')
      {
        size += 5;
      }
      if(buffer == '6')
      {
        size += 6;
      }
      if(buffer == '7')
      {
        size += 7;
      }
      if(buffer == '8')
      {
        size += 8;
      }
      if(buffer == '9')
      {
        size += 9;
      }
      if(buffer == '0')
      {
        size += 0;
      }
    }
  }

  //Gets the second line for the goal coordinates
  size=0;
  getline(inFile, line);
  for(unsigned int i=0; i<line.length(); i++)
  {
    buffer = line[i];

    //Once the line index hits a space it will assign the accumulated value to
    // the goalx variable for referencing the goal state
    if(buffer == ' ')
    {
      goalx = size;
      size=0;

      for(unsigned int k=i+1; k<line.length(); k++)
      {
        buffer = line[k];
      	size = size*10;

        if(buffer == '1')
        {
          size += 1;
        }
        if(buffer == '2')
        {
          size += 2;
        }
        if(buffer == '3')
        {
          size += 3;
        }
        if(buffer == '4')
        {
          size += 4;
        }
        if(buffer == '5')
        {
          size += 5;
        }
        if(buffer == '6')
        {
          size += 6;
        }
        if(buffer == '7')
        {
          size += 7;
        }
      	if(buffer == '8')
        {
          size += 8;
        }
      	if(buffer == '9')
        {
          size += 9;
        }
        if(buffer == '0')
        {
          size += 0;
        }

        //Stores the accumulated value in goaly once the line index reaches the
        // end of the line
        if(k == (line.length()-1))
      	{
          goaly = size;
        }

        i=k;
      }
    }

    //Makes a left shift by multiplying by 10 until the line index references
    // a space and then stores the accumulated value in goalx
    else
    {
      size = size*10;
      if(buffer == '1')
      {
        size += 1;
      }
      if(buffer == '2')
      {
        size += 2;
      }
      if(buffer == '3')
      {
        size += 3;
      }
      if(buffer == '4')
      {
        size += 4;
      }
      if(buffer == '5')
      {
        size += 5;
      }
      if(buffer == '6')
      {
        size += 6;
      }
      if(buffer == '7')
      {
        size += 7;
      }
      if(buffer == '8')
      {
        size += 8;
      }
      if(buffer == '9')
      {
        size += 9;
      }
      if(buffer == '0')
      {
        size += 0;
      }
    }
  }

  //Creates a board in root to read in the initial board state
  root.board = new int* [xmax];
  for(int i=0; i<xmax; i++)
  {
    root.board[i] = new int [ymax];
  }

  //Reads in the original board state from the top down
  for(int k=ymax-1; k>=0; k--)
  {
    if(inFile.good())
    {
      getline(inFile, line);

      for(int i=0; i<xmax; i++)
      {
        buffer = line[i];

        //Stores blank spaces in the board
        if(buffer == '0')
        {
          root.board[i][k]=0;
        }

        //Stores non-player filled cells
        else if(buffer == '1')
        {
          root.board[i][k]=1;
        }

        //Stores the player's starting location in the board and the starting
        // coordinates in locx and locy
        else if(buffer == '2')
        {
          root.board[i][k]=2;
          root.locx = i;
          root.locy = k;
        }
      }
    }
  }

  inFile.close();

  return;
}

