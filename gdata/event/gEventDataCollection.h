#ifndef  GEVENTDATA_H
#define  GEVENTDATA_H  1

// conventions
#include "gdataConventions.h"

// c++
#include <vector>
using std::vector;

// gdata
#include "gEventDataCollectionHeader.h"
#include "gDataCollection.h"

// glibrary
#include "goptions.h"
#include "gutsConventions.h"


class GEventDataCollection
{
public:
	// construct event data using a GEventHeader
	GEventDataCollection(GEventDataCollectionHeader* header, int v = 0 ) : verbosity(v), gheader(header) {
		if ( verbosity ) {
			gLogClassConstruct("GEventData");
		}

//		// deleting
//		for (auto& dCollection: gdataCollection) {
//			delete dCollection.second;
//		}
	}

	~GEventDataCollection() {

		if ( verbosity ) {
			gLogDestruct("GEventData");
		}

		delete gheader;
	}

public:

	void addDetectorDigitizedData(string sdName, GDigitizedData *dgtzData);

	// getters
	GEventDataCollectionHeader *getHeader() {return gheader;}

	map<string, GDataCollection*> *getDataCollection() {return gdataCollection;}

private:
	int verbosity;

	GEventDataCollectionHeader *gheader = nullptr;

	// key is sensitive detector name
	map<string, GDataCollection*> *gdataCollection;


};


#endif
