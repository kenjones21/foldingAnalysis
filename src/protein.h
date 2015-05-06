#ifndef PROTEIN_H
#define PROTEIN_H

#include "residue.h"
#include <vector>

class Protein {

private:
  std::vector<Residue> residues;

public:
  float center_of_mass();
  Protein();
  void add_residue(Residue res);
  int getNumRes();
  
};

#endif
