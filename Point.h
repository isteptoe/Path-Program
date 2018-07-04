#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Point {
public:
   Point(int a = 0, int b = 0) {
      row = a;
      column = b;
   }

   int getColumn() const { return column; }
   int getRow() const { return row; }
   bool operator==(const Point a) const {
      return this->row == a.row && this->column == a.column;
   }
   bool operator!=(Point a) {
      return !(*this == a);
   }
private:
   int row;
   int column;
};

const vector<Point> firstMoveIllegal = { Point(0,0), Point(0,1), Point(0,2), Point(0,3), Point(0,4),
Point(1,0),Point(1,4), Point(2,0), Point(2,4),  Point(3,0), Point(3,4), Point(4,0), Point(4,4),
Point(5,0), Point(5,4), Point(6,0), Point(6,4), Point(7,0), Point(7,1), Point(7,3), Point(7,4),
Point(8,0), Point(8,1), Point(8,2), Point(8,3), Point(8,4) };