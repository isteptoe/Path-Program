#pragma once
#include "Path.h"

class Item {
public:
   Item(int row = 0, int column = 0, char t = 'O') : type(t) {
      trackPosition = make_pair(row, column);
   }
   int getRow() const { return trackPosition.first; }
   int getColumn()const { return trackPosition.second; }
   bool operator<(const Item a) const {
      if (this->getRow() == a.getRow()) {
         return this->getColumn() > a.getColumn();
      }
      return this->getRow() > a.getRow();
   }
   char getChar() const { return type; }
private:
   pair<int, int> trackPosition;
   char type;
};

class People : public Item {
public:
   People(int row = 0, int column = 0, char t = 'N') : Item(row, column, t) {
      bool isIllegal = false;
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row, column);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row, column + 1);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row, column + 1);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row + 1, column + 1);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row + 1, column + 1);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row + 1, column);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row, column);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row + 1, column);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row, column + 1);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row, column);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row + 1, column + 1);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row, column + 1);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row + 1, column);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row + 1, column + 1);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      for (int j = 0; j < 1; j++) {
         isIllegal = false;
         Point a(row + 1, column);
         for (Point t : firstMoveIllegal) {
            if (t == a) {
               isIllegal = true;
               break;
            }
         }
         if (isIllegal) continue;
         Point b(row, column);
         Move temp(a, b);
         pickupMoves.push_back(temp);
      }
      //test if illegal and remove
   }
   vector<Move> getMoves() const { return pickupMoves; }
private:
   vector<Move> pickupMoves;
};

priority_queue<Item> forPrintingItems(vector<People> a, vector<People> b, vector<Item> c) {
   priority_queue<Item> print;
   for (People p : a) print.emplace(p);
   for (People p2 : b) print.emplace(p2);
   for (Item p3 : c) print.emplace(p3);
   return print;
}