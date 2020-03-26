#ifndef  GOPTIONS_CONVENTIONS_H
#define  GOPTIONS_CONVENTIONS_H  1

// JSON TAGS
#define JSONTAGNAME "jsonTagName"
#define JSONTAGDESC "jsonTagDescription"
#define JSONTAGDFLT "jsonTagDefault"
#define IMPORTSTRING "importJcards"

// Standard string throughout goptions
#define FILENOTFOUND "fileNotFound"
#define NODEFAULT    "noDefault"

// standardizing verbosity
#define GVERBOSITY_SILENT  0
#define GVERBOSITY_SUMMARY 1
#define GVERBOSITY_DETAILS 2
#define GVERBOSITY_ALL     3

// verbosity description
#define GVERBOSITY_SILENT_D  " ・ 0: silent\n"
#define GVERBOSITY_SUMMARY_D " ・ 1: summary information\n"
#define GVERBOSITY_DETAILS_D " ・ 2: detailed information\n"
#define GVERBOSITY_ALL_D     " ・ 3: max verbosity\n"


// to be filled by libraries utilizing goptions
namespace goptions {

}

// gutilities namespace:
#include <vector>
#include <map>
using namespace std;

namespace gutilities {
	template<class KEY, class VALUE> vector<KEY> getKeys(const map<KEY, VALUE>& map) {
		vector<KEY> keys(map.size());
		for (const auto& it : map)
			keys.push_back(it.first);
		return keys;
	}
}


#endif

