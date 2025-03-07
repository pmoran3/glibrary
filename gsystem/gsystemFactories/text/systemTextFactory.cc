// string for gexit
#include "gutilities.h"
using namespace gutilities;

// gsystem
#include "systemTextFactory.h"

// c++
using namespace std;


GSystemTextFactory::GSystemTextFactory() {
	
}


// returns the file stream, checking all possible directories.
// SYSTEMTYPE can be:
// - GTEXTGEOMTYPE (mandatory, exit if not found)
// - GTEXTMATSTYPE
ifstream* GSystemTextFactory::gSystemTextFileStream(GSystem *system, string SYSTEMTYPE, int verbosity)
{
	string fileName  = system->getFilePath();
	string variation = system->getVariation();
	
	string fname = fileName +  SYSTEMTYPE + variation + ".txt";
	
	// default dir is "."
	ifstream *IN = new ifstream(fname.c_str());
	
	if( IN->good() ) {
		if( verbosity == GVERBOSITY_DETAILS ) {
			cout << GSYSTEMLOGHEADER << "Opening file " <<  KMAG << fname << RST  << endl;
		}
		return IN;
	} else {
		// file not good, now trying other locations
		for(auto trialLocation : possibleLocationOfFiles) {
			
			string newName = trialLocation + "/" + fname;
			if( verbosity == GVERBOSITY_DETAILS ) {
				cout << GSYSTEMLOGHEADER << "Trying file " << newName << endl;
			}
			IN->open(newName.c_str());
			
			if( IN->good() ) {
				if(verbosity >= GVERBOSITY_SUMMARY) {
					cout << GSYSTEMLOGHEADER << "Opening file " << KMAG << newName << RST << endl;
				}
				// file found, return stream
				return  IN;
			}
		}
	}
	
	// at this point file was not found, error if it was a geometry file
	if ( SYSTEMTYPE == GTEXTGEOMTYPE ) {
		cerr << GSYSTEMLOGHEADER << "File " << fname << " not found " << endl;
		gexit(EC__GSETUPFILENOTOFOUND);
	}
	
	// file was not found
	return nullptr;
}


