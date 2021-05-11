#ifndef SYSTEMCADFACTORY_H
#define SYSTEMCADFACTORY_H 1

// gsetup
#include "systemFactory.h"

// system factory
class GSystemCadFactory : GSystemFactory
{

private:
	virtual void loadMaterial(GSystem *system, int verbosity);
	virtual void loadGeometry(GSystem *system, int verbosity);

};


#endif
