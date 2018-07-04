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
   vector<Move> cMoves, int a, int b, int c, vector<string> pickup, int &shortestOrder) {
   for (Move A : (a == 1) ? aMoves : ((a == 2) ? bMoves : cMoves)) { // 123
      for (Move B : (b == 1) ? aMoves : ((b == 2) ? bMoves : cMoves)) {
         for (Move C : (c == 1) ? aMoves : ((c == 2) ? bMoves : cMoves)) {
            if (!(A != B && A != C && B != C)) continue;
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
               setOrder(shortestOrder, a, b, c);
            }
            if (Path(shortestPath) > Path(testPath)) {
               shortestPath = testPath;
               setOrder(shortestOrder, a, b, c);
            }
            testPath.clear();
         }
      }
   }
}
void neut(vector<Move> &temp, vector<Move> &testPath, vector<Move> &shortestPath,
   Move start, Move end, bool &isFirst, vector<Move> aMoves, vector<Move> bMoves,
   vector<Move> cMoves, vector<Move> dMoves, int a, int b, int c, int d, vector<string> pickup, int &shortestOrder) {
   for (Move A : (a == 1) ? aMoves : ((a == 2) ? bMoves : ((a == 3) ? cMoves: dMoves))) {
      for (Move B : (b == 1) ? aMoves : ((b == 2) ? bMoves : ((b == 3) ? cMoves : dMoves))) {
         for (Move C : (c == 1) ? aMoves : ((c == 2) ? bMoves : ((c == 3) ? cMoves : dMoves))) {
            for (Move D : (d == 1) ? aMoves : ((d == 2) ? bMoves : ((d == 3) ? cMoves : dMoves))) {
               if (!(A != B && A != C && A != D && B != C && B != D && C != D)) continue;
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
               testPath.push_back(Move(Point(7, 2), Point(7, 3)));
               if (isFirst) {
                  isFirst = false;
                  shortestPath = testPath;
                  setOrder(shortestOrder, a, b, c, d);
               }
               if (Path(shortestPath) > Path(testPath)) {
                  shortestPath = testPath;
                  setOrder(shortestOrder, a, b, c, d);
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
   int shortestOrder = 0;
   for (int i = 1; i < 4; i++) {
      for (int j = 1; j < 4; j++) {
         for (int k = 1; k < 4; k++) {
            if (i == j || i == k || j == k) continue;
            red(temp, testPath, shortestPath, start, end, isFirst, aMoves, bMoves, cMoves, i, j, k, pickup, shortestOrder);
         }
      }
   }
   cout << 1 / 25.0 * 100.0 << "%| ";
   return Path(shortestPath, shortestOrder);
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
   int shortestOrder = 0;
   int stepCount = 1;
   cout << fixed << setprecision(0);
   for (int i = 1; i < 5; i++) {
      for (int j = 1; j < 5; j++) {
         for (int k = 1; k < 5; k++) {
            for (int l = 1; l < 5; l++) {
               if (i == j || i == k || i == l || j == k || j == l || k == l) continue;
               neut(temp, testPath, shortestPath, start, end, isFirst, aMoves, bMoves, cMoves, dMoves, i, j, k, l, pickup, shortestOrder);
               cout << (double)++stepCount / 25.0 * 100.0 << "%| ";
            }
         }
      }
   }
   cout << endl;
   return Path(shortestPath, shortestOrder);
   
}

string getDirection(Move m, People p) {
   string direction;
   dir moveDirect = m.getMoveDir();

   if (m.getRow() == p.getRow() * 2) { // above person
      if (moveDirect == WEST) direction = "LEFT";
      else direction = "RIGHT";
   }
   else if (m.getRow() == (p.getRow() + 1) * 2) { // below person
      if (moveDirect == EAST) direction = "LEFT";
      else direction = "RIGHT";
   }
   else if (m.getColumn() == p.getColumn() + 1) { // to the right
      if (moveDirect == NORTH) direction = "LEFT";
      else direction = "RIGHT";
   }
   else { // to left
      if (moveDirect == SOUTH) direction = "LEFT";
      else direction = "RIGHT";
   }

   return direction;
}

void setPickupPath(Path &p, vector<People> people) {
   vector<string> pickupPath;
   vector<Move> moves = p.getMoves();
   People personA = people.at(0);
   People personB = people.at(1);
   People personC = people.at(2);
   People personD;
   if (people.size() == 4) personD = people.at(3);
   bool AisUp = false;
   bool BisUp = false;
   bool CisUp = false;
   bool DisUp = true;
   if (people.size() == 4) DisUp = false;
   int first = p.getOrder() % 10;
   int second = (p.getOrder() % 100) / 10;
   int third = (p.getOrder() % 1000) / 100;
   int last;
   if (people.size() == 4) last = p.getOrder() / 1000;
   bool doContinue = false;
   if (people.size() == 3) {
      for (Move m : moves) {
         doContinue = false;
         if (!((first == 1) ? AisUp : ((first == 2) ? BisUp : CisUp))) {
            for (Move test : ((first == 1) ? personA : ((first == 2) ? personB : personC)).getMoves()) {
               if (!(test != m)) {
                  doContinue = true;
                  ((first == 1) ? AisUp : ((first == 2) ? BisUp : CisUp)) = true;
                  pickupPath.push_back(getDirection(m, ((first == 1) ? personA : ((first == 2) ? personB : personC))));
                  break;
               }
            }
         }
         if (doContinue) continue;
         if (!((second == 1) ? AisUp : ((second == 2) ? BisUp : CisUp))) {
            for (Move test : ((second == 1) ? personA : ((second == 2) ? personB : personC)).getMoves()) {
               if (!(test != m)) {
                  doContinue = true;
                  ((second == 1) ? AisUp : ((second == 2) ? BisUp : CisUp)) = true;
                  pickupPath.push_back(getDirection(m, ((second == 1) ? personA : ((second == 2) ? personB : personC))));
                  break;
               }
            }
         }
         if (doContinue) continue;
         if (!((third == 1) ? AisUp : ((third == 2) ? BisUp : CisUp))) {
            for (Move test : ((third == 1) ? personA : ((third == 2) ? personB : personC)).getMoves()) {
               if (!(test != m)) {
                  doContinue = true;
                  ((third == 1) ? AisUp : ((third == 2) ? BisUp : CisUp)) = true;
                  pickupPath.push_back(getDirection(m, ((third == 1) ? personA : ((third == 2) ? personB : personC))));
                  break;
               }
            }
         }
         if (doContinue) continue;
         pickupPath.push_back("EMPTY");

      }
   }
   else {
      for (Move m : moves) {
         doContinue = false;
         if (!((first == 1) ? AisUp : ((first == 2) ? BisUp : ((first == 3) ? CisUp : DisUp)))) {
            for (Move test : ((first == 1) ? personA : ((first == 2) ? personB : ((first == 3) ? personC : personD))).getMoves()) {
               if (!(test != m)) {
                  doContinue = true;
                  ((first == 1) ? AisUp : ((first == 2) ? BisUp : ((first == 3) ? CisUp : DisUp))) = true;
                  pickupPath.push_back(getDirection(m, ((first == 1) ? personA : ((first == 2) ? personB : ((first == 3) ? personC : personD)))));
                  break;
               }
            }
         }
         if (doContinue) continue;
         if (!((second == 1) ? AisUp : ((second == 2) ? BisUp : ((second == 3) ? CisUp : DisUp)))) {
            for (Move test : ((second == 1) ? personA : ((second == 2) ? personB : ((second == 3) ? personC : personD))).getMoves()) {
               if (!(test != m)) {
                  doContinue = true;
                  ((second == 1) ? AisUp : ((second == 2) ? BisUp : ((second == 3) ? CisUp : DisUp))) = true;
                  pickupPath.push_back(getDirection(m, ((second == 1) ? personA : ((second == 2) ? personB : ((second == 3) ? personC : personD)))));
                  break;
               }
            }
         }
         if (doContinue) continue;
         if (!((third == 1) ? AisUp : ((third == 2) ? BisUp : ((third == 3) ? CisUp : DisUp)))) {
            for (Move test : ((third == 1) ? personA : ((third == 2) ? personB : ((third == 3) ? personC : personD))).getMoves()) {
               if (!(test != m)) {
                  doContinue = true;
                  ((third == 1) ? AisUp : ((third == 2) ? BisUp : ((third == 3) ? CisUp : DisUp))) = true;
                  pickupPath.push_back(getDirection(m, ((third == 1) ? personA : ((third == 2) ? personB : ((third == 3) ? personC : personD)))));
                  break;
               }
            }
         }
         if (doContinue) continue;
         if (!((last == 1) ? AisUp : ((last == 2) ? BisUp : ((last == 3) ? CisUp : DisUp)))) {
            for (Move test : ((last == 1) ? personA : ((last == 2) ? personB : ((last == 3) ? personC : personD))).getMoves()) {
               if (!(test != m)) {
                  doContinue = true;
                  ((last == 1) ? AisUp : ((last == 2) ? BisUp : ((last == 3) ? CisUp : DisUp))) = true;
                  pickupPath.push_back(getDirection(m, ((last == 1) ? personA : ((last == 2) ? personB : ((last == 3) ? personC : personD)))));
                  break;
               }
            }
         }
         if (doContinue) continue;
         pickupPath.push_back("EMPTY");

      }
   }
   p.setPickup(pickupPath);
}