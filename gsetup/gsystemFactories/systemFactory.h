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


protected:
	int verbosity;

};

#endif
