// glibrary
#include "gfactory.h"

// gsetup
#include "gworld.h"
#include "gsystemFactories/systemFactory.h"
#include "gsystemFactories/text/systemTextFactory.h"
#include "gsystemFactories/cad/systemCadFactory.h"
//#include "gsystemFactories/gdml/systemCadFactory.h"
//#include "gsystemFactories/mysql/systemCadFactory.h"


GWorld::GWorld(GOptions* gopts) {

	int verbosity = gopts->getInt("gsetupV");

	// projecting options onto vector of JSystem
	vector<gsetup::JSystem> systems = gsetup::getSystems(gopts);

	// loading gsystemsMap
	for (auto& system: systems) {
		gsystemsMap[system.system] = new GSystem(system.system, system.factory, system.variation, system.runno, verbosity);
	}

	// projecting options onto vector of GModifiers
	vector<gsetup::JModifier> jmodifiers = gsetup::getModifiers(gopts);

	// loading gmodifiersMap
	for (auto& modifier: jmodifiers) {
		if ( modifier.volume != NOMODIFIER) {
			gmodifiersMap[modifier.volume] = new GModifier(modifier.volume, modifier.shift, modifier.tilt, modifier.isPresent, verbosity);
		}
	}

	// instantiating gSystemManager
	GManager gSystemManager(verbosity);

	map<string, GSystemFactory*> systemFactory;

	// registering factories in the manager
	// and adding them to systemFactory
	// if a factory is not found, registering it in the manager and loading it into the map
	for (auto& system: gsystemsMap) {
		string factory = system.second->getFactory();

		// text
		// ----
		if(factory == "text") {
			if(systemFactory.find(factory) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemTextFactory>(GSYSTEMTXTFACTORY);
				systemFactory[factory] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMTXTFACTORY);
			}
		} else if(factory == "cad") {
			if(systemFactory.find(factory) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemCadFactory>(GSYSTEMCADFACTORY);
				systemFactory[factory] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMCADFACTORY);
			}
		}  else if(factory == "gdml") {
			if(systemFactory.find(factory) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemCadFactory>(GSYSTEMGDMFACTORY);
				systemFactory[factory] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMGDMFACTORY);
			}
		} else if(factory == "mysql") {
			if(systemFactory.find(factory) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemCadFactory>(GSYSTEMSQLFACTORY);
				systemFactory[factory] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMSQLFACTORY);
			}
		}
	}

	// now loading detector definitions
	for (auto& system: gsystemsMap) {
		string systemName = system.first;
		string factory = system.second->getFactory();

		if(systemFactory.find(factory) != systemFactory.end()) {
			systemFactory[factory]->loadSystem(system.second, verbosity);
		} else {
			cerr << FATALERRORL << "SystemFactory factory <" << factory << "> not found for " << systemName << endl;
			gexit(EC__FACTORYNOTFOUND);
		}

		// PRAGMA TODO: log accounting
		// account number of volume definitions loaded
	}

	
	// applying modifiers
	for (auto& [volumeNameToModify, gmodifier] : gmodifiersMap ) {

		// looping over systems, searching for volume
		GVolume *thisVolume = searchForVolume(volumeNameToModify);
		if(thisVolume != nullptr) {
			thisVolume->applyShift(gmodifier->getShift());
			thisVolume->applyTilt(gmodifier->getTilts());
			thisVolume->modifyExistence(gmodifier->getExistence());
		}

	}


}


// seerch for a volume among systems in gsystemsMap
GVolume* GWorld::searchForVolume(string volumeName) {

	GVolume* volumeFound = nullptr;

	for (auto& system: gsystemsMap) {
		GVolume *thisVolume = system.second->getGVolume(volumeName);
		if(thisVolume != nullptr) {
			return thisVolume;
		}
	}

	// error: volume not found
	cerr << FATALERRORL << "Volume <" << volumeName << "> not found in gsetup " << endl;
	gexit(EC__GVOLUMENOTFOUND);


	return volumeFound;
}








// PRAGMA TODO: Loads materials
// PRAGMA TODO: Loads system parameters

