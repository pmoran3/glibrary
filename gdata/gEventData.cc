// gdata 
#include "gEventData.h"

void GEventData::addDetectorDigitizedData(string sdName, GDigitizedData *dgtzData) {

	auto detectorHitCollection = gdataCollection.find(sdName);

	// not found, creating it
	if ( detectorHitCollection == gdataCollection.end() ) {
		gdataCollection[sdName] = new GDataCollection();
		gdataCollection[sdName]->addDigitizedData(dgtzData);
	}

	

}
