// glibrary
#include "gfactory.h"

// g4system
#include "g4world.h"
#include "g4systemFactories/g4systemFactory.h"
#include "g4systemFactories/g4native/g4NativeSystemFactory.h"
#include "g4systemFactories/cad/cadSystemFactory.h"



G4World::G4World(GWorld *gworld, GOptions* opt) {

	// instantiating gSystemManager
	int verbosity = opt->getInt("g4systemv");
	GManager g4SystemManager("G4World", verbosity);

	map<string, G4SystemFactory*> g4systemFactory;

	// registering factories in the manager
	// and adding them to g4systemFactory
	for(auto &s : *gworld->getSystemsMap()) {
		string factory = s.second->getFactory();

		if(factory == "text" || factory == ROOTWORLDGVOLUMENAME) {
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
	// done with g4SystemManager
	g4SystemManager.clearDLMap();

	if(verbosity == GVERBOSITY_DETAILS) {
		for(auto &system : *gworld->getSystemsMap()) {
			for(auto &gvolume : *system.second->getGVolumesMap()) {
				cout << G4SYSTEMLOGHEADER << "g4system <" << KYEL << system.first << RST << ">, g4volume <" << KYEL << gvolume.first << RST << ">" << endl;
			}
		}
	}

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
			// looping over getGVolumesMap in that system
			for(auto &gvolume : *system.second->getGVolumesMap()) {
				if(g4systemFactory.find(factory) != g4systemFactory.end()) {


					if(verbosity == GVERBOSITY_DETAILS) {
						cout << G4SYSTEMLOGHEADER << "using factory <" << KYEL << factory << RST << ">, to build g4volume <" << KYEL << gvolume.first << RST << ">" << endl;
					}
					// getting or instantiating a new g4system, and getting its g4volumesMap
					auto g4volumesMapForThisSystem = getOrCreateG4System(systemName, factory, verbosity)->getg4volumesMap();

					// calling loadG4System
					// if a new system cannot be loaded, false is returned and the volumes added to thisIterationRemainingVolumes
					if(g4systemFactory[factory]->loadG4System(opt, gvolume.second, g4volumesMapForThisSystem) == false) {
						thisIterationRemainingVolumes.push_back(gvolume.second);
					}
				} else {
					cerr << FATALERRORL << "g4systemFactory factory <" << factory << "> not found." << endl;
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
					cout << GTAB << "- <" << gvolumeLeft->getName() << "> with mother <" << gvolumeLeft->getMother() << ">" << endl;
				}
				gexit(EC__DEPENDENCIESNOTSOLVED);
			}
		} else {
			allRemainingVolumes = thisIterationRemainingVolumes.size();
		}
	} while (thisIterationRemainingVolumes.size() > 0);


}


// return system pointer if exist, otherwise create a new one, add it to the map
// then return that one.
G4System* G4World::getOrCreateG4System(string sname, string factory, int verbosity) {


	// check if g4s already exists
	if(g4systemsMap.find(sname) != g4systemsMap.end()) {
		if(verbosity == GVERBOSITY_DETAILS) {
			cout << G4SYSTEMLOGHEADER << "System  <" << KYEL << sname << RST << "> already exist in g4systemsMap" << endl;
		}
		return g4systemsMap[sname];
	} else {
		if(verbosity == GVERBOSITY_DETAILS) {
			cout << G4SYSTEMLOGHEADER << "Creating new system  <" << KYEL << sname << RST << "> and adding it to g4systemsMap" << endl;
		}
		// adding volume to the map
		g4systemsMap[sname] = new G4System(sname, factory, verbosity);
		return g4systemsMap[sname];
	}

}
