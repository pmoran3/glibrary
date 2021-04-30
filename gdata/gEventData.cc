// gdata 
#include "gEventData.h"

void GEventData::addDetectorDigitizedHit(string detector, GDigitizedHit *dgtzHit) {

	auto detectorHitCollection = gdata.find(detector);

	// not found, creating it
	if ( detectorHitCollection == gdata.end() ) {
		gdata[detector] = new GHitsCollection();
		gdata[detector]->addDigitizedHit(dgtzHit);
	}

	

}
