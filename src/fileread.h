#ifndef FILEREAD_H
#define FILEREAD_H

#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "protein.h"

class Fileread {

private:
  
  std::string pdbFileName;
  std::string psfFileName;
  std::vector<Atom> tempAtoms;
  Protein protein;
  std::string readChars(std::string str, int schar, int echar);

public:
  
  Fileread(std::string pdbFileName, std::string psfFileName);
  void initSystem();
  Protein getProtein();
  
};

#endif
