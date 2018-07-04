#pragma once
#include <iostream>
#include <utility>
#include <queue>
#include "dir.h"


class Move {
public:
   Move(Point a, Point b) : one(a), two(b){
      moveDir = direc(a, b);
      int moveRow;
      if (a.getRow() != b.getRow()) {
         moveRow = (a.getRow() < b.getRow() ? b.getRow() * 2 - 1 : a.getRow() * 2 - 1); // multiplies the higher row by 2 and subtracts 1
      }
      else {
         moveRow = a.getRow() * 2; // multiplies either row by 2
      }
      movePos = make_pair(moveRow, (a.getColumn() < b.getColumn()) ? a.getColumn() : b.getColumn()); //gets the lower column, if equal, either one
   }
   bool operator<(const Move a) const {
      if (this->getRow() == a.getRow()) {
         return this->getColumn() > a.getColumn();
      }
      return this->getRow() > a.getRow();
   }
   dir getMoveDir() const { return moveDir; }

   int getRow() const { return movePos.first; }
   int getColumn() const { return movePos.second; }
   Point getOne() { return one; }
   Point getTwo() { return two; }
   Move goNorth(Move a) {
      return Move(a.getTwo(), Point(a.getTwo().getRow() - 1, a.getTwo().getColumn()));
   }
   Move goSouth(Move a) {
      return Move(a.getTwo(), Point(a.getTwo().getRow() + 1, a.getTwo().getColumn()));
   }
   Move goEast(Move a) {
      return Move(a.getTwo(), Point(a.getTwo().getRow(), a.getTwo().getColumn() + 1));
   }
   Move goWest(Move a){
      return Move(a.getTwo(), Point(a.getTwo().getRow(), a.getTwo().getColumn() - 1));
   }
   bool operator==(Move a) {
      return this->getTwo().getColumn() == a.getOne().getColumn() && this->getTwo().getRow() == a.getOne().getRow();
   }

   bool operator!=(Move a) {
      return one != a.one || two != a.two;
   }
   Move switchDir() {
      swap(one, two);
      if (moveDir == NORTH) moveDir = SOUTH;
      else if (moveDir == SOUTH) moveDir = NORTH;
      else if (moveDir == EAST) moveDir = WEST;
      else if (moveDir == WEST) moveDir = EAST;
      return *this;
   }
private:
   pair<int, int> movePos;
   Point one;
   Point two;
   dir   moveDir;
};

Move goNorth(Move a) {
   return Move(a.getTwo(), Point(a.getTwo().getRow() - 1, a.getTwo().getColumn()));
}
Move goSouth(Move a) {
   return Move(a.getTwo(), Point(a.getTwo().getRow() + 1, a.getTwo().getColumn()));
}
Move goEast(Move a) {
   return Move(a.getTwo(), Point(a.getTwo().getRow(), a.getTwo().getColumn() + 1));
}
Move goWest(Move a) {
   return Move(a.getTwo(), Point(a.getTwo().getRow(), a.getTwo().getColumn() - 1));
}

priority_queue<Move> forPrintingMoves(vector<Move> v) {
   priority_queue<Move> print;
   for (Move m : v) {
      print.emplace(m);
   }
   return print;
}



bool isCorner(Move a, Move b) {
   if (a.getMoveDir() != b.getMoveDir()) return true;
   return false;
}

vector<Move> routeTo(Move start, Move end) {
   vector<Move> route;
   vector<Move> temp;
   if (start == end) {
      route.push_back(end);
      return route;
   }
   if (end.getMoveDir() == NORTH || end.getMoveDir() == SOUTH) { // column then row
      if (start.getTwo().getColumn() < end.getOne().getColumn()) {
         route.push_back(goEast(start));
         temp = routeTo(goEast(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
      else if (start.getTwo().getColumn() > end.getOne().getColumn()) {
         route.push_back(goWest(start));
         temp = routeTo(goWest(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
      else if (start.getTwo().getRow() < end.getOne().getRow()) {
         route.push_back(goSouth(start));
         temp = routeTo(goSouth(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
      else if (start.getTwo().getRow() > end.getOne().getRow()) {
         route.push_back(goNorth(start));
         temp = routeTo(goNorth(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
   }
   else {// row then column
      if (start.getTwo().getRow() < end.getOne().getRow()) {
         route.push_back(goSouth(start));
         temp = routeTo(goSouth(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
      else if (start.getTwo().getRow() > end.getOne().getRow()) {
         route.push_back(goNorth(start));
         temp = routeTo(goNorth(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
      else if (start.getTwo().getColumn() < end.getOne().getColumn()) {
         route.push_back(goEast(start));
         temp = routeTo(goEast(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
      else if (start.getTwo().getColumn() > end.getOne().getColumn()) {
         route.push_back(goWest(start));
         temp = routeTo(goWest(start), end);
         route.insert(route.end(), temp.begin(), temp.end());
         temp.clear();
         return route;
      }
   }

   return route;
}