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

// exiting with error, print error on screen.
// should this be part of a namespace ?
void gexit(int error);

/**
 * The class is used to:
 * * define an option
 * * assig option values from entry in a JSON file
 * * assig option values from an entry in a command line
 */
class GOption
{
public:

	/// default copy constructor
	GOption ( const GOption & ) = default;

	/**
	 * @details Constructor for simple option. Non groupable. Help is the goption description
	 * \param joptionDefinition contains the verbosity (defaulted at silent) and array of
	 * Example: { GNAME: "runno", GDESC: "run number", GDFLT: 11 }
	 */
	GOption(json joptionDefinition);

	/**
	 * @details Constructor for structured option
	 * \param name option title
	 * \param description summary description. This is used in the search.
	 * \param joptionDefinition contains the verbosity (defaulted at silent) and array of these objects.
	 * \param help the full description of the option. Multiple lines are separated by \"\n\".
	 * \param cumulative if an option belongs to a group, options can be collected by using -add-\<name\>.\n
	 * Example: {
	 *    {  GNAME: "runno",      GDESC: "run number",          GDFLT: 11},
	 *    {  GNAME: "nthreads", GDESC: "number of thrads", GDFLT: 4}
	 *	 }
	 */
	GOption(string name, string description, json joptionDefinition, string help = "na", bool cumulative = false);


private:

	const string name;         // option name
	const string description;  // summary description. This is used in the search.

	// the json definition contains the verbosity (defaulted at silent) and array of these objects:
	// Example: {
	//    { GNAME: "runno",    GDESC: "run number",       GDFLT: 11},
	//    { GNAME: "nthreads", GDESC: "number of thrads", GDFLT: 4}
	// }
	const json joptionDefinition;

	// help: here we can put the full description of the option.
	// multiple lines are defined by using "\n"
	const string help;

	// the option assigned values, validated against the definition
	// this is a vector of size 1 if the option is not multple
	//
	// if some tags are not set, they will be set to the joptionDefinition default
	// if an option is defined with default values, it will be passed to jValues
	//
	// conditions for a valid option:
	// 1. each key must match a defined tag
	// 2. if the definition does not provide a default, the option must provide one
	vector<json> jOptionAssignedValues;
	bool isDefault = false;    // true if jOptionAssignedValues is default


	// utilities to characterize the option
	void checkTagIsValid(string key, bool gdebug);    // check if a tag is defined. Exit if it's not
	bool isDefaultValue(string key, json userValue);  // check if userValue matches the default value
	bool isSimpleption();                             // check if it's a simple option

	// if an option is cumulative, options must be collected by using -add-<name>
	// jOptionAssignedValues can have multiple entries
	const bool cumulative;

	// parse user jsons options and assign jOptionAssignedValues accordingly
	void assignValuesFromJson(string userJsonKey, json userJsonValues, bool isAddition, bool gdebug, bool gstrict);
	void assignSingleValueFromSimpleJson(string userJsonKey, json userJsonValues, bool gdebug, bool gstrict);
	void assignSingleValueFromStructuredJson(string userJsonKey, json userJsonValues, bool gdebug, bool gstrict);

	// print the options different from defaults
	// if withDefaults is true also print the defaults
	void printOption(bool withDefaults);

	// making goptions friend to it can access the private variables and functions
	friend class GOptions;

};


/**
 * Contains STL the (private) GOption array
 */
class GOptions
{
public:

	/**
	 * @details User Constructor
	 * \param argc number of arguments, passed from "main"
	 * \param argv argument arrays of *chars, passed from main
	 * \param goptionDefinitions vector of user options, usually returned by a defineOptions() function
	 */
	GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions);

private:

	// read directly in the command line to control option debugging
	// an option cannot be used because the parsing is part of the debug
	// activate debug logging
	bool gdebug;

	// read directly in the command line to control option debugging
	// an option cannot be used because the parsing is part of the debug
	// activate exit on:
	// - duplicate options
	bool gstrict;

	// GOption array
	vector<GOption> jOptions;

	// jcards parsing utilities
	string findBaseJCard(int argc, char *argv[]);  // finds a configuration file (jcard). Returns "na' if not found.

	vector<json> getUserJsonsFromJCard(string jcardFilename);    // returns all jsons objects pointed by the base and imported jcards

	void parseJSONSIntoGOption(vector<json> allUserJsons);       // parse all the jsons from the jcards / command line in the GOptions array

	// search utilities
	long findOptionIndex(string name);  // find goption from the array. return jOptions array index or -1 if not found

	// same as above, but look for specifically a non structured option
	// exit if the tag refers to a non structured option
	json getNonStructuredOptionSingleValue(string tag);

	// options for GOptions
	vector<GOption>  defineGOptionsOptions();


public:

	/**
	 * @details Print Settings
	 * \param withDefaults if true prints the options not assigned by the user
	 */
	void printSettings(bool withDefaults);

	int getInt(string tag);       ///< gets the integer value associated with non structured option \"tag\"
	float getFloat(string tag);   ///< gets the float value associated with non structured option \"tag\"
	double getDouble(string tag); ///< gets the double value associated with non structured option \"tag\"

	// get option is private because the public only uses getType, or projection onto structures
	vector<json> getOptionAssignedValues(string tag);

};


#endif
