#ifndef ATOM_H
#define ATOM_H

#include <vector>

class Atom {
private:
  constexpr static float CUTOFF = 5.0;
  int elnum;
  int sysnum;
  float x;
  float y;
  float z;
  float weight;
  std::vector<Atom*> bondedTo;

public:
  
  void newpos(float x, float y, float z);
  Atom (int elnum, int sysnum, float x, float y, float z, float weight);
  Atom (int elnum, int sysnum, float weight);
  Atom ();
  float distance(Atom other);
  void makeBond(Atom* other);
  void printBonds();
  bool isHeavy();
  int getSysnum();
  int getElnum();
  float getWeight();
  void setInfo (int elnum, int sysnum, float weight);
  float getX();
  float getY();
  float getZ();
  
};

#endif
