// string for gexit
#include "gutilities.h"
using namespace gutilities;

// gsystem
#include "systemGdmlFactory.h"

// c++
using namespace std;


GSystemGDMLFactory::GSystemGDMLFactory() {

	possibleLocationOfTextDatabases.push_back(".");
	possibleLocationOfTextDatabases.push_back("");

	auto gtextEnv = getenv(GEMCDB_ENV); // char*
	if ( gtextEnv != nullptr) {
		vector<string> dirsDB = getStringVectorFromString(gtextEnv);

		if ( dirsDB.size() > 0) {
			for ( auto& dirDB: dirsDB ) {
				possibleLocationOfTextDatabases.push_back(dirDB);
			}

		}
	}
}

