// goptions 
#include "goptions.h"

// c++
#include <iostream>

//! constructor: add options to the group option map
GOptions::GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions)
{
	cout << endl;

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


	// parse jcards, including imports
	string jcard = findJCard(argc, argv);

	switch ( parseJCard(jcard) ) {
	case -1:
		cout << endl << CANTPARSEERROR << " Jcard cannot be parsed. Exiting." << endl << endl;
		exit(0);
	case 0:
		cout << endl << NOTFOUNDWARNING << " no jcard." << endl << endl;
	default:
		break;
	}


	// parse command line


	// now print the user settings that differ from the default choices
	// printUserSettings();




	cout << endl;

}


/*!

 \fn string GOptions::findJCard(int argc, char *argv[])

 Finds the configuration file (jcard). Returns "na' if not found.

 \param argc argv the program arguments
 \return The filename if a jcard was found. "na" otherwise
 */

string GOptions::findBaseJCard(int argc, char *argv[])
{
	// finds gcard file as one of the argument
	// extension is .gcard
	for(int i=1; i<argc; i++) {

		string arg = argv[i];

		size_t pos = arg.find(".jcard");
		if(pos != string::npos) return arg;
	}

	return "na";
}


/*!

 \fn vector<json> GOptions::allJsons(string jcard)

 Returns the vector of json objects pointed by the base and imported jcards

 \param argc argv the program arguments
 \return The filename if a jcard was found. "na" otherwise
 */

vector<json> GOptions::allJsons(string jcard)
{
	// finds gcard file as one of the argument
	// extension is .gcard
	for(int i=1; i<argc; i++) {

		string arg = argv[i];

		size_t pos = arg.find(".jcard");
		if(pos != string::npos) return arg;
	}

	return "na";
}





// gstrings
#include "gstring.h"
using namespace gstring;






/*! \fn int GOptions::parseJCard(string file)

 - Parse the jcard if it's defined
 - Returns 0 if no jcard, -1 if it cannot be parsed

 \param file the filename
 */
int GOptions::parseJCard(string file)
{

	if (file == "na") {
		return 0;
	} else {

		// removing '#' from "base" (command line) jcard
		string baseParsedJson = parseFileAndRemoveComments(file);

		// building json object
		json basejson = json::parse(baseParsedJson);

		vector<json> derivedJsons;
		derivedJsons.push_back(basejson);

		// let's check first if we
		// structured bindings (C++17)
		for (auto& [key, value] : basejson.items()) {

			std::cout << key << " : " << value << "\n";

			if ( key == IMPORTSTRING ) {
				for ( auto &importedFile: basejson[IMPORTSTRING]) {
					string importedParsedJson = parseFileAndRemoveComments(importedFile);
					derivedJsons.push_back(json::parse(importedParsedJson));
				}
			}


		}
		return 1;

	}

	return -1;

}
