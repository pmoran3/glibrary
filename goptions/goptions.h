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

	const string description;  // summary description. This is used in the search.
	const string group;        // if an option belongs to a group, it can be repeated.

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
	GOption(string d, json j, string g = "general"): description(d), group(g), joptionDefinition(j) { }

	// group getter
	string getGroup() const { return group;}
};


class GOptions
{
public:
	// constructor using the definitions
	GOptions(int argc, char *argv[], vector<GOption> goptionDefinitions);

private:

	// GOptions group map
	map<string, vector<GOption>> optionsMap;

	// build the optionsMap based on the vector<GOption> goptionDefinitions
	void buildOptionsMap(vector<GOption> goptionDefinitions);

	// jcards parsing utilities
	string findBaseJCard(int argc, char *argv[]);      // finds a configuration file (jcard). Returns "na' if not found.
	vector<json> buildAllJsons(string jcardFilename);  // returns all jsons objects pointed by the base and imported jcards
	int parseJCards(vector<json> jsons);               // parse the jcard in the GOptions map


};




#endif
