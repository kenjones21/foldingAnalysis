#ifndef RESIDUE_H
#define RESIDUE_H

#include <string>
#include <vector>
#include "atom.h"

class Residue {
  
private:
  std::string code3;
  std::string code1;
  std::vector<Atom*> atoms;  
  
public:
  std::string get3code();
  std::string get1code();
  Atom* getAtom(int sysnum);
  std::vector<Atom*> getAllAtoms();
  std::vector<Atom*> getHeavyAtoms();
  Residue(std::vector<Atom*> atoms, std::string code3, std::string code1);
  Residue(std::vector<Atom*> atoms);
  
};

#endif
