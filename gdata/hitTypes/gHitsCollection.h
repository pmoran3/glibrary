#ifndef GHITSCOLLECTION_H
#define GHITSCOLLECTION_H 1

// gadata
#include "gTrueInfoHit.h"
#include "gTrueInfoSteps.h"
#include "gDigitizedHit.h"

// observable types include int, float, double,
#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;


class GHitsCollection {

public:
	// called by virtual method. Default: does nothing.
	void initializeVarDescrition();
	map<string, string> *varDescriptions;

private:

	// index is hit number
	vactor<GTrueInfoHit>   *trueInfosHits;
	vactor<GTrueInfoSteps> *trueInfosSteps;
	vactor<GDigitizedHit>  *digitizedHits;

	
}





#endif
