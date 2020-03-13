// doxygen
#include "doxy.h"

// conventions
#include "conventions.h"

// gtouchable
#include "gtouchable.h"


// todo: optimize the algorithm
bool GTouchable::operator == (const GTouchable& that) const
{

	// first, compare identities (just the int value)
	if (this->gIdentity.size() != that.gIdentity.size()) {
		if (verbosity) {
			cout << " Touchable sizes are different " << endl;
		}
		return false;
	}

	if (verbosity) {
		cout << " Touchable comparison:  " << endl;
		for (int i=0; i<that.gIdentity.size(); i++) {
			cout << this->gIdentity[i] << " " <<  that.gIdentity[i] << endl;
		}
	}

	// now compare that the identity is actuallty the same
	for (int i=0; i<that.gIdentity.size(); i++) {
		if (this->gIdentity[i] != that.gIdentity[i]) {
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

ostream &operator<<(ostream &stream, GTouchable gtouchable) {


	return stream;
}
