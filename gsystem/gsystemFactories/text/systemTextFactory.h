#ifndef SYSTEMTEXTFACTORY_H
#define SYSTEMTEXTFACTORY_H 1

// gsystem
#include "systemTextFactory.h"
#include "systemFactory.h"

// file types
#define GTEXTGEOMTYPE "__geometry_"
#define GTEXTMATSTYPE "__materials_"
#define GTEXTMIRSTYPE "__mirrors_"

// system factory
class GSystemTextFactory : GSystemFactory
{
public:

	// constructor will load the possible location(s) of the geometry and material databases
	GSystemTextFactory();

private:
	vector<string> possibleLocationOfTextDatabases;

private:

	virtual void loadMaterial(GSystem *system, int verbosity);
	virtual void loadGeometry(GSystem *system, int verbosity);

	// returns the file stream, checking all possible directories.
	ifstream* gSystemTextFile(GSystem *system, string SYSTEMTYPE, int verbosity);  // SYTEMTYPE one of file types above

};

#endif
