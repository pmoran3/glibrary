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
		{JSONTAGNAME, "detector"},
		{JSONTAGDESC, "detector system name. For TEXT factories, it includes the path to the file."},
		{JSONTAGDFLT, NODEFAULT}
	};
	json factoryTag = {
		{JSONTAGNAME, "factory"},
		{JSONTAGDESC, "detector factory name"},
		{JSONTAGDFLT, NODEFAULT}
	};
	json variationTag = {
		{JSONTAGNAME, "variation"},
		{JSONTAGDESC, "detector variation."},
		{JSONTAGDFLT, "default"}
	};

	json jDetOptionDefinitions = { jdetectorTag, factoryTag, variationTag};

	goptions.push_back(GOption("detector", "detector option", jDetOptionDefinitions, true));

	// run option
	// not groupable
	json runTag = {
		{JSONTAGNAME, "runno"},
		{JSONTAGDESC, "Run number"},
		{JSONTAGDFLT, 0}
	};

	goptions.push_back(GOption("runno", "run option", runTag));

	return goptions;
}


int main(int argc, char* argv[])
{

	GOptions *gopts = new GOptions(argc, argv, defineOptions());

	// print settings w/o defaults
	cout << endl;
	gopts->printSettings(false);
	cout << endl;


//	cout << " Detector Option: " << endl;

	cout << " Detector Option: " << gopts->getOptionNamed("detector").getName() << endl;

	return 1;
}

