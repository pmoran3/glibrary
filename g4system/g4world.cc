// glibrary
#include "gfactory.h"

// g4system
#include "g4world.h"
#include "g4objectsFactories/g4objectsFactory.h"
#include "g4objectsFactories/g4native/g4NativeObjectsFactory.h"
#include "g4objectsFactories/cad/cadSystemFactory.h"



G4World::G4World(GWorld *gworld, GOptions* opt) {


	// instantiating volumes map
	g4volumesMap = new map<string, G4Volume*>;

	// instantiating gSystemManager
	int verbosity = opt->getInt(G4SYSTEMVERBOSITY);
	GManager g4SystemManager("G4World", verbosity);

	map<string, G4ObjectsFactory*> g4systemFactory;

	// registering factories in the manager
	// and adding them to g4systemFactory
	for(auto &s : *gworld->getSystemsMap()) {
		string factory = s.second->getFactory();
		string g4Factory = g4FactoryNameFromSystemFactory(factory);

		if(factory == "text" || factory == "mysql") {
			// if factory not found, registering it in the manager and loading it into the map
			if(g4systemFactory.find(g4Factory) == g4systemFactory.end()) {
				g4SystemManager.RegisterObjectFactory<G4NativeSystemFactory>(g4Factory);
			}
		} else if(factory == "cad") {
			// if factory not found, registering it in the manager and loading it into the map
			if(g4systemFactory.find(G4SYSTEMCADFACTORY) == g4systemFactory.end()) {
				g4SystemManager.RegisterObjectFactory<G4CadSystemFactory>(g4Factory);
			}
		}
		g4systemFactory[g4Factory] = g4SystemManager.CreateObject<G4ObjectsFactory>(g4Factory);
	}

	// done with g4SystemManager
	//g4SystemManager.clearDLMap();

	// now building geant4 objects
	// every volume that is not built (due to dependencies) increments remainingVolumes
	vector<GVolume*> thisIterationRemainingVolumes;
	unsigned long allRemainingVolumes = 0;
	do {
		thisIterationRemainingVolumes.clear();

		// looping over system in the gsystemsMap
		for(auto &system : *gworld->getSystemsMap()) {
			string systemName = system.first;
			string factory = system.second->getFactory();
			string g4Factory = g4FactoryNameFromSystemFactory(factory);

			// looping over getGVolumesMap in that system
			for(auto &gvolume : *system.second->getGVolumesMap()) {
				if(g4systemFactory.find(g4Factory) != g4systemFactory.end()) {

					if(verbosity == GVERBOSITY_DETAILS) {
						cout << G4SYSTEMLOGHEADER << "using factory <" << KYEL << g4Factory << RST << ">, to build g4volume <" << KYEL << gvolume.first << RST << ">" << endl;
					}

					// calling loadG4System
					// if a new system cannot be loaded, false is returned and the volumes added to thisIterationRemainingVolumes
					if(g4systemFactory[g4Factory]->loadG4System(opt, gvolume.second, g4volumesMap) == false) {
						thisIterationRemainingVolumes.push_back(gvolume.second);
					}
				} else {
					cerr << FATALERRORL << "g4systemFactory factory <" << g4Factory << "> not found in map." << endl;
					gexit(EC__G4SYSTEMFACTORYNOTFOUND);
				}
			}
			if(verbosity == GVERBOSITY_DETAILS) {
				cout << G4SYSTEMLOGHEADER << system.first << " : " << thisIterationRemainingVolumes.size() << " remaining motherless g4volumes to be built: " <<  endl;
				for (auto &gvolumeLeft: thisIterationRemainingVolumes) {
					cout << GTAB << "- " << gvolumeLeft->getName() << " with mother " << gvolumeLeft->getMother() << endl;
				}
			}
		}
		if(allRemainingVolumes != 0 && thisIterationRemainingVolumes.size() != 0) {
			if(allRemainingVolumes >= thisIterationRemainingVolumes.size()) {
				cerr << FATALERRORL << "dependencies are not being resolved: their number should diminish. Outstanding volumes:" << endl;
				for (auto &gvolumeLeft: thisIterationRemainingVolumes) {
					cerr << GTAB << "- <" << gvolumeLeft->getName() << "> with mother <" << gvolumeLeft->getMother() << ">" << endl;
				}
				gexit(EC__G4DEPENDENCIESNOTSOLVED);
			}
		} else {
			allRemainingVolumes = thisIterationRemainingVolumes.size();
		}
	} while (thisIterationRemainingVolumes.size() > 0);


}


string G4World::g4FactoryNameFromSystemFactory(string factory) {
	if (factory == "text" || factory == "mysql" ) {
		return G4SYSTEMNATFACTORY;
	} else if (factory == "cad" ) {
		return G4SYSTEMCADFACTORY;
	} else {
		cerr << FATALERRORL << "g4systemFactory factory <" << factory << "> not found in g4FactoryNameFromSystemFactory." << endl;
		gexit(EC__G4SYSTEMFACTORYNOTFOUND);
	}
	return G4SYSTEMNOTAPPLICABLEENTRY;
}
