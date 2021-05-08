// glibrary
#include "gfactory.h"

// gsetup
#include "gworld.h"
#include "gsystemFactories/systemFactory.h"
#include "gsystemFactories/text/systemTextFactory.h"
//#include "gsystemFactories/cad/systemCadFactory.h"
//#include "gsystemFactories/gdml/systemCadFactory.h"






GWorld::GWorld(GOptions* gopts) {

	int verbosity = gopts->getInt("gsetupV");

	// projecting options onto vector of JSystem
	vector<gsetup::JSystem> systems = gsetup::getSystems(gopts);

	for (auto& system: systems) {
		gsystemsMap[system.system] = new GSystem(system.system, system.factory, system.variation, system.runno, verbosity);
	}

	// projecting options onto vector of GModifiers
	vector<gsetup::JModifier> jmodifiers = gsetup::getModifiers(gopts);

	for (auto& modifier: jmodifiers) {
		if ( modifier.volume != NOMODIFIER) {
			gmodifiersMap[modifier.volume] = new GModifier(modifier.volume, modifier.shift, modifier.tilt, modifier.isPresent, verbosity);
		}
	}

	// instantiating gSystemManager
	GManager gSystemManager(verbosity);


}



// PRAGMA TODO: Add proper log messages


//	map<string, GSystemFactory*> systemFactory;

//	// registering factories in the manager
//	// and adding them to systemFactory
//	for(auto &s : setup) {
//		string factory = s.second->getFactory();
//
//		// text
//		// ----
//		if(factory == "text") {
//			// if factory not found, registering it in the manager and loading it into the map
//			if(systemFactory.find(factory) == systemFactory.end()) {
//				gSystemManager.RegisterObjectFactory<GSystemTextFactory>("GSystemTextFactory");
//				systemFactory[factory] = gSystemManager.CreateObject<GSystemFactory>("GSystemTextFactory");
//			}
//		}
//
//		if(factory == "cad") {
//			// if factory not found, registering it in the manager and loading it into the map
//			if(systemFactory.find(factory) == systemFactory.end()) {
//				gSystemManager.RegisterObjectFactory<GSystemCadFactory>("GSystemCadFactory");
//				systemFactory[factory] = gSystemManager.CreateObject<GSystemFactory>("GSystemCadFactory");
//			}
//		}
//	}


//	// now loading detector definitions
//	for(auto &s : setup) {
//		string factory    = s.second->getFactory();
//		string systemName = s.first;
//
//		if(systemFactory.find(factory) != systemFactory.end()) {
//			systemFactory[factory]->loadSystem(gopt, setup[systemName]);
//		} else {
//			cerr << FATALERRORL << " Fatal Error: systemFactory factory <" << factory << "> not found for " << systemName << endl;
//			exit(0);
//		}
//
//		// PRAGMA TODO: accounting
//		// account number of volume definitions loaded
//	}

//	// applying modifiers
//	for(auto &m : setupModifiers) {
//		for(auto &s : setup) {
//			GVolume *thisVolume = s.second->getGVolume(m.first);
//			if(thisVolume != nullptr) {
//				thisVolume->modifyPos(m.second->getShift());
//				thisVolume->modifyRot(m.second->getTilts());
//				thisVolume->modifyExistence(m.second->getExistence());
//			}
//		}
//	}
//
//	// making sure every detector mother is defined
//	for(auto &s : setup) {
//		for(auto &vname: s.second->getAllVolumeNames()) {
//			string mother = s.second->getGVolume(vname)->getMother();
//			if(mother != WORLDNAME) {
//				if(s.second->getGVolume(mother) == nullptr) {
//					cerr << FATALERRORL << " Fatal Error: mother <" << mother << "> not found for <" << vname << ">" << endl;
//					exit(0);
//				}
//			}
//		}
//	}


	// PRAGMA TODO: Loads material
	// PRAGMA TODO: Loads system parameters

