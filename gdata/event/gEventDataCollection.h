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
		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogClassConstruct("GEventData");
		}
		gdataCollection = new map<string, GDataCollection*>();
	}

	~GEventDataCollection() {

		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogDestruct("GEventData");
		}

		// PRAGMA TODO: what do delete here?
		for (auto& [keys, values]: (*gdataCollection) ) {
			delete values;
		}
		delete gdataCollection;
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
