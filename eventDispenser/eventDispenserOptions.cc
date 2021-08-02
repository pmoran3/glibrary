// eventDispenser
#include "eventDispenserOptions.h"

// namespace to define options
namespace eventDispenser {

	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;

		json jsonEDVerbosity = {
			{GNAME, "eventDistributionv"},
			{GDESC, GVERBOSITY_DESCRIPTION},
			{GDFLT, 1}
		};
		goptions.push_back(GOption(jsonEDVerbosity));


		return goptions;
	}

}
