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
GOptions::GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions)
{
	cout << endl;

	buildOptionsMap(goptionDefinitions);

	// parse jcards, including imports
	string jcardFilename = findBaseJCard(argc, argv);
	vector<json> allUserJOptions = retrieveUserJsons(jcardFilename);
	parseJCards(allUserJOptions);


	// parse command line

	// clean up if necessary
	for (const auto& group: gutilities::getKeys(optionsMap)) {
		// cleanUpGroupOption()
	}

	// now print the user settings that differ from the default choices
	// printUserSettings();


	cout << endl;

}


// build the optionsMap based on the vector<GOption> goptionDefinitions
void GOptions::buildOptionsMap(vector<GOption> goptionDefinitions)
{
	// define "singles" group
	optionsMap[NOGROUP] = vector<GOption>();

	// build the group map from the option definitions
	for (const auto &gopt:goptionDefinitions) {
		// group option
		if (  gopt.isGroup ) {
			optionsMap[gopt.getName()].push_back(gopt);
		} else {
			// singles: all under key NOGROUP
			optionsMap[NOGROUP].push_back(gopt);
		}
	}
}


// Finds the configuration file (jcard). Returns "na' if not found.
// This also sets the verbosity
string GOptions::findBaseJCard(int argc, char *argv[])
{

	// check if gverbosity is set
	for(int i=1; i<argc; i++) {
		if ( retrieveStringBetweenChars(argv[i], "-", " ") == "gverbosity" ) {
			gverbosity = true;
			cout << " > gverbosity option found." << endl;
		}

	}

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
	if (jcardFilename == "na") {
		return vector<json>();
	} else {

		// base jcard
		// removing '#' from "base" (command line) jcard
		string baseParsedJson = parseFileAndRemoveComments(jcardFilename);

		// building json object
		json basejson = json::parse(baseParsedJson);

		vector<json> derivedJsons;

		// now imports other jcard if they are imported
		// structured bindings (C++17)
		for (auto& [key, value] : basejson.items()) {
			if ( key == IMPORTSTRING ) {
				for ( auto &importedFile: basejson[IMPORTSTRING]) {
					string fileName = replaceCharInStringWithChars(importedFile, "\"", "") + ".jcard";
					string importedParsedJson = parseFileAndRemoveComments(fileName);
					derivedJsons.push_back(json::parse(importedParsedJson));
				}
			}
		}
		// putting the base jcard at the end:
		// all imports should be declared at the top of the jcard thus they come first
		derivedJsons.push_back(basejson);
		return derivedJsons;
	}
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
				pair<bool, long int> findSingle = findSingleOption(key);

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
pair<bool, long int> GOptions::findSingleOption(string name)
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

