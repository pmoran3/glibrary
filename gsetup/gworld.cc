// gsetup
#include "gworld.h"

// project goption to a system
namespace gsetup {

	struct JSystem {
		string name;
		string factory;
		string variation;
		int runno;
	};


	void from_json(const json& j, JSystem& det) {
		j.at("name").get_to(det.name);
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
			{GDESC, "system name. For TEXT factories, it may include the path to the file."},
			{GDFLT, NODFLT}
		};
		json jsonFactoryTag = {
			{GNAME, "factory"},
			{GDESC, "system factory name"},
			{GDFLT, NODFLT}
		};
		json jsonVariationTag = {
			{GNAME, "variation"},
			{GDESC, "system variation."},
			{GDFLT, "default"}
		};

		json jsonDetectorOption = { jsonDetectorTag, jsonFactoryTag, jsonVariationTag};

		string help = "A system definition includes the geometry location, factory and variation\n";
		help += "The geometry and variation are mandatory fields\n";
		help += "The variation is optional, with \"default\": default\n";

		// the last argument refers to "cumulative"
		goptions.push_back(GOption("gsetup", "gsetup cumulative option", jsonDetectorOption, help, true));

		return goptions;
	}


}
