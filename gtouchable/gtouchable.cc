// gtouchable
#include "gtouchable.h"

using namespace std;

// todo: optimize the algorithm
bool GTouchable::operator == (const GTouchable& that) const
{

	// first, compare size of identity
	// this should never happen because the same sensitivity should be assigned the same identifier structure
	if (this->gidentifier.size() != that.gidentifier.size()) {
		if (verbosity) {
			cout << " Touchable sizes are different " << endl;
		}
		return false;
	}

	if (verbosity) {
		cout << " Touchable comparison:  " << endl;
		for (int i=0; i<that.gidentifier.size(); i++) {
			cout << this->gidentifier[i] << " " <<  that.gidentifier[i] << endl;
		}
	}

	// now compare that the identity is actuallty the same
	// return false if something is different
	for (int i=0; i<that.gidentifier.size(); i++) {
		if (this->gidentifier[i] != that.gidentifier[i]) {
			return false;
		}
	}

	switch (this->gType) {
	case readout:
		return this->gridTimeIndex == that.gridTimeIndex;
	case flux:
		return this->trackId == that.trackId;
	case particleCounter:
		return true;
	}

	return false;
}
