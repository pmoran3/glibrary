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
	GHitsCollection() {
		digitizedHits  = new vector<GDigitizedHit*>;
		trueInfosHits  = new vector<GTrueInfoHit*>;
		trueInfosSteps = new vector<GTrueInfoSteps*>;
	}

	~GHitsCollection() {

		for ( auto* hit: (*digitizedHits) )  { delete hit; }
		for ( auto* hit: (*trueInfosHits) )  { delete hit; }
		for ( auto* hit: (*trueInfosSteps) ) { delete hit; }

		delete digitizedHits;
		delete trueInfosHits;
		delete trueInfosSteps;
	}


public:
	// called by virtual method. Default: does nothing.
	//void initializeVarDescrition();
	
	//map<string, string> *varDescriptions;


	// public interface to add hit
	void addDigitizedHit(GDigitizedHit *dgtzHit);

private:

	// index is hit number
	vector<GDigitizedHit*>  *digitizedHits  = nullptr;
	vector<GTrueInfoHit*>   *trueInfosHits  = nullptr;
	vector<GTrueInfoSteps*> *trueInfosSteps = nullptr;

};



#endif
