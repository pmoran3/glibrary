// string for gexit
#include "gstring.h"
using namespace gstring;

// gsetup
#include "systemTextFactory.h"

// c++
using namespace std;

//#include "dirent.h" // for directory access to DIR object

GSystemTextFactory::GSystemTextFactory() {

	auto gtextEnv = getenv(GEMC_TEXTDB); // char*
	if ( gtextEnv != nullptr) {
		vector<string> dirsDB = getStringVectorFromString(gtextEnv);

		if ( dirsDB.size() > 0) {
			for ( auto& dirDB: dirsDB ) {
				possibleLocationOfTextDatabases.push_back(dirDB);
			}

		} else {
			cerr << GWARNING << " Warning: Environment variable " << GEMC_TEXTDB << " not defined. The TEXT DB will only be searched in \".\"" << endl;
		}
	}  else {
		cerr << GWARNING << " Warning: Environment variable " << GEMC_TEXTDB << " not defined. The TEXT DB will only be searched in \".\"" << endl;
	}
}


// returns the file stream, checking all possible directories.
ifstream* GSystemTextFactory::gSystemTextFile(GSystem *system, string SYSTEMTYPE, int verbosity)
{
	string systemName = system->getName();
	string variation  = system->getVariation();


	string fname = systemName +  SYSTEMTYPE + variation + ".txt";

	// default dir is "."
	ifstream *IN = new ifstream(fname.c_str());

	if( !IN->good() ) {
		for(auto locs : possibleLocationOfTextDatabases) {
			if(locs != GSETUPNOTAPPLICABLEENTRY) {
				string newName = locs + "/" + fname;
				IN->open(newName.c_str());
				if( verbosity == GVERBOSITY_DETAILS ) {
					cout << GSETUPLOGHEADER << " Trying TEXT " << newName << endl;
				}
				if( IN->good() ) {
					if(verbosity >= GVERBOSITY_SUMMARY) {
						cout << GSETUPLOGHEADER << " Opening " << newName << endl;
					}
					// file found, return stream
					return  IN;
				}
			}
		}
		// file not found, error
		cout << GSETUPLOGHEADER << " File " << fname << " not found " << endl;
		gexit(EC__GSETUPFILENOTOFOUND);

	}

	// file was not found
	return nullptr;
}


