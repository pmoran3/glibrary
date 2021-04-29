// gdata
#include "gHitsCollection.h"

// public interface to add hit
void GHitsCollection::addDigitizedHit(GDigitizedHit *dgtzHit) {
	digitizedHits->push_back(dgtzHit);
}
