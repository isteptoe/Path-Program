#pragma once
#include "Move.h"
class Path {
public:
   Path(vector<Move> p/*, vector<string> s*/) {
      path = p;
      //pickup = s;
      steps = p.size();
      corners = 0;
      for (int i = 0; i < p.size() - 1; i++) {
         if (isCorner(p.at(i), p.at(i + 1))) corners++;
      }
   }
   bool operator>(const Path a) {
      if (this->corners == a.corners) return this->steps > a.steps;
      return this->corners > a.corners;
   }
   vector<Move> operator+(const Path a) const {
      vector<Move> returnThis = this->path;
      returnThis.insert(returnThis.end(), a.getMoves().begin(), a.getMoves().end());

   }
   vector<Move> getMoves() const { return path; }
private:
   vector<Move> path;
   //vector<string> pickup;
   int corners;
   int steps;
};

void printMoves(Path path, int missionNum, char color) {
   vector<Move> v = path.getMoves();
   //vector<string> s = path.getPickup();
   cout << "const char " << ((color == 'r') ? "RED_MISSION_" : "NEUTRAL_MISSION_") << missionNum << "[] = { ";
   for (int i = 0; i < v.size() - 1; i++) {
      if (v.at(i).getMoveDir() == NORTH) cout << "FORWARD, ";
      else if (v.at(i).getMoveDir() == SOUTH) cout << "BACK, ";
      else if (v.at(i).getMoveDir() == EAST) cout << "RIGHT, ";
      else if (v.at(i).getMoveDir() == WEST) cout << "LEFT, ";
   }
   if (v.at(v.size() - 1).getMoveDir() == NORTH) cout << "FORWARD };" << endl;
   else if (v.at(v.size() - 1).getMoveDir() == SOUTH) cout << "BACK };" << endl;
   else if (v.at(v.size() - 1).getMoveDir() == EAST) cout << "RIGHT };" << endl;
   else if (v.at(v.size() - 1).getMoveDir() == WEST) cout << "LEFT };" << endl;

   /*cout << "const char " << ((color == 'r') ? "RED_PICKUP_" : "NEUTRAL_PICKUP_") << missionNum << "[] = { ";
   for (int i = 0; i < v.size() - 1; i++) {
   cout << s.at(i) << ", ";
   }
   cout << s.at(s.size() - 1) << " };" << endl;
   */
}