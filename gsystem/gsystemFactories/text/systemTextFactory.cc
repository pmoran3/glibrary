// string for gexit
#include "gstring.h"
using namespace gstring;

// gsystem
#include "systemTextFactory.h"

// c++
using namespace std;

//#include "dirent.h" // for directory access to DIR object

GSystemTextFactory::GSystemTextFactory() {

	possibleLocationOfTextDatabases.push_back(".");
	possibleLocationOfTextDatabases.push_back("");

	auto gtextEnv = getenv(GEMC_TEXTDB); // char*
	if ( gtextEnv != nullptr) {
		vector<string> dirsDB = getStringVectorFromString(gtextEnv);

		if ( dirsDB.size() > 0) {
			for ( auto& dirDB: dirsDB ) {
				possibleLocationOfTextDatabases.push_back(dirDB);
			}

		} else {
			cerr << GWARNING << " Environment variable " << GEMC_TEXTDB << " not defined. The TEXT DB will only be searched in \".\" and \"/\"." << endl;
		}
	}  else {
		cerr << GWARNING << " Environment variable " << GEMC_TEXTDB << " not defined. The TEXT DB will only be searched in \".\" and \"/\"." << endl;
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

	if( IN->good() ) {
		return IN;
	} else {
		// file not good, now trying other locations
		for(auto trialLocation : possibleLocationOfTextDatabases) {

			string newName = trialLocation + "/" + fname;
			if( verbosity == GVERBOSITY_DETAILS ) {
				cout << GSYSTEMLOGHEADER << " Trying TEXT " << newName << endl;
			}
			IN->open(newName.c_str());

			if( IN->good() ) {
				if(verbosity >= GVERBOSITY_SUMMARY) {
					cout << GSYSTEMLOGHEADER << " Opening " << newName << endl;
				}
				// file found, return stream
				return  IN;
			}
		}
	}

	// at this point file was not found, error
	cout << GSYSTEMLOGHEADER << " File " << fname << " not found " << endl;
	gexit(EC__GSETUPFILENOTOFOUND);


	// file was not found
	return nullptr;
}


