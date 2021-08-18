// glibrary
#include "gfactory.h"
#include "gutilities.h"

// gsystem
#include "gworld.h"
#include "gsystemFactories/systemFactory.h"
#include "gsystemFactories/text/systemTextFactory.h"
#include "gsystemFactories/cad/systemCadFactory.h"
//#include "gsystemFactories/gdml/systemCadFactory.h"
//#include "gsystemFactories/mysql/systemCadFactory.h"


GWorld::GWorld(GOptions* gopts) {

	gsystemsMap = new map<string, GSystem*>;
	
	int verbosity = gopts->getInt("gsystemv");

	// projecting json options onto vector of JSystem
	vector<gsystem::JSystem> jsystems = gsystem::getSystems(gopts);

	// loading gsystemsMap with GSystems
	for (auto& jsystem: jsystems) {
		string keyName = gutilities::getFileFromPath(jsystem.system);
		(*gsystemsMap)[keyName] = new GSystem(jsystem.system, jsystem.factory, jsystem.variation, verbosity);
	}

	// projecting options onto vector of GModifiers
	vector<gsystem::JModifier> jmodifiers = gsystem::getModifiers(gopts);

	// loading gmodifiersMap
	for (auto& modifier: jmodifiers) {
		if ( modifier.volume != NOMODIFIER) {
			gmodifiersMap[modifier.volume] = new GModifier(modifier.volume, modifier.shift, modifier.tilt, modifier.isPresent, verbosity);
		}
	}

	// instantiating gSystemManager and systemFactory
	GManager gSystemManager("GWorld", verbosity);

	map<string, GSystemFactory*> systemFactory;

	// registering factories in gSystemManager
	// and adding them to systemFactory
	// if a factory is not existing already, registering it in the manager, instantiating it, and loading it into the map
	for (auto& system: *gsystemsMap) {
		
		string factoryName = system.second->getFactoryName();

		if(factoryName == "text") {
			if(systemFactory.find(factoryName) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemTextFactory>(GSYSTEMTXTFACTORY);
				systemFactory[factoryName] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMTXTFACTORY);
			}
		} else if(factoryName == "cad") {
			if(systemFactory.find(factoryName) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemCadFactory>(GSYSTEMCADFACTORY);
				systemFactory[factoryName] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMCADFACTORY);
			}
		}  else if(factoryName == "gdml") {
			if(systemFactory.find(factoryName) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemCadFactory>(GSYSTEMGDMFACTORY);
				systemFactory[factoryName] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMGDMFACTORY);
			}
		} else if(factoryName == "mysql") {
			if(systemFactory.find(factoryName) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemCadFactory>(GSYSTEMSQLFACTORY);
				systemFactory[factoryName] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMSQLFACTORY);
			}
		}
	}

	// done with gSystemManager
	gSystemManager.clearDLMap();

	// now loading gvolumes definitions for all systems
	for (auto& system: *gsystemsMap) {
		string systemName = system.first;
		string factory = system.second->getFactoryName();

		if(systemFactory.find(factory) != systemFactory.end()) {
			systemFactory[factory]->loadSystem(system.second, verbosity);
		} else {
			cerr << FATALERRORL << "systemFactory factory <" << factory << "> not found for " << systemName << endl;
			gexit(EC__FACTORYNOTFOUND);
		}

		// PRAGMA TODO: log accounting
		// account number of volume definitions loaded
	}

	if(verbosity == GVERBOSITY_DETAILS) {
		for (auto system: *gsystemsMap) {
			// first collect all volume names
			for (auto& [volumeName, gvolume] : *system.second->getGVolumesMap() ) {
				cout << GSYSTEMLOGHEADER << "system " << system.first << " volume " << volumeName << endl;
			}
		}
	}


	// adding root volume to the a "root" gsystem
	// using the first existing factory name (if there is anything in the factory)
	// otherwise use "TEXT"
	string firstFactory = "text";
	if (gsystemsMap->size() > 0) {
		firstFactory = gsystemsMap->begin()->second->getFactoryName();
	} 
	string worldVolume = gopts->getString("worldVolume");
	(*gsystemsMap)[ROOTWORLDGVOLUMENAME] = new GSystem(ROOTWORLDGVOLUMENAME, firstFactory, "default", verbosity);
	(*gsystemsMap)[ROOTWORLDGVOLUMENAME]->addROOTVolume(worldVolume);

	// applying gvolumes modifiers
	for (auto& [volumeNameToModify, gmodifier] : gmodifiersMap ) {

		// looping over systems, searching for volume
		GVolume *thisVolume = searchForVolume(volumeNameToModify, " is marked for modifications ");
		if(thisVolume != nullptr) {
			thisVolume->applyShift(gmodifier->getShift());
			thisVolume->applyTilt(gmodifier->getTilts());
			thisVolume->modifyExistence(gmodifier->getExistence());
		}
	}


	// making sure every detector mother is defined
	for (auto system: *gsystemsMap) {
		// first collect all volume names
		for (auto& [volumeName, gvolume] : *system.second->getGVolumesMap() ) {
			// will exit with error if not found
			// skipping world volume
			string motherVolumeName = gvolume->getMother();
			if (motherVolumeName != MOTHEROFUSALL ) {
				searchForVolume(motherVolumeName, "mother of <" + gvolume->getName() + ">");
			}
		}
	}

	// PRAGMA TODO: Loads material
	// PRAGMA TODO: Loads system parameters


}


// seerch for a volume among systems in gsystemsMap
GVolume* GWorld::searchForVolume(string volumeName, string purpose) {

	GVolume* volumeFound = nullptr;

	for (auto& system: *gsystemsMap) {
		GVolume *thisVolume = system.second->getGVolume(volumeName);
		if(thisVolume != nullptr) {
			return thisVolume;
		}
	}

	// error: volume not found
	cerr << FATALERRORL << "gvolume named <" << volumeName << "> (" << purpose << ") not found in gsystemsMap " << endl;
	gexit(EC__GVOLUMENOTFOUND);

	return volumeFound;
}





// PRAGMA TODO: Loads materials
// PRAGMA TODO: Loads system parameters

