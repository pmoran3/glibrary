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

	// JSON I/O functions for easy conversion
	void to_json(json& j, const sdet& det) {
		j = json{{"detector", det.detector}, {"factory", det.factory}, {"variation", det.variation}};
	}

	void from_json(const json& j, sdet& det) {
		j.at("detector").get_to(det.detector);
		j.at("factory").get_to(det.factory);
		j.at("variation").get_to(det.variation);
	}
}



// returns array of options definitions
vector<GOption> defineOptions()
{
	vector<GOption> goptions;

	json jdetectorTag = {
		{"tag", "detector"},
		{"description", "detector system name. For TEXT factories, it includes the path to the file."},
		{"default", "no"}
	};
	json factoryTag = {
		{"tag", "variation"},
		{"description", "detector factory"},
		{"default", "no"}
	};
	json variationTag = {
		{"tag", "variation"},
		{"description", "detector variation. if not specified, \"default\" is used."},
		{"default", "default"}
	};

	json jDetOptionDefinitions = { jdetectorTag, factoryTag, variationTag};

	goptions.push_back(GOption("detector", jDetOptionDefinitions, "detector"));

	return goptions;
}



int main(int argc, char* argv[])
{

	GOptions *gopts = new GOptions(argc, argv, defineOptions());



	return 1;
}

