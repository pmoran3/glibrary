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
			gLogClassConstruct("GFrameDataCollection");
		}
		integralPayload = new vector<GIntegralPayload*>();
	}

	~GFrameDataCollection() {

		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogDestruct("GFrameDataCollection");
		}

		delete gheader;
		delete integralPayload;
	}

public:

	// getters
	// we want to crash if the pointers do not exist
	GFrameDataCollectionHeader *getHeader() {return gheader;}

	// integral payload: integrated quantity
	void addIntegralPayload(vector<int> payload, int verbosity);
	vector<GIntegralPayload*> const *getIntegralPayload() const {return integralPayload;}

	inline long int const getFrameID() const { return gheader->getFrameID(); }

private:
	int verbosity;

	GFrameDataCollectionHeader *gheader = nullptr;

	vector<GIntegralPayload*> *integralPayload;


};


#endif

