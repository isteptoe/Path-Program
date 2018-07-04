#pragma once
#include "Move.h"
class Path {
public:
   Path(vector<Move> p, int o = 0) {
      path = p;
      pickup = vector<string>{};
      steps = p.size();
      corners = 0;
      order = o;
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
   vector<string> getPickup() { return pickup; }
   void setPickup(vector<string> s) { pickup = s; }
   int getOrder() { return order; }
   void setOrder(int o) { order = o; }
private:
   vector<Move> path;
   vector<string> pickup;
   int corners;
   int steps;
   int order;
};

void setOrder(int &order, int a, int b, int c, int d = 0) {
   order = d * 1000 + c * 100 + b * 10 + a;
}

void printMoves(Path path, int missionNum, char color) {
   vector<Move> v = path.getMoves();
   vector<string> s = path.getPickup();
   cout << "const char " << ((color == 'r') ? "RED_MISSION_" : "NEUTRAL_MISSION_") << missionNum << "[] = { ";
   cout << "FORWARD, ";
   dir curr;
   dir next;
   for (int i = 0; i < v.size() - 2; i++) {
      curr = v.at(i).getMoveDir();
      next = v.at(i + 1).getMoveDir();
      if (curr == next) cout << "FORWARD, ";
      else if (curr - next == -1 || curr - next == 3) cout << "RIGHT, ";
      else if (curr - next == 1 || curr - next == -3) cout << "LEFT, ";
      else cout << "BACK, ";
   }
   curr = v.at(v.size() - 2).getMoveDir();
   next = v.at(v.size() - 1).getMoveDir();
   if (curr == next) cout << "FORWARD }" << endl;
   else if (curr - next == -1 || curr - next == 3) cout << "RIGHT }" << endl;
   else if (curr - next == 1 || curr - next == -3) cout << "LEFT }" << endl;
   else cout << "BACK }" << endl;

   cout << "const char " << ((color == 'r') ? "RED_PICKUP_" : "NEUTRAL_PICKUP_") << missionNum << "[] = { ";
   for (int i = 0; i < v.size() - 1; i++) {
      cout << s.at(i) << ", ";
   }
   cout << s.at(s.size() - 1) << " };" << endl;
   
   cout << "const int " << ((color == 'r') ? "RED_STEPS_" : "NEUTRAL_STEPS_") << missionNum << " = " << v.size() << ";" << endl;

}