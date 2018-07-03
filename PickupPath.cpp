#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

int main() {

   vector<Move> path;
   vector<People> redPeople;
   vector<People> neutPeople;
   vector<Item> obs;
   obs.push_back(Item(0, 0, 'F')); // fire
   obs.push_back(Item(7, 0, 'H')); // hospital
   obs.push_back(Item(7, 3, 'S')); // shelter
   Move redStart(Point(7, 2), Point(6, 2));
   Move redEnd(Point(6, 1), Point(7, 1));
   Move neutStart(Point(7, 1), Point(6, 1));
   Move neutEnd(Point(7, 2), Point(7, 3));

   int missionNum = 0;

   cout << "What mission is this?" << endl;
   cin >> missionNum;
   if (missionNum != 1) {
      fillMission(redPeople, neutPeople, obs);
   }
   else {
      //first mission
      fillMission(redPeople, neutPeople, obs, 1);
   }
   Path redPath = findRedPath(redStart, redPeople, redEnd);
   Path neutPath = findNeutPath(neutStart, neutPeople, neutEnd);
   printMoves(redPath.getMoves(), missionNum, 'r');
   printMoves(neutPath.getMoves(), missionNum, 'n');
   cout << "Printing mission " << missionNum << ": \nRed Path" << endl;
   printTrack(redPath.getMoves(), redPeople, neutPeople, obs);
   cout << endl << "Neutral Path" << endl;
   printTrack(neutPath.getMoves(), redPeople, neutPeople, obs);
   return 0;
}


//add pickupmoves when creating paths
// this is a nother test
