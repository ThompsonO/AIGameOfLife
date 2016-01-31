/*
  Oliver Thompson
  Puzzle1
  main.cpp
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <queue>
#include "tn.cpp"
#include "board.cpp"

using namespace std;

int main(int argc, char* argv[])
{
  ifstream inFile;
  bool goal = false;
  int goalx, goaly, xmax, ymax;
  queue<TN*> search;
  vector<TN*> explored;
  TN* root = new TN(0,0,0,0);
  TN* current;
  char file[1000];

goalx = 0;
goaly = 0;

  //If a puzzle filename is not provided at runtime, the user is prompted to
  // provide one.
  if(argc != 2)
  {
	  cout << "Enter the name of the file to process: ";
	  cout.flush();
	  cin >> file;
	  inFile.open(file, ifstream::in);
  }
  else
  {
    inFile.open(argv[1], ifstream::in); //filename
  }

  //Initializes the root and initial board state as well as the goal coordinates
  read_in_board(*root, goalx, goaly, xmax, ymax, inFile);
  search.push(root);

  //Searches the frontier while the goal state has not been reached.
  while(goal == false  && search.empty() == false)
  {
	  current = search.front();
	  search.pop();
	  (*current).valid_moves(goal, goalx, goaly, search);
    explored.push_back(current);
  }

  //If no solution found
  if(goal == false)
  {
    cout << "No solution" << endl << endl;
  }


  //Deletes all nodes in the frontier
  while(search.empty() == false)
  {
    current = search.front();
    search.pop();
    delete current;
  }

  //Deletes all explored nodes
  while(explored.empty() == false)
  {
    current = explored.back();
    explored.pop_back();
    delete current;
  }

  return 0;
}
