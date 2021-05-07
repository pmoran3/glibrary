// gsetup
#include "gworld.h"

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


}
