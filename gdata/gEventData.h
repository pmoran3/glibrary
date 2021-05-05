#ifndef  GEVENTDATA_H
#define  GEVENTDATA_H  1

// conventions
#include "gdataConventions.h"

// c++
#include <vector>
using std::vector;

// gdata
#include "gEventHeader.h"
#include "gDataCollection.h"

// glibrary
#include "goptions.h"
#include "gstringConventions.h"


class GEventData
{
public:
	// construct event data using a GEventHeader
	GEventData(GEventHeader* header, int v = 0 ) : gheader(header), verbosity(v) {
		if ( verbosity ) {
			gLogClassConstruct("GEventData");
		}

		// deleting
		for (auto& hitCollection: gdataCollection) {
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

	void addDetectorDigitizedData(string detector, GDigitizedData *dgtzData);

private:
	GEventHeader *gheader = nullptr;
	int verbosity;


	map<string, GDataCollection*> gdataCollection;


};


#endif
