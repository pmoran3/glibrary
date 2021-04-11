#ifndef  GOPTIONS_H
#define  GOPTIONS_H  1

// gstrings
#include "gstring.h"
using namespace gstring;

// doxygen
#include "goptionsDoxy.h"

// conventions
#include "goptionsConventions.h"

// json parser
#include "json.hpp"
using namespace nlohmann;

// c++
#include <iostream>
#include <string>
using namespace std;

/**
 * The class is used to:
 * * define an option
 * * assig option values from entry in a JSON file
 * * assig option values from an entry in a command line
 */
class GOption
{
private:

	const string name;         // option name
	const string description;  // summary description. This is used in the search.

	// the json definition contains the verbosity (defaulted at silent) and array of these objects:
	// Example: { { GNAME: "runno", GDESC: "run number", GDFLT: 11}, { GNAME: "nthreads", GDESC: "number of thrads", GDFLT: 4} }
	const json joptionDefinition;

	// help: here we can put the full description of the option.
	// multiple lines are defined by using "\n"
	const string help;

	// if an option belongs to a group, options can be collected by using -add-<name>
	const bool groupable;

	// the option instance, validated against the definition
	// if some tags are not set, they will be set to the joptionDefinition default
	// if an option is defined with default values, it will be passed to jValues
	//
	// conditions for a valid option:
	// 1. each key must match a defined tag
	// 2. if the definition does not provide a default, the option must provide one
	vector<json> jOptionValues;

	// check if a tag is defined
	bool isTagDefined(string key, int verbosity);
	bool isDefaultValue(json jValue);

public:

	// default copy constructor
	GOption ( const GOption & ) = default;

	/**
	 * @details Constructor for simple option
	 * \param joptionDefinition contains the verbosity (defaulted at silent) and array of these objects.
	 * \param groupable if an option belongs to a group, options can be collected by using -add-<name>
	 * \param help here we can put the full description of the option.
	 * Example: { GNAME: "runno", GDESC: "run number", GDFLT: 11 }
	 */
	GOption(json joptionDefinition, string help = "na", bool groupable = false);

	/**
	 * @details Constructor for structured option
	 * \param name option title
	 * \param description summary description. This is used in the search.
	 * \param joptionDefinition contains the verbosity (defaulted at silent) and array of these objects.
	 * \param groupable if an option belongs to a group, options can be collected by using -add-<name>
	 * \param help here we can put the full description of the option.
	 * Example: { { GNAME: "runno", GDESC: "run number", GDFLT: 11}, { GNAME: "nthreads", GDESC: "number of thrads", GDFLT: 4} }
	 */
	GOption(string name, string description, json joptionDefinition, string help = "na", bool groupable = false);

	/// returns option name
	string getName() const {return name;}

	bool assignValuesFromJson(string key, json userJson, bool isAddition, int verbosity);

	void printOption(bool withDefaults);

	vector<json> getOptionValues() const {
		return jOptionValues;
	}

};


/**
 * Contains STL the (private) GOption array
 */
class GOptions
{
public:
	// constructor using the GOption array vector<GOption>
	GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions);

private:

	// return verbosity from options
	int getVerbosity();

	// GOption array
	vector<GOption> jOptions;

	// jcards parsing utilities
	string findBaseJCard(int argc, char *argv[]);  // set gverbosity; finds a configuration file (jcard). Returns "na' if not found.

	vector<json> retrieveUserJsonsFromJCard(string jcardFilename);         // returns all jsons objects pointed by the base and imported jcards

	void parseJCards(vector<json> allUserJsons);                  // parse the jcard in the GOptions array

	// search utilities
	long findOption(string name);  // find goption from the array. return jOptions array index or -1 if not found

	// options for GOptions
	vector<GOption>  defineGOptionsOptions();

public:

	void printSettings(bool withDefaults);

	void writeSettingsToJsonFile();

	// retrieve option with name
	vector<json> operator[](string name) {
		long optionIndex = findOption(name);
		if ( optionIndex != -1 ) {
			return jOptions[optionIndex].getOptionValues();
		} else {
			cerr << FATALERRORL << " Option " << name << " not found in jOptions vector. Exiting with (OPTIONNOTFOUNDINVECTOR). " << endl;
			exit(OPTIONNOTFOUNDINVECTOR);

		}
	}

};


#endif
