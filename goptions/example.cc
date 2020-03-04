// goptions
#include "goptions.h"

// c++
#include <iostream>
using namespace std;

// a simple struct to model the detector option
namespace goptions {

	struct sdet {
		string detector;
		string factory;
		string variation;
	};

	void from_json(const json& j, sdet& det) {
		j.at("detector").get_to(det.detector);
		j.at("factory").get_to(det.factory);
		j.at("variation").get_to(det.variation);
	}

	struct run {
		int runno;
	};

	void from_json(const json& j, run& r) {
		j.at("runno").get_to(r.runno);
	}
}



// returns array of options definitions
vector<GOption> defineOptions()
{
	vector<GOption> goptions;

	// detector option
	// groupable
	json jdetectorTag = {
		{"tag", "detector"},
		{"description", "detector system name. For TEXT factories, it includes the path to the file."},
		{"variation", NODEFAULT}
	};
	json factoryTag = {
		{"tag", "factory"},
		{"description", "detector factory"},
		{"variation", NODEFAULT}
	};
	json variationTag = {
		{"tag", "variation"},
		{"description", "detector variation."},
		{"variation", DEFAULTVARIATION}
	};

	json jDetOptionDefinitions = { jdetectorTag, factoryTag, variationTag};

	goptions.push_back(GOption("detector", "detector option", jDetOptionDefinitions, true));

	// run option
	// not groupable
	json runTag = {
		{"tag", "runno"},
		{"description", "Run number"},
		{"default", 0}
	};

	goptions.push_back(GOption("runno", "run option", runTag));

	return goptions;
}


int main(int argc, char* argv[])
{

	GOptions *gopts = new GOptions(argc, argv, defineOptions());



	return 1;
}

