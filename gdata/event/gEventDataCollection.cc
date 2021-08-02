// gdata 
#include "gEventDataCollection.h"

// glibrary

void GEventDataCollection::addDetectorDigitizedData(string sdName, GDigitizedData *dgtzData) {

	auto detectorHitCollection = gdataCollection->find(sdName);

	// not found, creating it
	if ( detectorHitCollection == gdataCollection->end() ) {
		(*gdataCollection)[sdName] = new GDataCollection();
		(*gdataCollection)[sdName]->addDigitizedData(dgtzData);
	}

}

