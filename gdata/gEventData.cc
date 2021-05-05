// gdata 
#include "gEventData.h"

void GEventData::addDetectorDigitizedData(string detector, GDigitizedData *dgtzData) {

	auto detectorHitCollection = gdataCollection.find(detector);

	// not found, creating it
	if ( detectorHitCollection == gdataCollection.end() ) {
		gdataCollection[detector] = new GDataCollection();
		gdataCollection[detector]->addDigitizedData(dgtzData);
	}

	

}
