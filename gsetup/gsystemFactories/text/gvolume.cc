// gsetup
#include "systemTextFactory.h"

// mlibrary
#include "gstring.h"

// c++
#include <iostream>

void GSystemTextFactory::loadGeometry(GSystem *system, int verbosity)
{
	// will exit if not found
	ifstream *IN = gSystemTextFile(system, GTEXTGEOMTYPE, verbosity);


	if(verbosity > GVERBOSITY_SUMMARY) {
		cout << GSETUPLOGHEADER << " Loading <text> geometry for " <<  system->getName() << endl;
	}

	// loading volumes
	while(!IN->eof()) {

		string dbline;
		getline(*IN, dbline);

		if(!dbline.size())
			continue;

		// extract gvolume parameters
		vector<string> gvolumePars = gstring::getStringVectorFromStringWithDelimiter(dbline, "|");
		system->addGVolume(gvolumePars, verbosity);
	}

	IN->close();

}

