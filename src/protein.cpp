#include "protein.h"
#include <algorithm>
#include <iostream>
#include <vector>

float Protein::center_of_mass() {
  float ans = 0.f;
  int count = 0;
  std::for_each(residues.begin(), residues.end(), [&ans](Residue *r) {
      std::vector<Atom*> heavyAtoms = r->getHeavyAtoms();
      std::for_each(heavyAtoms.begin(), heavyAtoms.end(), [&ans](Atom* a) {
          ans += (float)(a->getElnum());
        });
    });
  return ans/count;
}
