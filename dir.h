#pragma once
#include "Point.h"


enum dir {
   NORTH, SOUTH, EAST, WEST
};

dir direc(const Point a, const Point b) { // from a to b
   if (a.getRow() == b.getRow()) { // east or west
      return (a.getColumn() > b.getColumn()) ? WEST : EAST;
   }
   return (a.getRow() < b.getRow()) ? SOUTH : NORTH;
}