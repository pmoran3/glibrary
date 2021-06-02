#ifndef SYSTEMTEXTFACTORY_H
#define SYSTEMTEXTFACTORY_H 1

// gsetup
#include "../systemFactory.h"

// system factory
class GSystemGDMLFactory : GSystemFactory
{
public:
	void loadSystem(GOptions* gopt, GSystem *s) {
		verbosity = gopt->getInt("gvolumev");
		if(verbosity > GVERBOSITY_SUMMARY) {
			cout << setupLogHeader << " Loading <GDML> system " << s->getName() << endl;
		}
		loadMaterial(gopt, s);
		loadGeometry(gopt, s);
	}
		
private:
	// PRAGMA TODO: is GOptions necessary?
	virtual void loadMaterial(GOptions* gopt, GSystem *s);
	virtual void loadGeometry(GOptions* gopt, GSystem *s);
	
};


#endif
