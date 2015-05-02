#ifndef ATOM_H
#define ATOM_H

#include <vector>

class Atom {
private:
  int elnum;
  int sysnum;
  float x;
  float y;
  float z;
  std::vector<Atom*> bondedTo;

public:
  void newpos(float x, float y, float z);
  Atom (int elnum, int sysnum, float x, float y, float z);
  float distance(Atom other);
  void makeBond(Atom* other);
  void printBonds();
  
};

#endif
