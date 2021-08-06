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

		json jsonRunWeights = {
			{GNAME, "runWeightsFile"},
			{GDESC, "Text file with run number and their weights"},
			{GDFLT, "na"}
		};
		goptions.push_back(GOption(jsonRunWeights));

		json jsonnbunch = {
			{GNAME, "runWeightsFile"},
			{GDESC, "Text file with run number and their weights"},
			{GDFLT, "na"}
		};
		goptions.push_back(GOption(jsonnbunch));

		json jsonNEvents = {
			{GNAME, "n"},
			{GDESC, "Number of events to process"},
			{GDFLT, 0}
		};
		goptions.push_back(GOption(jsonNEvents));

		return goptions;
	}

}
