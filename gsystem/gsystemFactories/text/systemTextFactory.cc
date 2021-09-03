// string for gexit
#include "gutilities.h"
using namespace gutilities;

// gsystem
#include "systemTextFactory.h"

// c++
using namespace std;


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
			
		}
	}  
}


// returns the file stream, checking all possible directories.
ifstream* GSystemTextFactory::gSystemTextFile(GSystem *system, string SYSTEMTYPE, int verbosity)
{
	string fileName  = system->getFile();
	string variation = system->getVariation();
	
	string fname = fileName +  SYSTEMTYPE + variation + ".txt";
	
	// default dir is "."
	ifstream *IN = new ifstream(fname.c_str());
	
	if( IN->good() ) {
		return IN;
	} else {
		// file not good, now trying other locations
		for(auto trialLocation : possibleLocationOfTextDatabases) {
			
			string newName = trialLocation + "/" + fname;
			if( verbosity == GVERBOSITY_DETAILS ) {
				cout << GSYSTEMLOGHEADER << "Trying file " << newName << endl;
			}
			IN->open(newName.c_str());
			
			if( IN->good() ) {
				if(verbosity >= GVERBOSITY_SUMMARY) {
					cout << GSYSTEMLOGHEADER << "Opening " << newName << endl;
				}
				// file found, return stream
				return  IN;
			}
		}
	}
	
	// at this point file was not found, error
	cerr << GSYSTEMLOGHEADER << "File " << fname << " not found " << endl;
	gexit(EC__GSETUPFILENOTOFOUND);
	
	
	// file was not found
	return nullptr;
}


