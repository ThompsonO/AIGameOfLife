/*
Oliver Thompson
Puzzle1
tn.cpp
*/

#include <queue>
#include <stack>
#include <cstdlib>
#include <iostream>

#include "tn.h"
using namespace std;

TN::TN(int move, int cost, int x, int y, int** spaces, int xMax, int yMax)
{
  //Copies the parameters into the member variables
  action = move;
  locx = x;
  locy = y;
  pathCost = cost;
  xmax = xMax;
  ymax = yMax;

  //Copies the spaces double pointer into the board
  board = new int* [xmax];
  for(int i=0; i<xmax; i++)
  {
    board[i] = new int [ymax];
  }

  for(int i=0; i<xmax; i++)
  {
    for(int k=0; k<ymax; k++)
    {
      board[i][k] = spaces[i][k];
    }
  }

  //Sets everything else to null
  p = NULL;
  n = NULL;
  e = NULL;
  s = NULL;
  w = NULL;
  ne = NULL;
  se = NULL;
  sw = NULL;
  nw = NULL;
  stay = NULL;
}


TN::TN(int move, int cost, int x, int y)
{
  //Copies the parameters into the member variables
  action = move;
  locx = x;
  locy = y;
  pathCost = cost;

  //Sets everything else to null
  board = NULL;
  p = NULL;
  n = NULL;
  e = NULL;
  s = NULL;
  w = NULL;
  ne = NULL;
  se = NULL;
  sw = NULL;
  nw = NULL;
  stay = NULL;
}


TN& TN::operator=(const TN& rhs)
{
  //All member variables and pointer locations are copied.
  p = rhs.p;
  nw = rhs.nw;
  n = rhs.n;
  ne = rhs.ne;
  e = rhs.e;
  se = rhs.se;
  s = rhs.s;
  sw = rhs.sw;
  w = rhs.w;
  stay = rhs.stay;
  action = rhs.action;
  locx = rhs.locx;
  locy = rhs.locy;
  pathCost = rhs.pathCost;
  board = rhs.board;

  return *this;
}


TN::~TN()
{
  //Deletes the node's board
  if(board != NULL)
  {
    for(int i=0; i<xmax; i++)
    {
      delete [] board[i];
    }

    delete [] board;
    board = NULL;
  }
}


void TN::board_update()
{
    //Creates a table to store the number of neighbors for each space
    int** neighbors = new int* [xmax];

    for(int i=0; i<xmax; i++)
    {
      neighbors[i] = new int [ymax];
    }

	//Populates the neighbors table with the number of adjacent 1's and 2's for
	// each board space
    for(int i=0; i<xmax; i++)
    {
      for(int k=0; k<ymax; k++)
      {
        neighbors[i][k] = find_neighbors(i,k);
      }
    }

    //Updates the board according to the game rules
    for(int i=0; i<xmax; i++)
    {
      for(int k=0; k<ymax; k++)
      {
        if(board[i][k] == 0 && neighbors[i][k] == 3)
        {
          board[i][k] = 1;
        }

        else if(board[i][k] == 1 && neighbors[i][k] != 2 && neighbors[i][k] != 3)
        {
          board[i][k] = 0;
        }
      }
    }

	//Deletes the neighbors board
    for(int i=0; i<xmax; i++)
    {
      delete [] neighbors[i];
    }

    delete [] neighbors;

  return;
}


bool TN::goal_check(int goalx, int goaly)
{
  if(locx == goalx && locy == goaly)
  {
    return true;
  }

  else
  {
    return false;
  }
}


void TN::print_solution()
{
  TN* temp = this;
  stack<TN*> path;

  //Pushes nodes onto the stack until temp is pointing at the root.
  while(temp->p != NULL)
  {
    path.push(temp);
    temp = temp->p;
  }

 //Prints the coordinates and board state of each node until the stack is empty
  while(path.empty() == false)
  {
    cout<< "Coordinates: (" << (*temp).locx << "," << (*temp).locy 
	    << ")" << endl;

	//Prints the board state
    cout<< "Board State:" << endl;
    for(int k=ymax-1; k>=0; k--)
    {
      for(int i=0; i<xmax; i++)
      {
        cout<< (*temp).board[i][k];
      }
      cout<< endl;
    }

    cout<< endl;

	//Sets up temp for the next iteration
    temp = path.top();
    path.pop();
  }

  //Prints out the coordinates and board state of the goal node
  cout<< "Coordinates: (" << (*temp).locx << "," << (*temp).locy << ")" << endl;

  cout<< "Board State:" << endl;
  for(int k=ymax-1; k>=0; k--)
  {
    for(int i=0; i<xmax; i++)
    {
      cout<< (*temp).board[i][k];
    }
    cout<< endl;
  }

  cout << endl;

  //Prints out the total path cost of the solution
  cout << "Path Cost: " << (*temp).pathCost << endl << endl;

  return;
}


int TN::find_neighbors(int x, int y)
{
  int neigh = 0;

  //Looks for northwest neighbor
  if(x > 0 && y < ymax-1)
  {
    if(board[x-1][y+1] == 1 || board[x-1][y+1] == 2)
    {
      neigh++;
    }
  }

  //Looks for north neighbor
  if(y < ymax-1)
  {
    if(board[x][y+1] == 1 || board[x][y+1] == 2)
    {
      neigh++;
    }
  }

  //Looks for northeast neighbor
  if(x < xmax-1 && y < ymax-1)
  {
    if(board[x+1][y+1] == 1 || board[x+1][y+1] == 2)
    {
      neigh++;
    }
  }

  //Looks for east neighbor
  if(x < xmax-1)
  {
    if(board[x+1][y] == 1 || board[x+1][y] == 2)
    {
      neigh++;
    }
  }

  //Looks for southeast neighbor
  if(x < xmax-1 && y > 0)
  {
    if(board[x+1][y-1] == 1 || board[x+1][y-1] == 2)
    {
      neigh++;
    }
  }

  //Looks for south neighbor
  if(y > 0)
  {
    if(board[x][y-1] == 1 || board[x][y-1] == 2)
    {
      neigh++;
    }
  }

  //Looks for southwest neighbor
  if(x > 0 && y > 0)
  {
    if(board[x-1][y-1] == 1 || board[x-1][y-1] == 2)
    {
      neigh++;
    }
  }

  //Looks for west neighbor
  if(x > 0)
  {
    if(board[x-1][y] == 1 || board[x-1][y] == 2)
    {
      neigh++;
    }
  }

  return neigh;
}


void TN::valid_moves(bool& goal, int goalx, int goaly, queue<TN*>& search)
{

  //A move in the northwest direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locx != 0 && locy != ymax-1)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx-1][locy+1] ==0 && 
        ((find_neighbors(locx-1, locy+1)-1) == 2 ||
         (find_neighbors(locx-1, locy+1)-1) == 3))
      {
        //Creates the node
        nw = new TN(1, pathCost+1, locx-1, locy+1, board, xmax, ymax);
        (*nw).p = this;

        //Makes the player move and updates the board to the next state
        nw->board[locx][locy] = 0;
	      nw->board[locx-1][locy+1] = 2;
        (*nw).board_update();

        //Checks if the new node is the goal state
        goal = (*nw).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*nw).print_solution();
        }

		//Pushes a pointer to the node onto the queue
        search.push(nw);
      }
    }
  }


  //A move in the north direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locy != ymax-1)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx][locy+1] ==0 && 
        ((find_neighbors(locx, locy+1)-1) == 2 ||
         (find_neighbors(locx, locy+1)-1) == 3))
      {
        //Creates the node
        n = new TN(2, pathCost+1, locx, locy+1, board, xmax, ymax);
        (*n).p = this;

		//Makes the player move and updates the board to the next state
	    n->board[locx][locy] = 0;
	    n->board[locx][locy+1] = 2;
        (*n).board_update();

		//Checks if the new node is the goal state
        goal = (*n).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*n).print_solution();
        }

        //Pushes a pointer to the node onto the queue
        search.push(n);
      }
    }
  }


  //A move in the northeast direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locx != xmax-1 && locy != ymax-1)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx+1][locy+1] ==0 && 
        ((find_neighbors(locx+1, locy+1)-1) == 2 ||
         (find_neighbors(locx+1, locy+1)-1) == 3))
      {

        //Creates the node
        ne = new TN(3, pathCost+1, locx+1, locy+1, board, xmax, ymax);
        (*ne).p = this;

        //Makes the player move and updates the board to the next state
        ne->board[locx][locy] = 0;
        ne->board[locx+1][locy+1] = 2;
        (*ne).board_update();

        //Checks if the new node is the goal state
        goal = (*ne).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*ne).print_solution();
        }

        //Pushes a pointer to the node onto the queue
        search.push(ne);
      }
    }
  }

  //A move in the east direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locx != xmax-1)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx+1][locy] ==0 && 
        ((find_neighbors(locx+1, locy)-1) == 2 ||
         (find_neighbors(locx+1, locy)-1) == 3))
      {
        //Creates the node
        e = new TN(4, pathCost+1, locx+1, locy, board, xmax, ymax);
        (*e).p = this;

        //Makes the player move and updates the board to the next state
        e->board[locx][locy] = 0;
        e->board[locx+1][locy] = 2;
        (*e).board_update();

        //Checks if the new node is the goal state
        goal = (*e).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*e).print_solution();
        }

        //Pushes a pointer to the node onto the queue
        search.push(e);
      }
    }
  }

  //A move in the southeast direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locx != xmax-1 && locy != 0)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx+1][locy-1] ==0 && 
        ((find_neighbors(locx+1, locy-1)-1) == 2 ||
         (find_neighbors(locx+1, locy-1)-1) == 3))
      {
        //Creates the node
        se = new TN(5, pathCost+1, locx+1, locy-1, board, xmax, ymax);
        (*se).p = this;

		//Makes the player move and updates the board to the next state
        se->board[locx][locy] = 0;
        se->board[locx+1][locy-1] = 2;
        (*se).board_update();

        //Checks if the new node is the goal state
        goal = (*se).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*se).print_solution();
        }

        //Pushes a pointer to the node onto the queue
        search.push(se);
      }
    }
  }

  //A move in the south direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locy != 0)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx][locy-1] ==0 && 
        ((find_neighbors(locx, locy-1)-1) == 2 ||
         (find_neighbors(locx, locy-1)-1) == 3))
      {
        //Creates the node
        s = new TN(6, pathCost+1, locx, locy-1, board, xmax, ymax);
        (*s).p = this;

        //Makes the player move and updates the board to the next state
        s->board[locx][locy] = 0;
        s->board[locx][locy-1] = 2;
        (*s).board_update();

        //Checks if the new node is the goal state
        goal = (*s).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*s).print_solution();
        }

        //Pushes a pointer to the node onto the queue
        search.push(s);
      }
    }
  }

  //A move in the southwest direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locx != 0 && locy != 0)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx-1][locy-1] ==0 && 
        ((find_neighbors(locx-1, locy-1)-1) == 2 ||
         (find_neighbors(locx-1, locy-1)-1) == 3))
      {
        //Creates the node
        sw = new TN(7, pathCost+1, locx-1, locy-1, board, xmax, ymax);
        (*sw).p = this;

        //Makes the player move and updates the board to the next state
        sw->board[locx][locy] = 0;
        sw->board[locx-1][locy-1] = 2;
        (*sw).board_update();

        //Checks if the new node is the goal state
        goal = (*sw).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*sw).print_solution();
        }

        //Pushes a pointer to the node onto the queue
        search.push(sw);
      }
    }
  }

  //A move in the west direction
  if(goal == false)
  {
    //Checks that the space exists
    if(locx != 0)
    {
      //Checks that the space is empty and has sufficient neighbors
      if(board[locx-1][locy] ==0 && 
        ((find_neighbors(locx-1, locy)-1) == 2 ||
         (find_neighbors(locx-1, locy)-1) == 3))
      {
        //Creates the node
        w = new TN(8, pathCost+1, locx-1, locy, board, xmax, ymax);
        (*w).p = this;

        //Makes the player move and updates the board to the next state
        w->board[locx][locy] = 0;
        w->board[locx-1][locy] = 2;
        (*w).board_update();

        //Checks if the new node is the goal state
        goal = (*w).goal_check(goalx, goaly);

        if(goal == true)
        {
          (*w).print_solution();
        }

        //Pushes a pointer to the node onto the queue
        search.push(w);
      }
    }
  }

  //A move where the player remains stationary
  if(goal == false)
  {
    //Checks that the space has sufficient neighbors
    if((find_neighbors(locx, locy)) == 2 ||
       (find_neighbors(locx, locy)) == 3)
    {
      //Creates the node
      stay = new TN(9, pathCost+1, locx, locy, board, xmax, ymax);
      (*stay).p = this;

      //Updates the board to the next state
      (*stay).board_update();

      //A goal check here is redundant but included anyway to be thurough
      goal = (*stay).goal_check(goalx, goaly);

      if(goal == true)
      {
        (*stay).print_solution();
      }

        //Pushes a pointer to the node onto the queue
        search.push(stay);
    }
  }

  return;
}

