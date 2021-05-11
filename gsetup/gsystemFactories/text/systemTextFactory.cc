// string for gexit
#include "gstring.h"

// gsetup
#include "systemTextFactory.h"

//#include "dirent.h" // for directory access to DIR object

// returns the file stream, checking all possible directories.
ifstream* GSystemTextFactory::gSystemTextFile(GSystem *system, int which, vector<string> locations, int verbosity)
{
	string systemName = system->getName();
	string variation = system->getVariation();

	string fname;
	if      (which == GTEXTMATSTYPE) fname = systemName +  "__materials_" ;
	else if (which == GTEXTGEOMTYPE) fname = systemName +  "__geometry_" ;
	else if (which == GTEXTMIRSTYPE) fname = systemName +  "__mirrors_" ;

	fname += variation + ".txt";

	// default dir is "."
	ifstream *IN = new ifstream(fname.c_str());

	if(!IN->good()) {
		for(auto locs : locations) {
			if(locs != GSETUPNOTAPPLICABLEENTRY) {
				string newName = locs + "/" + fname;
				IN->open(newName.c_str());
				if(verbosity == GVERBOSITY_DETAILS) {
					cout << GSETUPLOGHEADER << " Trying " << newName << endl;
				}
				if(IN->good()) {
					if(verbosity >= GVERBOSITY_SUMMARY) {
						cout << GSETUPLOGHEADER << " Opening " << newName << endl;
					}
					// file found
					return  IN;
				}
			}
		}
		// file not found, error
		cout << GSETUPLOGHEADER << " File " << fname << " not found " << endl;
		gexit(EC__GSETUPFILENOTOFOUND);

	}
	// file was found
	return IN;
}


