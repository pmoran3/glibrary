// gsetup
#include "gworld.h"

// project goption to a system
namespace gsetup {

	void from_json(const json& j, JSystem& det) {
		j.at("system").get_to(det.system);
		j.at("factory").get_to(det.factory);
		j.at("variation").get_to(det.variation);
		j.at("runno").get_to(det.runno);
	}

	// method to return a vector of GDetectors from a structured option
	vector<JSystem> getDetectors(GOptions *gopts) {

		vector<JSystem> systems;

		auto gdets = gopts->getStructuredOptionAssignedValues("gsetup");

		// looking over each of the vector<json> items
		for ( const auto& gdet: gdets ) {
			systems.push_back(gdet.get<JSystem>());
		}

		return systems;
	}

	// returns array of options definitions
	vector<GOption> defineOptions()
	{
		vector<GOption> goptions;

		// detector option
		// groupable: can use -add
		json jsonDetectorTag = {
			{GNAME, "system"},
			{GDESC, "system name (mandatory). For TEXT factories, it may include the path to the file."},
			{GDFLT, NODFLT}
		};
		json jsonFactoryTag = {
			{GNAME, "factory"},
			{GDESC, "factory name (mandatory). Possible choices: TEXT, CAD, GDML"},
			{GDFLT, NODFLT}
		};
		json jsonVariationTag = {
			{GNAME, "variation"},
			{GDESC, "variation (optional, default is \"default\")"},
			{GDFLT, "default"}
		};

		json jsonRunnoTag = {
			{GNAME, "runno"},
			{GDESC, "runno (optional, default is 1)"},
			{GDFLT, 1}
		};

		json jsonDetectorOption = { jsonDetectorTag, jsonFactoryTag, jsonVariationTag, jsonRunnoTag};

		vector<string> help;
		help.push_back("A system definition includes the geometry location, factory and variation");
		help.push_back("");
		help.push_back("Example: +gsetup={detector: experiments/clas12/targets; factory: TEXT; variation: bonus;}");

		// the last argument refers to "cumulative"
		goptions.push_back(GOption("gsetup", "defines a group of detectors", jsonDetectorOption, help, true));

		return goptions;
	}


}
