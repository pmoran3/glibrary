// g4volume
#include "g4volumes.h"



void G4Volumes::buildSetup(GSystem* gsystem, int verbosity)
{
	buildWorld(verbosity);

	// now loading gmanager
	g4SystemManager = GManager(verbosity - 1);

	// register the factories needed and build the geant4 volumes
	registerFactoriesAndBuildG4Volumes(gsetup, gopt);

	
}
