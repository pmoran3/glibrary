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
	vector<json> allUserJsons = retrieveUserJsons(jcardFilename);

	// parse the jcard in the GOptions array
	parseJCards(allUserJsons);

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
		if ( retrieveStringBetweenChars(argv[i], "-", "=") == "gverbosity" ) {
			//cout << " AAA " << retrieveStringBetweenChars(argv[i], "=", "") << endl;
				gverbosity = stoi(retrieveStringBetweenChars(argv[i], "=", ""));
				cout << REDPOINTITEM << "gverbosity option set to " << gverbosity << endl;
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
	// looping over all parsed jsons
	for (auto& userJsonOption: allUserJsons) {
		// looping over all json inside each userJsonOption
		for (auto& [userJsonKey, userJsonValue] : userJsonOption.items()) {

			if (gverbosity) {
				cout << endl << GREENPOINTITEM << "User Json Key: " << userJsonKey << ",  User Json content: " << userJsonValue << endl;
			}

			// match userJsonKey to a jOptions
			string userJsonKeyRoot = replaceAllStringsWithString(userJsonKey, "add-", "");
			long userJsonOptionIndex = findOption(userJsonKeyRoot);

			bool isAnAddition = (userJsonKey != userJsonKeyRoot);

			// option belong to a group
			if (userJsonOptionIndex != -1) {
				if (gverbosity) {
					string isAnAdditionString = "";
					if ( isAnAddition ) {
						isAnAdditionString = " This is an option addition.";
					}
					cout << GREENSQUAREITEM << "Option " << userJsonKeyRoot << " found." << isAnAdditionString << endl;
				}

				jOptions.at(userJsonOptionIndex).parseJsons(userJsonValue, isAnAddition, gverbosity);


			} else {
				cout << GWARNING << "the option >"<< userJsonKey << "< is not known to this system." << endl;
			}

		}

	}
	return 1;
}


// find single goption index from the map. bool false if not found
long GOptions::findOption(string name)
{

	for (auto it = jOptions.begin(); it != jOptions.end(); it++) {
		if (it->getName() == name) {
			return distance(jOptions.begin(), it);
		}
	}

	return -1;
}

bool GOption::parseJsons(json userJsons, bool isAddition, int gverbosity)
{
	for(auto &userJson: userJsons) {
		if (gverbosity) {
			cout << TGREENPOINTITEM << "Json Option " << userJson << endl;
		}

		if (!isAddition && jValues.size() > 0 ) {
			if (gverbosity) {
				cout << GWARNING << " Resetting Option Content " << endl;
			}
			jValues.clear();
		}

		if (isAddition && !groupable) {
			cout << GWARNING << " Trying to adding to the non groupable option " << name << ". This will be ignored." << endl;
			return false;
		}


		json newUserOption;

		// first checking that all user tags are valid entries.
		for (auto& [userJsonKey, userJsonValue] : userJson.items()) {

			if (gverbosity > 1) {
				cout << TTPOINTITEM << " Single Key: " << userJsonKey << ",  single value: " << userJsonValue << endl;
			}

			// checking if userJsonKey is defined
			if ( !isTagDefined(userJsonKey, gverbosity) )  {
				cout << GWARNING  << userJsonKey << " tag is not known to this system. This will be ignored." << endl;
				return false;
			}

			// tag is valid, assigning key and valie to new user option
			newUserOption[userJsonKey] = userJsonValue;

		}

		// at this point all json keys are valid.
		// we need to assign default values if they are not present

		for (auto& [userJsonKey, userJsonValue] : userJson.items()) {
		}

		// looping

		// looping over detector definitions
		//		for (auto& jsonTag: joptionDefinition) {
		//
		//			string jsonTagName = jsonTag[JSONTAGNAME];
		//			string jsonTagDesc = jsonTag[JSONTAGDESC];
		//			auto jsonTagDflt   = jsonTag[JSONTAGDFLT];
		//
		//		}

	}

	return false;
}

bool GOption::isTagDefined(string key, int gverbosity) {

	bool isDefined = false;

	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {

		// if it's a single number
		if(definitionJsonValue.is_number() || definitionJsonValue.is_string()) {

			return false;
		}

		// if it's a JSON object
		string jsonTagName = definitionJsonValue[JSONTAGNAME];
		if (gverbosity > 1) {
			cout << GTABTAB << " Checking  " << key << " against " << jsonTagName << endl;
		}

		if (key == jsonTagName) {
			if (gverbosity > 1) {
				cout << TTGREENARROWITEM << key << " matches " << jsonTagName << endl;
			}
			return true;
		}

	}


	return isDefined;
}
