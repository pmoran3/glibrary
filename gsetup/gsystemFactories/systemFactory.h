#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H 1

// glibrary
#include "goptions.h"

// gsetup
#include "gsystem.h"

// c++
#include <fstream>
#include <iostream>
using std::ifstream;
using std::cout;
using std::endl;


// file types
#define GTEXTMATSTYPE 0
#define GTEXTGEOMTYPE 0
#define GTEXTMIRSTYPE 0



// system factory
class GSystemFactory
{
public:
	// calls loadGeometry and loadMaterial
	void loadSystem(GSystem *system, int verbosity) {

		if(verbosity > GVERBOSITY_SUMMARY) {
			cout << GSETUPLOGHEADER << " Loading system " << system->getName() << " using factory: " << system->getFactory() <<  endl;
		}

		loadMaterial(system, verbosity);
		loadGeometry(system, verbosity);
	}

	virtual ~GSystemFactory() = default;

private:
	virtual void loadMaterial(GSystem *system, int verbosity) = 0;
	virtual void loadGeometry(GSystem *system, int verbosity) = 0;

	// returns the file stream, checking all possible directories.
	ifstream* gSystemFile(GSystem *system, int which, vector<string> locations, int verbosity);  // which: GTEXTMATERIALTYPE or GTEXTGEOMETRYTYPE

protected:
	int verbosity;

};

#endif
