#include "protein.h"
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<float> Protein::center_of_mass() {
  float xSum =  0.f;
  float ySum =  0.f;
  float zSum =  0.f;
  int count = 0;
  std::vector<float> ans;
  std::for_each(residues.begin(), residues.end(), [&](Residue r) {
      std::vector<Atom> heavyAtoms = r.getHeavyAtoms();
      std::cout << heavyAtoms.size() << std::endl;
      std::for_each(heavyAtoms.begin(), heavyAtoms.end(), [&](Atom a) {
          std::cout << xSum << std::endl;
          xSum += a.getX();
          ySum += a.getY();
          zSum += a.getZ();
          count++;
        });
    });
  std::cout << "Count is " << count << " and xSum is " << xSum << std::endl;
  ans.push_back(xSum / count);
  ans.push_back(ySum / count);
  ans.push_back(zSum / count);
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

void Protein::updatePos(const float* x, const float* y, const float* z) {
  for_each(residues.begin(), residues.end(), [&](Residue &r) {
      std::vector<Atom> heavyAtoms = r.getHeavyAtoms();
      for_each(heavyAtoms.begin(), heavyAtoms.end(), [&](Atom &a) {
          float tempX = x[a.getSysnum()];
          float tempY = y[a.getSysnum()];
          float tempZ = z[a.getSysnum()];
          if (a.getSysnum() == this->getAtom(7,2).getSysnum()) {
            std::cout << "tempX is " << tempX  << std::endl;
          }
          a.newpos(tempX, tempY, tempZ);
          r.replaceAtom(a);
        });
    });
}

Atom Protein::getAtom(int resnum, int arbnum) {
  return residues[resnum].getAtom2(arbnum);
}
