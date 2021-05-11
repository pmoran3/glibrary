#ifndef SYSTEMTEXTFACTORY_H
#define SYSTEMTEXTFACTORY_H 1

// gsetup
#include "systemFactory.h"

// file types
#define GTEXTMATSTYPE 0
#define GTEXTGEOMTYPE 0
#define GTEXTMIRSTYPE 0

// system factory
class GSystemTextFactory : GSystemFactory
{
private:
	virtual void loadMaterial(GSystem *system, int verbosity);
	virtual void loadGeometry(GSystem *system, int verbosity);

	// returns the file stream, checking all possible directories.
	ifstream* gSystemTextFile(GSystem *system, int which, vector<string> locations, int verbosity);  // which: GTEXTMATERIALTYPE or GTEXTGEOMETRYTYPE

};

#endif
