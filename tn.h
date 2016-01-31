/*
  Oliver Thompson
  Puzzle1
  tn.h
*/

#ifndef TN_H
#define TN_H

#include <queue>
using namespace std;


class TN
{
 public:
  TN(int move, int cost, int x, int y, int** spaces, int xMax, int yMax);
  TN(int move, int cost, int x, int y);
  TN& operator=(const TN& rhs);
  ~TN ();

  //Finds all directions that are legal moves given the board in the node
  void valid_moves(bool& goal, int goalx, int goaly, queue<TN*>& search);

  //Updates the board in the node to the next game state given that the player
  // remains in the same position on the board.
  void board_update();

  //Checks if the tree node's current location is the goal location.
  bool goal_check(int goalx, int goaly);

  //Prints the path from the root to the current node
  void print_solution();

  //Finds the number of neighbors of the given (x,y) point in the node's board.
  int find_neighbors(int x, int y);

  TN* p;
  TN* n;
  TN* e;
  TN* s;
  TN* w;
  TN* ne;
  TN* se;
  TN* sw;
  TN* nw;
  TN* stay;
  int action, locx, locy;
  int pathCost;
  int xmax, ymax;
  int** board;
};

#endif

