// string for gexit
#include "gutilities.h"
using namespace gutilities;

// gsystem
#include "systemCadFactory.h"

// c++
using namespace std;


GSystemCADFactory::GSystemCADFactory() {

	possibleLocationOfCadFiles.push_back(".");
	possibleLocationOfCadFiles.push_back("");

	// environment for cad
	auto gtextEnv = getenv(GEMCDB_ENV); // char*
	if ( gtextEnv != nullptr) {
		vector<string> dirsDB = getStringVectorFromString(gtextEnv);

		if ( dirsDB.size() > 0) {
			for ( auto& dirDB: dirsDB ) {
				possibleLocationOfCadFiles.push_back(dirDB);
			}
		}
	}

	
}

