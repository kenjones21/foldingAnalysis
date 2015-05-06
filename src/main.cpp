/*
 *  read_dcd : c++ class + main file example for reading a CHARMM dcd file
 *  Copyright (C) 2013  Florent Hedin
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <iostream>
#include "atom.h"
#include "fileread.h"

#include "../lib/array_tools.hpp"
#include "../lib/dcd_r.hpp"

using namespace std;

int main(int argc, char* argv[])
{                
    // instance of a new object DCD_R attached to a dcd file 
    DCD_R dcdf("../resources/noshake.dcd");
    
    // read the header and print it
    dcdf.read_header();
    dcdf.printHeader();
    
    const float *x,*y,*z;

    int count = 0;
    Protein alb;
    
    // in this loop the coordinates are read frame by frame
    for(int frame=0;frame<dcdf.getNFILE();frame++)
    {
        dcdf.read_oneFrame();
        
        /* your code goes here */
        
        x = dcdf.getX();
        y = dcdf.getY();
        z = dcdf.getZ();
        
        if (count == 0) {
          Fileread f("../resources/alb_final_ion.pdb",
                   "../resources/alb_final_ion.psf");
          f.initSystem();
          alb = f.getProtein();
          alb.updatePos(x, y, z);
          std::cout << alb.center_of_mass()[0] << std::endl;
          std::cout << "My x is " << alb.getAtom(7,2).getX() << std::endl;
        }
        if (count == 10) {
          std::cout << x[852] << std::endl;
        }
        count++;
        
        /* ... */
        
    }
    
    return EXIT_SUCCESS;
}
