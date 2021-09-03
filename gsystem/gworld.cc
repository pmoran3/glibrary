// glibrary
#include "gfactory.h"
#include "gutilities.h"

// gsystem
#include "gworld.h"
#include "gsystemFactories/systemFactory.h"
#include "gsystemFactories/text/systemTextFactory.h"
#include "gsystemFactories/cad/systemCadFactory.h"
#include "gsystemFactories/gdml/systemGdmlFactory.h"
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

	// text factory created no matter what, needed to create ROOT volume
	gSystemManager.RegisterObjectFactory<GSystemTextFactory>(GSYSTEMTXTFACTORY);
	systemFactory[GSYSTEMTEXTFACTORY] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMTXTFACTORY);

	for (auto& system: *gsystemsMap) {
		
		string factoryName = system.second->getFactoryName();

		if(factoryName == GSYSTEMCADTFACTORY) {
			if(systemFactory.find(factoryName) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemCADFactory>(GSYSTEMCADFACTORY);
				systemFactory[factoryName] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMCADFACTORY);
			}
		}  else if(factoryName == GSYSTEMGDMLTFACTORY) {
			if(systemFactory.find(factoryName) == systemFactory.end()) {
				gSystemManager.RegisterObjectFactory<GSystemGDMLFactory>(GSYSTEMGDMLFACTORY);
				systemFactory[factoryName] = gSystemManager.CreateObject<GSystemFactory>(GSYSTEMGDMLFACTORY);
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
	// using the text factory
	
	string worldVolumeDefinition = gopts->getString("worldVolumeDefinition");
	(*gsystemsMap)[ROOTWORLDGVOLUMENAME] = new GSystem(ROOTWORLDGVOLUMENAME, GSYSTEMTEXTFACTORY, "default", verbosity);
	(*gsystemsMap)[ROOTWORLDGVOLUMENAME]->addROOTVolume(worldVolumeDefinition);

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
GVolume* GWorld::searchForVolume(string volumeName, string purpose) const {

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


vector<string> GWorld::getSensitiveDetectorsList() {
	vector<string> snames;
	for (auto& system: *gsystemsMap) {
		for (auto &gvolume: *system.second->getGVolumesMap()) {
			string digitization = gvolume.second->getDigitization();
			if ( digitization != UNINITIALIZEDSTRINGQUANTITY) {
				if ( find(snames.begin(), snames.end(), digitization) == snames.end())
				snames.push_back(digitization);
			}
		}
	}

	return snames;
}



// PRAGMA TODO: Loads materials
// PRAGMA TODO: Loads system parameters

