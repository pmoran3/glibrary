// gsetup
#include "gworld.h"

// returns array of options definitions
vector<GOption> defineOptions()
{
	vector<GOption> goptions;

	// detector option
	// groupable: can use -add
	json jsonDetectorTag = {
		{GNAME, "detector"},
		{GDESC, "detector system name. For TEXT factories, it includes the path to the file."},
		{GDFLT, NODFLT}
	};
	json jsonFactoryTag = {
		{GNAME, "factory"},
		{GDESC, "detector factory name"},
		{GDFLT, NODFLT}
	};
	json jsonVariationTag = {
		{GNAME, "variation"},
		{GDESC, "detector variation."},
		{GDFLT, "default"}
	};

	json jsonDetectorOption = { jsonDetectorTag, jsonFactoryTag, jsonVariationTag};

	string help = "A detector definition includes the geometry location, factory and variation\n";
	help += "The geometry and variation are mandatory fields\n";
	help += "The variation is optional, with \"default\" as default\n";

	goptions.push_back(GOption("gdetector", "detector options", jsonDetectorOption, help));

	return goptions;
}

// project goption to a system
namespace goptions {

	struct JSystem {
		string name;
		string factory;
		string variation;
		int runno;
	};

	void from_json(const json& j, JSystem& det) {
		j.at("detector").get_to(det.detector);
		j.at("factory").get_to(det.factory);
		j.at("variation").get_to(det.variation);
		j.at("variation").get_to(det.variation);
	}

	// method to return a vector of GDetectors from a structured option
	vector<GDetector> getDetectors(GOptions *gopts) {

		vector<GDetector> detectors;

		// looking over each of the vector<json> items
		for (const auto& gdet: gopts->getOption("gdetector")) {
			detectors.push_back(gdet.get<GDetector>());
		}

		return detectors;
	}
}
