#pragma once
#include "People.h"
#include <iomanip>

void fillMission(vector<People>& redPeople, vector<People>& neutPeople, vector<Item>& obs, int missionNum = 0) {

   if (missionNum == 1) {
      redPeople.push_back(People(2, 1, 'R'));
      redPeople.push_back(People(5, 1, 'R'));
      redPeople.push_back(People(4, 3, 'R'));

      neutPeople.push_back(People(1, 0, 'N'));
      neutPeople.push_back(People(4, 0, 'N'));
      neutPeople.push_back(People(0, 3, 'N'));
      neutPeople.push_back(People(1, 2, 'N'));

      obs.push_back(Item(3, 0, 'O'));
      obs.push_back(Item(2, 2, 'O'));
      obs.push_back(Item(4, 2, 'O'));
      return;
   }

   string positionString;
   char columnchar = ' ';
   int column = -1;
   int row = -1;

   cout << "Enter positions of red people" << endl;
   for (int i = 0; i < 3; i++) {
      cout << i + 1 << ": ";
      cin >> positionString;
      sscanf(positionString.c_str(), "%c%i", &columnchar, &row);
      row--;
      columnchar = toupper(columnchar);
      if (columnchar == 'A') column = 0;
      else if (columnchar == 'B') column = 1;
      else if (columnchar == 'C') column = 2;
      else if (columnchar == 'D') column = 3;

      redPeople.push_back(People(row, column, 'R')); // red
   }

   cout << "Enter positions of neutral people" << endl;
   for (int i = 0; i < 4; i++) {
      cout << i + 1 << ": ";
      cin >> positionString;
      sscanf(positionString.c_str(), "%c%i", &columnchar, &row);
      row--;
columnchar = toupper(columnchar);
if (columnchar == 'A') column = 0;
else if (columnchar == 'B') column = 1;
else if (columnchar == 'C') column = 2;
else if (columnchar == 'D') column = 3;

neutPeople.push_back(People(row, column, 'N')); //neutral
   }

   cout << "Enter positions of obstacles" << endl;
   for (int i = 0; i < 3; i++) {
      cout << i + 1 << ": ";
      cin >> positionString;
      sscanf(positionString.c_str(), "%c%i", &columnchar, &row);
      row--;
      columnchar = toupper(columnchar);
      if (columnchar == 'A') column = 0;
      else if (columnchar == 'B') column = 1;
      else if (columnchar == 'C') column = 2;
      else if (columnchar == 'D') column = 3;

      obs.push_back(Item(row, column, 'O'));
   }
}


void printTrack(vector<Move> path, vector<People> redPeople, vector<People> neutPeople, vector<Item> obs) {
   priority_queue<Move> printMove = forPrintingMoves(path);
   priority_queue<Item> printItem = forPrintingItems(redPeople, neutPeople, obs);
   for (int i = 0; i < 8; i++) {

      for (int k = 0; k < 4; k++) {
         if (!printMove.empty() && printMove.top().getRow() == i * 2 && printMove.top().getColumn() == k) {
            cout << "+++~";
            Move temp = printMove.top();
            while (!printMove.empty() && printMove.top().getRow() == temp.getRow() && printMove.top().getColumn() == temp.getColumn()) {
               printMove.pop();
            }
         }
         else {
            cout << "---~";
         }
      }
      cout << endl;
      for (int j = 0; j < 4; j++) {
         if (!printMove.empty() && printMove.top().getRow() == i * 2 + 1 && printMove.top().getColumn() == j) {
            cout << "+";
            Move temp = printMove.top();
            while (!printMove.empty() && printMove.top().getRow() == temp.getRow() && printMove.top().getColumn() == temp.getColumn()) {
               printMove.pop();
            }
         }
         else {
            cout << "|";
         }
         if (!printItem.empty() && printItem.top().getRow() == i && printItem.top().getColumn() == j) {
            cout << " " << printItem.top().getChar() << " ";
            printItem.pop();
         }
         else cout << "   ";
      }
      if (!printMove.empty() && printMove.top().getRow() == i * 2 + 1 && printMove.top().getColumn() == 4) {
         cout << "+";
         Move temp = printMove.top();
         while (!printMove.empty() && printMove.top().getRow() == temp.getRow() && printMove.top().getColumn() == temp.getColumn()) {
            printMove.pop();
         }
      }
      else {
         cout << "|";
      }
      cout << endl << "~";
   }
   for (int k = 0; k < 4; k++) {
      if (!printMove.empty() && printMove.top().getRow() == 8 && printMove.top().getColumn() == k) {
         cout << "+++~";
         Move temp = printMove.top();
         while (!printMove.empty() && printMove.top().getRow() == temp.getRow() && printMove.top().getColumn() == temp.getColumn()) {
            printMove.pop();
         }
      }
      else {
         cout << "---~";
      }
   }
   cout << endl;
}
//testPath.insert(testPath.end(), temp.begin(), temp.end());
void red(vector<Move> &temp, vector<Move> &testPath, vector<Move> &shortestPath,
   Move start, Move end, bool &isFirst, vector<Move> aMoves, vector<Move> bMoves,
   vector<Move> cMoves, int a, int b, int c, vector<string> pickup) {
   for (Move A : (a == 1) ? aMoves : ((a == 2) ? bMoves : cMoves)) { // 123
      for (Move B : (b == 1) ? aMoves : ((b == 2) ? bMoves : cMoves)) {
         for (Move C : (c == 1) ? aMoves : ((c == 2) ? bMoves : cMoves)) {
            testPath.push_back(Move(Point(8, 2), Point(7, 2)));
            testPath.push_back(start);
            temp = routeTo(start, A);
            for (Point i : firstMoveIllegal) {
               if (A.getTwo() == i) {
                  temp.push_back(A.switchDir());
                  break;
               }
            }
            testPath.insert(testPath.end(), temp.begin(), temp.end());
            temp = routeTo(A, B);
            for (Point i : firstMoveIllegal) {
               if (B.getTwo() == i) {
                  temp.push_back(B.switchDir());
                  break;
               }
            }
            testPath.insert(testPath.end(), temp.begin(), temp.end());
            temp = routeTo(B, C);
            for (Point i : firstMoveIllegal) {
               if (C.getTwo() == i) {
                  temp.push_back(C.switchDir());
                  break;
               }
            }
            testPath.insert(testPath.end(), temp.begin(), temp.end());
            temp = routeTo(C, end);
            testPath.insert(testPath.end(), temp.begin(), temp.end());
            if (isFirst) {
               isFirst = false;
               shortestPath = testPath;
            }
            if (Path(shortestPath) > Path(testPath)) {
               shortestPath = testPath;
            }
            testPath.clear();
         }
      }
   }
}
void neut(vector<Move> &temp, vector<Move> &testPath, vector<Move> &shortestPath,
   Move start, Move end, bool &isFirst, vector<Move> aMoves, vector<Move> bMoves,
   vector<Move> cMoves, vector<Move> dMoves, int a, int b, int c, int d, vector<string> pickup) {
   for (Move A : (a == 1) ? aMoves : ((a == 2) ? bMoves : ((a == 3) ? cMoves: dMoves))) {
      for (Move B : (b == 1) ? aMoves : ((b == 2) ? bMoves : ((b == 3) ? cMoves : dMoves))) {
         for (Move C : (c == 1) ? aMoves : ((c == 2) ? bMoves : ((c == 3) ? cMoves : dMoves))) {
            for (Move D : (d == 1) ? aMoves : ((d == 2) ? bMoves : ((d == 3) ? cMoves : dMoves))) {

               testPath.push_back(start);
               temp = routeTo(start, A);
               for (Point i : firstMoveIllegal) {
                  if (A.getTwo() == i) {
                     temp.push_back(A.switchDir());
                     break;
                  }
               }
               testPath.insert(testPath.end(), temp.begin(), temp.end());
               temp = routeTo(A, B);
               for (Point i : firstMoveIllegal) {
                  if (B.getTwo() == i) {
                     temp.push_back(B.switchDir());
                     break;
                  }
               }
               testPath.insert(testPath.end(), temp.begin(), temp.end());
               temp = routeTo(B, C);
               for (Point i : firstMoveIllegal) {
                  if (C.getTwo() == i) {
                     temp.push_back(C.switchDir());
                     break;
                  }
               }
               testPath.insert(testPath.end(), temp.begin(), temp.end());
               temp = routeTo(C, D);
               for (Point i : firstMoveIllegal) {
                  if (D.getTwo() == i) {
                     temp.push_back(D.switchDir());
                     break;
                  }
               }
               testPath.insert(testPath.end(), temp.begin(), temp.end());
               temp = routeTo(D, end);
               testPath.insert(testPath.end(), temp.begin(), temp.end());
               if (isFirst) {
                  isFirst = false;
                  shortestPath = testPath;
               }
               vector<string> junk;
               if (Path(shortestPath) > Path(testPath)) {
                  shortestPath = testPath;
               }
               testPath.clear();

            }
         }
      }
   }
}

Path findRedPath(Move start, vector<People> redPeople, Move end) {
   bool isFirst = true;
   vector<Move> shortestPath;
   vector<Move> testPath;
   vector<Move> temp;
   vector<Move> aMoves = redPeople.at(0).getMoves();
   vector<Move> bMoves = redPeople.at(1).getMoves();
   vector<Move> cMoves = redPeople.at(2).getMoves();
   vector<string> pickup;
   
   for (int i = 1; i < 4; i++) {
      for (int j = 1; j < 4; j++) {
         for (int k = 1; k < 4; k++) {
            if (i == j || i == k || j == k) continue;
            red(temp, testPath, shortestPath, start, end, isFirst, aMoves, bMoves, cMoves, i, j, k, pickup);
         }
      }
   }
   cout << 1 / 25.0 * 100.0 << "%| ";
   return Path(shortestPath);
}
Path findNeutPath(Move start, vector<People> neutPeople, Move end) {
   
   bool isFirst = true;
   vector<Move> shortestPath;
   vector<Move> testPath;
   vector<Move> temp;
   vector<Move> aMoves = neutPeople.at(0).getMoves();
   vector<Move> bMoves = neutPeople.at(1).getMoves();
   vector<Move> cMoves = neutPeople.at(2).getMoves();
   vector<Move> dMoves = neutPeople.at(3).getMoves();
   vector<string> pickup;
   int stepCount = 1;
   cout << fixed << setprecision(0);
   for (int i = 1; i < 5; i++) {
      for (int j = 1; j < 5; j++) {
         for (int k = 1; k < 5; k++) {
            for (int l = 1; l < 5; l++) {
               if (i == j || i == k || i == l || j == k || j == l || k == l) continue;
               neut(temp, testPath, shortestPath, start, end, isFirst, aMoves, bMoves, cMoves, dMoves, i, j, k, l, pickup);
               cout << (double)++stepCount / 25.0 * 100.0 << "%| ";
            }
         }
      }
   }
   cout << endl;
   return Path(shortestPath);
   
}