// gsetup
#include "systemTextFactory.h"

// mlibrary
#include "gstring.h"

// c++
#include <iostream>

void GSystemTextFactory::loadGeometry(GSystem *s, int verbosity)
{
//	vector<string> possibleLocations = gopt->getStringVectorValue("setupDir");
//
//	ifstream *IN = s->gSystemFile(1, possibleLocations, verbosity);
//
//	// it could be not found
//	if(!IN->good()) {
//		return;
//	}
//
//	if(verbosity > GVERBOSITY_SUMMARY) {
//		cout << setupLogHeader << " Loading <text> geometry for " <<  s->getName() << endl;
//	}
//
//	// loading volumes
//	while(!IN->eof()) {
//
//		string dbline;
//		getline(*IN, dbline);
//
//		if(!dbline.size())
//			continue;
//
//		s->addGVolume(getStringVectorFromStringWithDelimiter(dbline, "|"), verbosity);
//	}
//
//	IN->close();

}

