#include "residue.h"
#include <stdexcept>
#include <iostream>

std::string Residue::get3code() {
  return this->code3;
}

std::string Residue::get1code() {
  return this->code1;
}

Atom Residue::getAtom(int sysnum) {
  for (std::vector<Atom>::iterator it = atoms.begin(); it != atoms.end(); it++) {
    if ((it)->getSysnum() == sysnum) {
      return *it;
    }
    else {
      throw std::invalid_argument("Received bad sysnum");
    }
  }
}

std::vector<Atom> Residue::getAllAtoms() {
  return this->atoms;
}

std::vector<Atom> Residue::getHeavyAtoms() {
  std::vector<Atom> heavyAtoms;
  for (std::vector<Atom>::iterator it = atoms.begin(); it != atoms.end(); it++) {
    if ((*it).isHeavy()) {
      heavyAtoms.push_back(*it);
    }
  }
  return heavyAtoms;
}

Residue::Residue(std::vector<Atom> atoms, std::string code3, std::string code1) {
  this->atoms = atoms;
  this->code3 = code3;
  this->code1 = code1;
}

Residue::Residue(std::vector<Atom> atoms) {
  this->atoms = atoms;
  this->code3 = "xxx";
  this->code1 = "x";
}

void Residue::addAtom(Atom atom) {
  atoms.push_back(atom);
}

Atom Residue::getAtom2(int arbnum) {
  return atoms[arbnum];
}

void Residue::replaceAtom(Atom atom) {
  bool errFlag = true;
  for (uint i = 0; i < this->atoms.size(); i++) {
    if (this->atoms[i].getSysnum() == atom.getSysnum()) {
      atoms[i] = atom;
      errFlag = false;
    }
  }
  if (errFlag) {
    std::cout << "ERROR IN REPLACE ATOM" << std::endl;
  }
}
