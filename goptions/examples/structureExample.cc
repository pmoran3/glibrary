#ifndef DOXYGEN_SHOULD_SKIP_THIS /* DOXYGEN_SHOULD_SKIP_THIS */

// goptions
#include "goptions.h"

// gstrings
#include "gstring.h"
using namespace gstring;

// c++
#include <iostream>
using namespace std;

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

// a simple struct to model the detector option
namespace goptions {
	
	struct GDetector {
		string detector;
		string factory;
		string variation;
	};

	void from_json(const json& j, GDetector& det) {
		//auto jdet = j.at("gdetector");
		j.at("detector").get_to(det.detector);
		j.at("factory").get_to(det.factory);
		j.at("variation").get_to(det.variation);
	}

	// method to return a vector of GDetectors from a structured option
	GDetector getDetector(GOptions *gopts) {

		// getting json detector from option
		auto gdet = gopts->getStructuredOptionAssignedValues("gdetector");

		// projecting it onto GDetector structure
		return gdet.front().get<GDetector>();
	}

}


// example of parsing one jcard and reading a variable
int main(int argc, char* argv[])
{
	GOptions *gopts = new GOptions(argc, argv, defineOptions());

	// print settings with defaults
	gopts->printSettings(true);

	// projecting option onto GDetector
	goptions::GDetector gdet = goptions::getDetector(gopts);

	cout << " Accessing projected structure GDetector: " << endl << endl;
	cout << " detector: " << gdet.detector << ", factory: " << gdet.factory << ", variation: " << gdet.variation << endl;
	cout << endl;
	
	return EXIT_SUCCESS;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
