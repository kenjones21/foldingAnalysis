#ifndef FILEREAD_H
#define FILEREAD_H

#include <string>
#include <iostream>
#include <vector>

#include "protein.h"

class Fileread {

private:
  
  std::string pdbFileName;
  std::string psfFileName;
  std::vector<Atom> tempAtoms;
  Protein protein;

public:
  
  Fileread(std::string pdbFileName, std::string psfFileName);
  void initSystem();
  Protein getProtein();
  
};

#endif
