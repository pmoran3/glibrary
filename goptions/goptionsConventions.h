#ifndef  GOPTIONS_CONVENTIONS_H
#define  GOPTIONS_CONVENTIONS_H  1

//  TAGS
#define GNAME  "JsonTagGNAME"
#define GDESC  "JsonTagGDESCription"
#define GDFLT  "jsonTagDefault"
#define NODFLT "NODFLT"

#define IMPORTJCARD "import jcard"

#define GDEBUGSTRING  "-gdebug"
#define GSTRICTSTRING "-gstrict"

#define PRINTALLOPTIONS "printAllOptions"
#define GOPTIONDOCUMENTATION "https://gemc.github.io/glibrary/goptions/"

// standardizing verbosity
#define GVERBOSITY_SUMMARY 1 // prints only summary message
#define GVERBOSITY_DETAILS 2 // print all details


// exit codes: 100s
#define NOOPTIONFOUND               101
#define MANDATORYOPTIONNOTFOUND     102
#define NOADDFORCUMULATIVE          103
#define ADDFORNONCUMULATIVE         104
#define JSONPARSEERROR              105
#define OPTIONSHOULDNOTBESTRUCTURED 106
#define NONCUMULATIVEALREADYPRESENT 107
#define OPTIONNOTASSIGNED           108

// template to be filled by libraries utilizing goptions
namespace goptions {

}

// gutilities namespace:
#include <vector>
#include <map>
using namespace std;

namespace gutilities {
	// returns all keys from a map<key, value>
	// I think this is in STL now?
	template<class KEY, class VALUE> vector<KEY> getKeys(const map<KEY, VALUE>& map) {
		vector<KEY> keys(map.size());
		for (const auto& it : map)
			keys.push_back(it.first);
		return keys;
	}
}


#endif

