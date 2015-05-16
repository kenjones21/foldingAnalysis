#include "protein.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

/*
Calculates center of mass. 
 */
std::vector<float> Protein::center_of_mass() {
  float xSum =  0.f;
  float ySum =  0.f;
  float zSum =  0.f;
  float totalWeight = 0.f;
  int count = 0;
  std::vector<float> ans;
  std::for_each(residues.begin(), residues.end(), [&](Residue r) {
      std::vector<Atom> heavyAtoms = r.getHeavyAtoms();
      std::for_each(heavyAtoms.begin(), heavyAtoms.end(), [&](Atom a) {
          xSum += a.getX() * a.getWeight();
          ySum += a.getY() * a.getWeight();
          zSum += a.getZ() * a.getWeight();
          totalWeight += a.getWeight();
          count++;
        });
    });
  ans.push_back(xSum / totalWeight);
  ans.push_back(ySum / totalWeight);
  ans.push_back(zSum / totalWeight);
  return ans;
}

Protein::Protein() {
  std::vector<Residue> residues;
  this->residues = residues;
}

void Protein::add_residue(Residue res) {
  residues.push_back(res);
}

int Protein::getNumRes() {
  return this->residues.size();
}

/*
Updates positions based on arrays x, y, and z. 
 */
void Protein::updatePos(const float* x, const float* y, const float* z) {
  for_each(residues.begin(), residues.end(), [&](Residue &r) {
      std::vector<Atom> heavyAtoms = r.getHeavyAtoms();
      for_each(heavyAtoms.begin(), heavyAtoms.end(), [&](Atom &a) {
          float tempX = x[a.getSysnum()];
          float tempY = y[a.getSysnum()];
          float tempZ = z[a.getSysnum()];
          a.newpos(tempX, tempY, tempZ);
          r.replaceAtom(a);
        });
    });
}

Atom Protein::getAtom(int resnum, int arbnum) {
  return residues[resnum].getAtom2(arbnum);
}

/*
Calculates # of residue heavy atoms "close" to other residue heavy atoms,
if they are "close" in the native structure. Cannot be used before nativeContacts
is initialized. Must be > 2 residues apart. Untested.
 */
float Protein::calcQ() {
  float ans = 0.f;
  for (uint i = 0; i < residues.size(); i++) {
    std::vector<Atom> heavyAtoms = this->residues[i].getHeavyAtoms();
    for (uint j = i + 3; j < residues.size(); j++) {
      std::vector<Atom> otherHeavyAtoms = this->residues[j].getHeavyAtoms();
      for (uint k = 0; k < heavyAtoms.size(); k++) {
        for (uint l = 0; l < otherHeavyAtoms.size(); l++) {
          // 4 nested for loops god damn
          if (heavyAtoms[k].distance(otherHeavyAtoms[l]) < DIST_CUTOFF) {
            std::pair<int, int> test(heavyAtoms[k].getSysnum(),
                                     heavyAtoms[l].getSysnum());
            if (this->nativeContacts.find(test) != this->nativeContacts.end()) {
              ans += 1.0;
            }
          }
        }
      }
    }
  }
  ans /= nativeContacts.size();
  return ans;
}

/*
Sets nativeContacts for the folded structure of an atom. 
 */
void Protein::setNativeContacts() {
  std::set<std::pair<int, int>> ans;
  for (uint i = 0; i < residues.size(); i++) {
    std::vector<Atom> heavyAtoms = this->residues[i].getHeavyAtoms();
    for (uint j = i + 3; j < residues.size(); j++) {
      std::vector<Atom> otherHeavyAtoms = this->residues[j].getHeavyAtoms();
      for (uint k = 0; k < heavyAtoms.size(); k++) {
        for (uint l = 0; l < otherHeavyAtoms.size(); l++) {
          // 4 nested for loops god damn
          if (heavyAtoms[k].distance(otherHeavyAtoms[l]) < DIST_CUTOFF) {
            std::pair<int, int> atoms(heavyAtoms[k].getSysnum(),
                                      heavyAtoms[l].getSysnum());
            ans.insert(atoms);
          }
        }
      }
    }
  }
  std::set<std::pair<int, int>>::iterator iter;
  int count = 0;
  for(iter=ans.begin(); iter!=ans.end();++iter);{
    //cout<<(*iter)<<endl;
    count += 1;
    std::cout << count << std::endl;
  }
  this->nativeContacts = ans;
}
