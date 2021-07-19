// glibrary
#include "gfactory.h"

// g4system
#include "g4world.h"
#include "g4systemFactories/g4systemFactory.h"
#include "g4systemFactories/g4native/g4NativeSystemFactory.h"
#include "g4systemFactories/cad/cadSystemFactory.h"



G4World::G4World(GWorld *gworld, int verbosity) {


	// instantiating gSystemManager
	GManager g4SystemManager(verbosity);

	map<string, G4SystemFactory*> g4systemFactory;

	// registering factories in the manager
	// and adding them to g4systemFactory
	for(auto &s : gworld->getSystemsMap()) {
		string factory = s.second->getFactory();

		// text
		// ----
		if(factory == "text") {
			// if factory not found, registering it in the manager and loading it into the map
			if(g4systemFactory.find(factory) == g4systemFactory.end()) {
				g4SystemManager.RegisterObjectFactory<G4NativeSystemFactory>("G4NativeSystemFactory");
				g4systemFactory[factory] = g4SystemManager.CreateObject<G4SystemFactory>("G4NativeSystemFactory");
			}
		} else if(factory == "cad") {
			// if factory not found, registering it in the manager and loading it into the map
			if(g4systemFactory.find(factory) == g4systemFactory.end()) {
				g4SystemManager.RegisterObjectFactory<G4CadSystemFactory>("G4CadSystemFactory");
				g4systemFactory[factory] = g4SystemManager.CreateObject<G4SystemFactory>("G4CadSystemFactory");
			}
		}
	}

	g4SystemManager.clearDLMap();



//	buildRootVolume(gworld, verbosity);
}
