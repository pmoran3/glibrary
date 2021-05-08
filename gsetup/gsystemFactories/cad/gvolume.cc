// gsetup
#include "systemCadFactory.h"

// mlibrary
#include "gstring.h"
using namespace gstring;

// c++
#include <iostream>
#include <fstream>
using namespace std;

void GSystemCadFactory::loadGeometry(GOptions* gopt, GSystem *s)
{
	vector<string> possibleLocations = gopt->getStringVectorValue("setupDir");
	
	vector<string> cadFiles = s->gImportFiles(possibleLocations, verbosity, {"stl", "ply", "obj"});

	for(auto cf: cadFiles) {
		s->addGImportedVolume("cad", cf, verbosity);
	}
}

