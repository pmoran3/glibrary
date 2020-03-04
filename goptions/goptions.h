#ifndef  GOPTIONS_H
#define  GOPTIONS_H  1

// doxygen
#include "doxy.h"

// conventions
#include "conventions.h"

// json parser
#include "json.hpp"
using namespace nlohmann;

// c++
#include <string>
using namespace std;


class GOption
{
private:

	const string name;         // option name
	const string description;  // summary description. This is used in the search.

	// the json definition contains the verbosity (defaulted at silent) and array of these objects:
	// { "tag": "tagname", "description": "tag description", "default": default value}
	const json joptionDefinition;

	bool groupable;           // if an option belongs to a group, options can be collected by using -add-<name>

	// the option, validated against the definition
	// if some tags are not set, they will be set to the joptionDefinition default
	vector<json> jValues;


	// conditions for a valid option:
	// 1. each key must match a defined tag
	// 2. if the definition does not provide a default, the option must provide one

	// check if a tag is defined
	bool isTagDefined(string key, int verbosity);

public:

	// default constructor
	GOption() = default;

	// default copy constructor
	GOption ( const GOption & ) = default;

	// constructor using the definitions
	GOption(string n, string d, json j, bool g = false): name(n), description(d), joptionDefinition(j), groupable(g) { }

	string getName() const {return name;}

	bool parseJsons(json userJson, bool isAddition, int verbosity);
};


class GOptions
{
public:
	// constructor using the definitions
	GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions);

private:

	// a special command line option -gverbosity=# will set this
	int gverbosity = 0;

	// GOptions array
	vector<GOption> jOptions;

	// jcards parsing utilities
	string setVerbosityAndFindBaseJCard(int argc, char *argv[]);  // set gverbosity; finds a configuration file (jcard). Returns "na' if not found.
	vector<json> retrieveUserJsons(string jcardFilename);         // returns all jsons objects pointed by the base and imported jcards
	int parseJCards(vector<json> allUserJsons);                   // parse the jcard in the GOptions array

	// search utilities
	long findOption(string name);  // find goption from the array. return jOptions array index or -1 if not found

	// cleanup groups if a non -add option appears not in first place
	int cleanUpGroupOption(string groupName);
};




#endif
