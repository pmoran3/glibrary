// goptions 
#include "goptions.h"

// c++
#include <iostream>

// gstrings
#include "gstring.h"
using namespace gstring;

// constructor:
// - buildOptionsMap using the option definitions
// - parse the base jcard plus all imported jcards
// - parse the command line options (CLS)
// - print user settings (variables set by users, not default)
GOptions::GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions) : jOptions(goptionDefinitions)
{
	cout << endl;

	// set gverbosity; finds a configuration file (jcard). Returns "na' if not found.
	string jcardFilename = setVerbosityAndFindBaseJCard(argc, argv);

	// returns all jsons objects pointed by the base and imported jcards
	vector<json> allUserJOptions = retrieveUserJsons(jcardFilename);

	// parse the jcard in the GOptions array
	parseJCards(allUserJOptions);


	// parse command line


	// clean up if necessary
	for (const auto& jOption: jOptions) {
		// cleanUpGroupOption()
	}

	// now print the user settings that differ from the default choices
	// printUserSettings();

	cout << endl;

}

// Finds the configuration file (jcard). Returns "na' if not found.
// This also sets the verbosity
string GOptions::setVerbosityAndFindBaseJCard(int argc, char *argv[])
{
	// check if gverbosity is set
	for(int i=1; i<argc; i++) {
		if ( retrieveStringBetweenChars(argv[i], "-", " ") == "gverbosity" ) {
			gverbosity = true;
			cout << " > gverbosity option found." << endl;
		}
	}

	// relooping as this returns
	// finds gcard file as one of the argument
	// extension is .gcard
	for(int i=1; i<argc; i++) {
		string arg = argv[i];

		size_t pos = arg.find(".jcard");
		if(pos != string::npos) return arg;
	}

	cout << endl << GWARNING << " no jcard." << endl << endl;
	return "na";
}



// Outputs a vector of json objects of the base jcard plus all imported jcards
vector<json> GOptions::retrieveUserJsons(string jcardFilename)
{
	vector<json> userJsons;

	// nothing happens if jcard wasn't found
	if (jcardFilename == "na") {
		return userJsons;
	}

	// base jcard
	// removing '#' from "base" (command line) jcard
	string basePureJsonString = parseFileAndRemoveComments(jcardFilename);

	// building json object from base jcard
	json baseJson = json::parse(basePureJsonString);

	// now imports imported jcard if any
	for (auto& [key, value] : baseJson.items()) {
		if ( key == IMPORTSTRING ) {
			// value is a vector<string>
			for ( auto &importedJCardName: value) {
				// adding extension to set fileName
				string importJcardFileName = replaceCharInStringWithChars(importedJCardName, "\"", "") + ".jcard";

				// import json (this exit if filename isn't there)
				string importedParsedJson = parseFileAndRemoveComments(importJcardFileName);

				// add imported json to userJsons vector
				userJsons.push_back(json::parse(importedParsedJson));
			}
		}
	}
	// appending the base jcard json at the end:
	// all imports should be declared at the top of the jcard thus they come before the base settings
	userJsons.push_back(baseJson);
	return userJsons;

}

// parse base and imported Jsons
int GOptions::parseJCards(vector<json> allUserJsons)
{
	for (auto& jsonOption: allUserJsons) {
		// structured bindings (C++17)
		for (auto& [key, value] : jsonOption.items()) {

			// option belong to a group
			if (gverbosity) {
				cout << key << " :" << value << endl;
			}

			// match a group to
			string keyRoot = replaceAllStringsWithString(key, "add-", "");
			bool groupMatchFound = findGroupOption(keyRoot);

			// option belong to a group
			if (groupMatchFound) {
				if (gverbosity) {
					cout << " Group " << keyRoot << " found " << endl;
				}
				vector<GOption> groupOptions = optionsMap[keyRoot];

				// the first option is already in the definition

			} else {
				// not in group, checking single
				pair<bool, long int> findSingle = findOption(key);

				if (findSingle.first == true) {
					if (gverbosity) {
						cout << " Single " << key << " found " << endl;
					}

				} else {
					cout << GWARNING << key << " option is not known to this system." << endl;
				}
			}
		}


	}
	return 1;

}

// find single goption index from the map. bool false if not found
pair<bool, long int> GOptions::findOption(string name)
{
	pair<bool, long int> result;

	vector<GOption> singleOptions = optionsMap[NOGROUP];

	for (auto it = singleOptions.begin(); it != singleOptions.end(); it++) {

		if (it->getName() == name) {
			result.first = true;
			result.second = distance(singleOptions.begin(), it);
			return result;
		}
	}

	return result;
}

