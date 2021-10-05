#ifndef SYSTEMCADFACTORY_H
#define SYSTEMCADFACTORY_H 1

// gsystem
#include "systemFactory.h"

// system factory
class GSystemCADFactory : GSystemFactory
{

public:
	
	// constructor will load the possible location(s) of the geometry and material databases
	GSystemCADFactory();

private:
	vector<string> possibleLocationOfCadFiles;

private:

	virtual void loadMaterial(GSystem *system, int verbosity);
	virtual void loadGeometry(GSystem *system, int verbosity);

};


#endif
// returns a vector of import files, checking all possible directories.
// this should be in some general utility library? gutilities?
// vector<string> gImportFiles(vector<string> locations, int verbosity, vector<string> possibleExtensions);
