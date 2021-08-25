#ifndef  GEVENTDATA_H
#define  GEVENTDATA_H  1

// gdata
#include "gEventDataCollectionHeader.h"
#include "gdataConventions.h"
#include "gDataCollection.h"

// c++
#include <vector>
using std::vector;

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
		delete gheader;
		delete gdataCollection;
	}

public:
	// api to add data
	void addDetectorTrueInfoData(string sdName,  GTrueInfoData *data);
	void addDetectorDigitizedData(string sdName, GDigitizedData *data);

	// getters
	// we want to crash if the pointers do not exist
	GEventDataCollectionHeader *getHeader() {return gheader;}
	map<string, GDataCollection*> *getDataCollection() {return gdataCollection;}
	inline int const getEventNumber() const { return gheader->getG4LocalEvn(); }

private:
	int verbosity;

	GEventDataCollectionHeader *gheader = nullptr;

	// key is sensitive detector name
	// each GDataCollection is a vector, indexed by hit number
	map<string, GDataCollection*> *gdataCollection;


};


#endif
