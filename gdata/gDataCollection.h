#ifndef GHITSCOLLECTION_H
#define GHITSCOLLECTION_H 1

// gdata
#include "gTrueInfoData.h"
#include "gDigitizedData.h"

// observable types include int, float, double,
#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;


// collected for each sensitive detector
class GDataCollection {

public:
	GDataCollection() {
		digitizedData  = new vector<GDigitizedData*>;
		trueInfosData  = new vector<GTrueInfoData*>;
	}

	~GDataCollection() {

		for ( auto* hit: (*digitizedData) )  { delete hit; }
		for ( auto* hit: (*trueInfosData) )  { delete hit; }

		delete digitizedData;
		delete trueInfosData;
	}


public:
	// called by virtual method. Default: does nothing.
	//void initializeVarDescrition();
	
	//map<string, string> *varDescriptions;


	// public interface to add hit
	void addDigitizedData(GDigitizedData *dgtzHit);

	vector<GTrueInfoData*>  *getTrueInfoData()  { return trueInfosData;}
	vector<GDigitizedData*> *getDigitizedData() { return digitizedData;}

private:

	// index is hit number
	vector<GTrueInfoData*>   *trueInfosData = nullptr;
	vector<GDigitizedData*>  *digitizedData = nullptr;

};



#endif
