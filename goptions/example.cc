// goptions
#include "goptions.h"

// c++
#include <iostream>
using namespace std;

// a simple struct to model the detector option
namespace goptions {

	// detector
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

	// groupable: method to return a vector<sdet>
	vector<sdet> getDetectors(vector<json> jValues) {
		vector<sdet> detectors;

		for (auto jdet: jValues) {
			detectors.push_back(jdet.get<sdet>());
		}

		return detectors;
	}

	// run number
	struct run {
		int runno;
	};

	void from_json(const json& j, run& r) {
		j.at("runno").get_to(r.runno);
	}

	// non groupable: method to return a single run
	run getRun(vector<json> jValues) {
		return jValues.front().get<run>();
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
	gopts->printSettings(false);


	// Perhaps there's a better modern way to do this
	vector<json> detOptions = gopts->getOptions("detector");
	vector<goptions::sdet> detectors = goptions::getDetectors(detOptions);

	for (auto& det: detectors) {
		cout << " detector  " << det.detector << ", factory  " << det.factory << ", variation  " << det.variation << endl;
	}


	// Perhaps there's a better modern way to do this
	vector<json> runOptions = gopts->getOptions("runno");
	goptions::run runno = goptions::getRun(runOptions);

	cout << " runno  " << runno.runno  << endl;


	return 1;
}

