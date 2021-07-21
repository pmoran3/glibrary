// g4system
#include "g4systemOptions.h"

// project goption to a system
namespace g4system {

	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;

		// geant4 world verbosity is defined here and passed to the g4world constructor
		json jsonG4WorldVerbosity = {
			{GNAME, "g4systemv"},
			{GDESC, GVERBOSITY_DESCRIPTION},
			{GDFLT, 1}
		};
		goptions.push_back(GOption(jsonG4WorldVerbosity));

		return goptions;
	}


}
