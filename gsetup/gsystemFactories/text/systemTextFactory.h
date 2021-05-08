#ifndef SYSTEMTEXTFACTORY_H
#define SYSTEMTEXTFACTORY_H 1

// gsetup
#include "systemFactory.h"

// system factory
class GSystemTextFactory : GSystemFactory
{
private:
	virtual void loadMaterial(GSystem *system, int verbosity);
	virtual void loadGeometry(GSystem *system, int verbosity);
};

#endif
