#include "fileread.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "atom.h"
#include "residue.h"
#include "protein.h"

Fileread::Fileread(std::string pdbFileName, std::string psfFileName) {
  this->pdbFileName = pdbFileName;
  this->psfFileName = psfFileName;
}

void Fileread::initSystem() {
  Protein protein;
  std::ifstream pdbFile(this->pdbFileName);
  std::vector<Atom> atoms;
  std::vector<Residue> residues;
  if (pdbFile.is_open()) {
    std::cout << "It's working" << std::endl;
    std::string line = "";
    getline(pdbFile, line); // Again, first line useless
    int count = 2;
    int resnum;
    int prevresnum = 1;
    while (getline(pdbFile, line)) {
      if (line[77] == ' ' && line[12] != 'H' && line[13] != 'H') {
        Atom tempAtom;
        if (line[13] == 'O') {
          tempAtom.setInfo(8, count - 1, 16.002);
        }
        else if (line[13] == 'C') {
          tempAtom.setInfo(6, count - 1, 12.001);
        }
        else if (line[13] == 'N') {
          tempAtom.setInfo(7, count - 1, 14.007);
        }
        if (line[24] == ' ') {
          resnum = line[25] - '0';
        }
        else {
          std::string resNumString = "";
          resNumString += line[24];
          resNumString += line[25];
          resnum = std::stoi(resNumString);
        }
        if (resnum != prevresnum) { // On resnum change
          Residue res(atoms);
          protein.add_residue(res);
          prevresnum = resnum;
          atoms.clear();
        }
        atoms.push_back(tempAtom);
      }
      count++;
    }
    Residue res(atoms);
    protein.add_residue(res);
    std::cout << "Number of residues in protein: " << protein.getNumRes() << std::endl;
    this->protein = protein;
  }
  else {
    std::cout << "Error opening PDB File" << std::endl;
  }
  std::ifstream psfFile(this->psfFileName);
  if (psfFile.is_open()) {
    // Connectivity stuff here
  }
  else {
    std::cout << "Error opening PSF File" << std::endl;
  }
}

Protein Fileread::getProtein() {
  return this->protein;
}
