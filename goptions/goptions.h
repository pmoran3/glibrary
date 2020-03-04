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

	// the option, validated against the definition
	// if some tags are not set, they will be set to the joptionDefinition default
	json joption;

public:

	// default constructor
	GOption() = default;

	// default copy constructor
	GOption ( const GOption & ) = default;

	// constructor using the definitions
	GOption(string n, string d, json j, bool g = false): name(n), description(d), joptionDefinition(j), isGroup(g) { }

	bool isGroup;        // if an option belongs to a group, options can be collected by using -add-<name>
	string getName() const {return name;}
};


class GOptions
{
public:
	// constructor using the definitions
	GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions);

private:
	// a special command line option -gverbosity=1 will set this to true
	bool gverbosity = false;

	// GOptions group map
	map<string, vector<GOption>> optionsMap;

	// build the optionsMap based on the vector<GOption> goptionDefinitions
	void buildOptionsMap(vector<GOption> goptionDefinitions);

	// jcards parsing utilities
	string findBaseJCard(int argc, char *argv[]);          // finds a configuration file (jcard). Returns "na' if not found.
	vector<json> retrieveUserJsons(string jcardFilename);  // returns all jsons objects pointed by the base and imported jcards
	int parseJCards(vector<json> allUserJsons);                   // parse the jcard in the GOptions map
	void parseGrou();


	// search utilities
	pair<bool, long int> findSingleOption(string name);  // find single goption from the map. bool false if not found
	// check if group exist based on group name
	bool findGroupOption(string name) {return optionsMap.find(name) != optionsMap.end();}

	// cleanup groups if a non -add option appears not in first place
	int cleanUpGroupOption(string groupName);
};




#endif
