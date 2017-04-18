/** @file tutorialInputOutput.cpp

    @brief Tutorial on how to use input output facilities of G+Smo library.

    This file is part of the G+Smo library.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    Author(s): J. Speh
*/

// For detailed options about visualization look at gsView.cpp example. 



#include <iostream>
#include <gismo.h>

using namespace gismo;


int main(int argc, char* argv[])
{

    //! [Parse command line]   
    std::string input("curves3d/bspline3d_curve_01.xml");
    std::string output("out");
    
    gsCmdLine cmd("Tutorial Input Output");
    cmd.addPlainString("filename", "G+Smo input geometry file.", input);
    cmd.addString("o", "output", "Name of the output file", output);
    cmd.getValues(argc,argv);
    //! [Parse command line]   
    
    //! [Read geometry]
    if (!gsFileManager::find(input))
    {
        gsWarn << "The file cannot be found!\n";
        return 1;
    }

    gsInfo << "Read file \"" << input << "\"\n";

    gsFileData<> fileData(input);

    gsGeometry<>::uPtr pGeom;
    if (fileData.has< gsGeometry<> >())
    {
        pGeom = fileData.getFirst< gsGeometry<> >();
    }
    else
    {
        gsWarn << "Input file doesn't have a geometry inside.\n";
        return -1;
    }
    //! [Read geometry]
    
    //! [Print geometry]
    gsInfo << "The file contains: \n" << *pGeom << "\n";
    //! [Print geometry]
    
    // writing a paraview file
    const std::string out = output + "Paraview";
    gsWriteParaview(*pGeom, out);
    gsInfo << "Wrote a paraview file: " << out << "\n";

    //! [Write geometry]    
    // writing a G+Smo .xml file            
    gsFileData<> fd;
    fd << *pGeom;
    // output is a string. The extention .xml is added automatically
    fd.save(output); 
    gsInfo << "Wrote G+Smo file: " << output << ".xml \n";
    //! [Write geometry]    
    
    return 0;
}



