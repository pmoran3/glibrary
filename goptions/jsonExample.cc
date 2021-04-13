#ifndef DOXYGEN_SHOULD_SKIP_THIS
// goptions
#include "goptions.h"

// gstrings
#include "gstring.h"
using namespace gstring;

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



// json parser
#include "json.hpp"
using namespace nlohmann;

// example of parsing one jcard and reading a variable
int main(int argc, char* argv[])
{

	if(argc != 2) {
		cout << " Error: you must provide a jcard." << endl;
	}

	string fileName = argv[1];

	cout << " Opening jcard: " << fileName << endl;

	// removing '#'
	string parsedJson = parseFileAndRemoveComments(fileName);

	// building json object
	json pjson = json::parse(parsedJson);

	// careful: this returns an array
	json jdetectors = pjson["add-detector"];

	for (auto det: jdetectors) {
		cout << " json: " << det << endl;
		auto d = det.get<goptions::sdet>();
		cout << " detector struct variable: " << d.detector << endl;
	}

	return EXIT_SUCCESS;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
