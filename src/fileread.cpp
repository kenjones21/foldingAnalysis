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

/*
Initializes a system according to a pdb file. Eventually may (or may not)
also read in a psf. 
 */
void Fileread::initSystem() {
  Protein protein;
  std::ifstream pdbFile(this->pdbFileName);
  std::cout << "Reading from file " << pdbFileName << std::endl;
  std::vector<Atom> atoms;
  std::vector<Residue> residues;
  if (pdbFile.is_open()) {
    std::cout << "It's working" << std::endl;
    std::string line = "";
    getline(pdbFile, line); // Again, first line useless
    while(line.substr(0,4) != "ATOM") {
      getline(pdbFile, line);
    }
    std::cout << "First good line: " << line.substr(0,4) << std::endl;
    int count = 2;
    int resnum;
    int prevresnum = 1;
    while (getline(pdbFile, line) && line.substr(0,4) == "ATOM") {
      if (line[77] != 'H') {
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
        if (line[24] == ' ') { // One digit
          resnum = line[25] - '0';
        }
        else { // Two digits
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
        float x = std::stof(readChars(line, 31, 38));
        float y = std::stof(readChars(line, 39, 46));
        float z = std::stof(readChars(line, 47, 54));
        tempAtom.newpos(x, y, z);
        atoms.push_back(tempAtom);
      }
      count++;
    }
    Residue res(atoms);
    protein.add_residue(res); // add last residue
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

std::string Fileread::readChars(std::string str, int schar, int echar) {
  std::string ans = "";
  for (int i = schar; i < echar + 1; i++) {
    ans += str[i];
  }
  return ans;
}
