#ifndef PROTEIN_H
#define PROTEIN_H

#include "residue.h"
#include <vector>
#include <set>

class Protein {

private:
  std::vector<Residue> residues;
  static constexpr float DIST_CUTOFF = 5.f;
  std::set<std::pair<int, int>> nativeContacts;

public:
  std::vector<float> center_of_mass();
  Protein();
  void add_residue(Residue res);
  int getNumRes();
  void updatePos(const float* x, const float* y, const float* z);
  Atom getAtom(int resnum, int arbnum);
  float calcQ();
  void setNativeContacts();
  
};

#endif
