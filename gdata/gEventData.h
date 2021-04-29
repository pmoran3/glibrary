#ifndef  GEVENTDATA_H
#define  GEVENTDATA_H  1

// conventions
#include "gdataConventions.h"

// c++
#include <vector>
using std::vector;

// gdata
#include "gEventHeader.h"
#include "gHitsCollection.h"

// glibrary
#include "goptions.h"
#include "gstringConventions.h"


class GEventData
{
public:
	// construct event data using a GEventHeader
	GEventData(GEventHeader* header, int v = 0 ) : gheader(header), verbosity(v) {
		if ( verbosity ) {
			gLogConstruct("GEventData");
		}

		// deleting
		for (auto& hitCollection: gdata) {
			delete hitCollection.second;
		}
	}

	~GEventData() {

		if ( verbosity ) {
			gLogDestruct("GEventData");
		}

		//delete [] gdata;
		delete gheader;
	}

public:

	void addDetectorDigitizedHit(string detector, GDigitizedHit *dgtzHit);

private:
	GEventHeader *gheader = nullptr;
	int verbosity;
	map<string, GHitsCollection*> gdata;


};


#endif
