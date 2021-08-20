#ifndef  GFRAMEDATA_H
#define  GFRAMEDATA_H  1

// gdata
#include "gFrameDataCollectionHeader.h"
#include "gIntegralPayload.h"
#include "gdataConventions.h"

// c++
#include <vector>
using std::vector;

class GFrameDataCollection
{
public:
	// construct event data using a GEventHeader
	GFrameDataCollection(GFrameDataCollectionHeader* header, int v = 0 ) : verbosity(v), gheader(header) {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogClassConstruct("GEventData");
		}
		integralPayload = new vector<GIntegralPayload>();
	}

	~GFrameDataCollection() {

		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogDestruct("GEventData");
		}

		delete gheader;
		delete integralPayload;
	}

public:

	// getters
	// we want to crash if the pointers do not exist
	GFrameDataCollectionHeader *getHeader() {return gheader;}
	vector<GIntegralPayload> *getIntegralPayload() {return integralPayload;}

private:
	int verbosity;

	GFrameDataCollectionHeader *gheader = nullptr;

	vector<GIntegralPayload> *integralPayload;


};


#endif

