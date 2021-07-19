// g4system
#include "g4world.h"
#include "g4systemFactories/g4systemFactory.h"



G4World::G4World(GWorld *gworld, int verbosity) {

	map<string, G4SystemFactory*> g4systemFactory;

	// registering factories in the manager
	// and adding them to systemFactory
	for(auto &s : gworld->getSystemsMap()) {
		string factory = s.second->getFactory();

//		// text
//		// ----
//		if(factory == "text") {
//			// if factory not found, registering it in the manager and loading it into the map
//			if(g4setupactory.find(factory) == g4setupactory.end()) {
//				g4SystemManager.RegisterObjectFactory<G4NativeSetupFactory>("G4NativeSetupFactory");
//				g4setupactory[factory] = g4SystemManager.CreateObject<G4SetupFactory>("G4NativeSetupFactory");
//			}
//		} else if(factory == "cad") {
//			// if factory not found, registering it in the manager and loading it into the map
//			if(g4setupactory.find(factory) == g4setupactory.end()) {
//				g4SystemManager.RegisterObjectFactory<G4CadSetupFactory>("G4CadSetupFactory");
//				g4setupactory[factory] = g4SystemManager.CreateObject<G4SetupFactory>("G4CadSetupFactory");
//			}
//		}

	}




	buildRootVolume(gworld, verbosity);
}
