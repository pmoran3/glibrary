// string for gexit
#include "gutilities.h"
using namespace gutilities;

// gsystem
#include "systemCadFactory.h"

// c++
using namespace std;


GSystemCADFactory::GSystemCADFactory() {

	possibleLocationOfTextDatabases.push_back(".");
	possibleLocationOfTextDatabases.push_back("");

	auto gtextEnv = getenv(GEMC_TEXTDB); // char*
	if ( gtextEnv != nullptr) {
		vector<string> dirsDB = getStringVectorFromString(gtextEnv);

		if ( dirsDB.size() > 0) {
			for ( auto& dirDB: dirsDB ) {
				possibleLocationOfTextDatabases.push_back(dirDB);
			}

		}
	}
}


