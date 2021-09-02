#include "ginternalDigitization.h"


bool GParticleCounterDigitization::defineReadoutSpecs() {
	float     timeWindow = 10;                  // electronic readout time-window of the detector
	float     gridStartTime = 0;                // defines the windows grid
	HitBitSet hitBitSet = HitBitSet("000000");  // defines what information to be stored in the hit
	bool      verbosity = true;

	readoutSpecs = new GReadoutSpecs(timeWindow, gridStartTime, hitBitSet, verbosity);

	return true;
}


// digitized the hit
GDigitizedData* GParticleCounterDigitization::digitizeHit(GHit *ghit, int hitn) {
	vector<GIdentifier> identity = ghit->getGID();

	GDigitizedData* gdata = new GDigitizedData(ghit);

	gdata->includeVariable("hitn",      hitn);

	return gdata;

}


