// goptions 
#include "goptions.h"

// c++
#include <iostream>

// gstrings
#include "gstring.h"
using namespace gstring;

// constructor:
// - load user defined options, add our options
// - assign internal option
// - parse the base jcard plus all imported jcards
// - parse the command line options
// - get our own option
GOptions::GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions) : jOptions(goptionDefinitions)
{
	// adding our options
	for(auto &ourOption: defineGOptionsOptions()) {
		jOptions.push_back(ourOption);
	}

	// check if gdebug is set on the command line
	for(int i=1; i<argc; i++) {
		if ( strcmp(argv[i], GDEBUGSTRING) == 0 ) {
			gdebug = true;
			if (gdebug) {
				cout << endl << REDPOINTITEM << "gdebug option set is set. " << endl;
			}
		}
	}


	// finds a configuration file (jcard). Returns "na' if not found.
	string jcardFilename = findBaseJCard(argc, argv);

	// parsing json can throw
	// returns all jsons objects pointed by the base and imported jcards
	try {
		vector<json> allUserJsons = retrieveUserJsonsFromJCard(jcardFilename);
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

		gexit(JSONPARSEERROR);
	}

	// parse command line

}


// Finds the configuration file (jcard). Returns "na' if not found.
// This also sets the verbosity
string GOptions::findBaseJCard(int argc, char *argv[])
{
	// finds jcard file as one of the argument
	// extension is .jcard
	for(int i=1; i<argc; i++) {
		string arg = argv[i];

		size_t pos = arg.find(".jcard");
		if(pos != string::npos) return arg;
	}
	return "na";
}


// returns a vector of json objects of the base jcard plus all imported jcards
vector<json> GOptions::retrieveUserJsonsFromJCard(string jcardFilename)
{
	vector<json> userJsons;

	// nothing happens if jcard wasn't found
	if (jcardFilename == "na") {
		return userJsons;
	}

	// base jcard
	// removing '#' from "base" (command line) jcard
	// function is defined in gstrings
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

			if (gdebug) {
				cout << endl << GREENSQUAREITEM << "User Json Key " << BOLDWHHL << userJsonKey << RSTHHR << " -  Content: " << userJsonValue << endl;
			}

			// match userJsonKey to a jOptions
			string userJsonKeyRoot = replaceAllStringsWithString(userJsonKey, "add-", "");

			// true if add- was found (no replacement in string)S
			bool isAnAddition = (userJsonKey != userJsonKeyRoot);

			// GOption index, -1 if not found
			long userJsonOptionDefinitionIndex = findOptionIndex(userJsonKeyRoot);

			// if GOption was found
			if (userJsonOptionDefinitionIndex != -1) {

				if (gdebug) {
					string isAnAdditionString = "";
					if ( isAnAddition ) {
						isAnAdditionString = " This is an option addition.";
					}
					cout << GREENSQUAREITEM << "Option " << BOLDWHHL << userJsonKeyRoot << RSTHHR << " definition found." << isAnAdditionString << endl;
				}

				jOptions.at(userJsonOptionDefinitionIndex).assignValuesFromJson(userJsonKey, userJsonValue, isAnAddition, gdebug);

				// if GOption was not found (findOption returned -1)
			} else {
				cout << FATALERRORL << "the option " << YELLOWHHL << userJsonKey << RSTHHR << " is not known to this system. " << endl;
				gexit(NOOPTIONFOUND);
			}
		}
	}
}


// find GOption index from the vector<GOption>
// error if GOption is not found
long GOptions::findOptionIndex(string name) {

	bool optionFound = false;

	for (auto it = jOptions.begin(); it != jOptions.end(); it++) {
		if (it->getName() == name) {
			optionFound = true;
			return distance(jOptions.begin(), it);
		}
	}

	if ( ! optionFound ) {
		cerr << FATALERRORL << " Option >" << name << "< not found in jOptions vector. ";
		cerr << "Use option " << PRINTALLOPTIONS << " to print all availaible options " << endl;
		gexit(OPTIONNOTFOUNDINVECTOR);
	}

	return -1;
}

vector<json> GOptions::getOption(string tag) {

	// this will exit if no option is found
	long optionIndex = findOptionIndex(tag);

	return jOptions[optionIndex].getOptionValues();

}


// print only the non default settings set by users
void GOptions::printSettings(bool withDefaults)
{
	// making sure at least one option has value
	bool canPrint = false;

	for(auto& jOption: jOptions) {
		if ( jOption.getOptionValues().size() ) {
			canPrint = true;
		}
	}

	// nothing to do.
	if (!canPrint) {
		cout << KGRN << " No Settings. " << RST << endl;
		return;
	}

	cout << endl << KGRN << " User Settings: " << RST << endl << endl;

	for(auto& jOption: jOptions) {
		jOption.printOption(withDefaults);
	}

	cout << endl;
}



// same as above, but look for specifically a non structured option
// exit if the tag refers to a non structured option
json GOptions::getNonStructuredOption(string tag) {

	// will exit if not found
	json jn = getOption(tag).front();

	if ( jn.begin().value().is_structured() ) {
		cerr << FATALERRORL << " The tag " << tag << " is part of the structured option " << jn << endl;
		cerr << " Use structure projection to retrieve this option (see documentation at " << GOPTIONDOCUMENTATION << ")" << endl;
		gexit(OPTIONISSTRUCTURED);
	}

	return jn;
}


int GOptions::getInt(string tag) {
	// will exit if not found
	json jn = getNonStructuredOption(tag);
	return jn[tag].get<int>();
}

float GOptions::getFloat(string tag) {
	// will exit if not found
	json jn = getNonStructuredOption(tag);
	return jn[tag].get<float>();
}

double GOptions::getDouble(string tag) {
	// will exit if not found
	json jn = getNonStructuredOption(tag);
	return jn[tag].get<double>();
}



// options for GOption
vector<GOption> GOptions::defineGOptionsOptions()
{
	vector<GOption> goptions;

	return goptions;

}

