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
    
    // help: here we can put the full description of the option.
    // multiple lines are defined by using "\n"
    string help;
    
    // verbosity as defined in conventions. Defaulted at 1.
    int verbosity;
    
    // if an option belongs to a group, options can be collected by using -add-<name>
    bool groupable;
    
    // the option, validated against the definition
    // if some tags are not set, they will be set to the joptionDefinition default
    // if an option is defined with default values, it will be passed to jValues
    vector<json> jUserValues;
    
    // conditions for a valid option:
    // 1. each key must match a defined tag
    // 2. if the definition does not provide a default, the option must provide one
    
    // check if a tag is defined
    bool isTagDefined(string key, int verbosity);
    bool isDefaultValue(json jValue);
    
    
public:
    
    // default constructor
    GOption() = default;
    
    // default copy constructor
    GOption ( const GOption & ) = default;
    
    // constructor using the definitions
    GOption(string n, string d, json j, bool g = false);
    
    string getName() const {return name;}
    
    bool parseJsons(string key, json userJson, bool isAddition, int verbosity);
    
    void printOption(bool withDefaults);
    
    vector<json> getOptions() {
        return jUserValues;
    }
    
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
    void parseJCards(vector<json> allUserJsons);                   // parse the jcard in the GOptions array
    
    // search utilities
    long findOption(string name);  // find goption from the array. return jOptions array index or -1 if not found
    
    
public:
    void printSettings(bool withDefaults);
    void writeSettingsToJsonFile();
    vector<json> operator[](string name) {return jOptions[findOption(name)].getOptions();}

};




#endif
