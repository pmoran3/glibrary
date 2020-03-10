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
	// set gverbosity; finds a configuration file (jcard). Returns "na' if not found.
	string jcardFilename = setVerbosityAndFindBaseJCard(argc, argv);

	// parsing json can throw
	// returns all jsons objects pointed by the base and imported jcards
	try {
		vector<json> allUserJsons = retrieveUserJsons(jcardFilename);
		parseJCards(allUserJsons);
	}
	catch (exception& e) {
		string thisException = e.what();
        

		// parse error
		if (thisException.find("parse_error") != string::npos) {
			cerr << FATALERRORL << " parsing " << jcardFilename
			<< " failed. Try validating the jcard at: " << " https://codebeautify.org/jsonvalidator" << endl;
			cout << " Remember to remove the comments, for example with \' grep -v #\' jcardFileName" << endl;
        } else {
            cerr << FATALERRORL << " exception: " << thisException << endl;
        }

		exit(EXIT_FAILURE);
	}

	// parse the jcard in the GOptions array

	// parse command line

}


// Finds the configuration file (jcard). Returns "na' if not found.
// This also sets the verbosity
string GOptions::setVerbosityAndFindBaseJCard(int argc, char *argv[])
{
	// check if gverbosity is set
	for(int i=1; i<argc; i++) {
		if ( retrieveStringBetweenChars(argv[i], "-", "=") == "gverbosity" ) {
			gverbosity = stoi(retrieveStringBetweenChars(argv[i], "=", ""));
			if (gverbosity > 0) {
				cout << REDPOINTITEM << "gverbosity option set to " << gverbosity << endl;
			}
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

	cout << endl << GWARNING << " no jcard found." << endl << endl;
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
void GOptions::parseJCards(vector<json> allUserJsons)
{
	// looping over all parsed jsons
	for (auto& userJsonOption: allUserJsons) {

		// looping over all json inside each userJsonOption
		for (auto& [userJsonKey, userJsonValue] : userJsonOption.items()) {

			// skipping import directives, the other json files are already here
			if (userJsonKey == IMPORTSTRING) {
				continue;
			}

			if (gverbosity) {
				cout << endl << GREENSQUAREITEM << "User Json Key " << BOLDWHHL << userJsonKey << RSTHHR << " -  Content: " << userJsonValue << endl;
			}

			// match userJsonKey to a jOptions
			string userJsonKeyRoot = replaceAllStringsWithString(userJsonKey, "add-", "");

			// true if add- was found
			bool isAnAddition = (userJsonKey != userJsonKeyRoot);

			// GOption index, -1 if not found
			long userJsonOptionIndex = findOption(userJsonKeyRoot);

			// if GOption was found
			if (userJsonOptionIndex != -1) {

				if (gverbosity) {
					string isAnAdditionString = "";
					if ( isAnAddition ) {
						isAnAdditionString = " This is an option addition.";
					}
					cout << GREENSQUAREITEM << "Option " << BOLDWHHL << userJsonKeyRoot << RSTHHR << " definition found." << isAnAdditionString << endl;
				}

				jOptions.at(userJsonOptionIndex).parseJsons(userJsonKey, userJsonValue, isAnAddition, gverbosity);

				// if GOption was not found (findOption returned -1)
			} else {
				cout << GWARNING << "the option " << YELLOWHHL << userJsonKey << RSTHHR << " is not known to this system." << endl;
			}
		}
	}
}


// find GOption index from the vector<GOption>
// return -1 if GOption is not found
long GOptions::findOption(string name)
{

	for (auto it = jOptions.begin(); it != jOptions.end(); it++) {
		if (it->getName() == name) {
			return distance(jOptions.begin(), it);
		}
	}

	return -1;
}


// print only the non default settings set by users
void GOptions::printSettings(bool withDefaults)
{
	cout << endl << KBLU << " User Settings: " << RST << endl << endl;;

	for(auto& jOption: jOptions) {
		jOption.printOption(withDefaults);
	}

	cout << endl;
}

