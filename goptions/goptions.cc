// goptions 
#include "goptions.h"

// c++
#include <iostream>

// constructor:
// - add option definitions to the group option map
// - parse jcards
// - parse command line options (CLS)
// - print user settings (variables set by users, not default)
GOptions::GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions)
{
	cout << endl;

	buildOptionsMap(goptionDefinitions);

	// parse jcards, including imports
	string jcardFilename = findBaseJCard(argc, argv);
	vector<json> allJOptions = buildAllJsons(jcardFilename);
	parseJCards(allJOptions);


	// parse command line

	// now print the user settings that differ from the default choices
	// printUserSettings();


	cout << endl;

}


// build the optionsMap based on the vector<GOption> goptionDefinitions
void GOptions::buildOptionsMap(vector<GOption> goptionDefinitions)
{
	// define "singles" group
	optionsMap["singles"] = vector<GOption>();

	// build the group map from the option definitions
	for (const auto &gopt:goptionDefinitions) {
		const string group = gopt.getGroup();
		// singles
		if (  group ==  "no" ) {
			optionsMap["singles"].push_back(gopt);

		} else {
			// group option
			optionsMap[group].push_back(gopt);
		}
	}


}


// Finds the configuration file (jcard). Returns "na' if not found.
string GOptions::findBaseJCard(int argc, char *argv[])
{
	// finds gcard file as one of the argument
	// extension is .gcard
	for(int i=1; i<argc; i++) {

		string arg = argv[i];

		size_t pos = arg.find(".jcard");
		if(pos != string::npos) return arg;
	}

	cout << endl << NOTFOUNDWARNING << " no jcard." << endl << endl;
	return "na";
}



// gstrings
#include "gstring.h"
using namespace gstring;


// Outputs a vector of json objects of the base jcard plus all imported jcards
vector<json> GOptions::buildAllJsons(string jcardFilename)
{
	vector<json> jsons;


	if (jcardFilename == "na") {
		return jsons;
	} else {

		// base jcard
		// removing '#' from "base" (command line) jcard
		string baseParsedJson = parseFileAndRemoveComments(jcardFilename);

		// building json object
		json basejson = json::parse(baseParsedJson);

		vector<json> derivedJsons;
		derivedJsons.push_back(basejson);


		// now imports other jcard if they are imported
		// structured bindings (C++17)
		for (auto& [key, value] : basejson.items()) {

			// cout << key << " : " << value << endl;;

			if ( key == IMPORTSTRING ) {
				for ( auto &importedFile: basejson[IMPORTSTRING]) {
					string importedParsedJson = parseFileAndRemoveComments(importedFile);
					derivedJsons.push_back(json::parse(importedParsedJson));
				}
			}
		}
	}

	return jsons;
}









// parse base and imported Jsons
int GOptions::parseJCards(vector<json> jsons)
{



	return 1;

}
