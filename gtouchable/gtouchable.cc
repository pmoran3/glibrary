// gtouchable
#include "gtouchable.h"
#include "gtouchableConventions.h"

// glibrary
#include "gutilities.h"

using namespace std;

// contructor from digitization and gidentity strings
GTouchable::GTouchable(string digitization, string gidentityString, vector<double> dimensions, bool verb) :
verbosity(verb),
trackId(0),
eMultiplier(1),
gridTimeIndex(0),
detectorDimenions(dimensions) {

	// gtype from digitization
	if ( digitization == FLUXNAME ) {
		gType = flux;
	} else if ( digitization == COUNTERNAME ) {
		gType = particleCounter;
	} else if ( digitization == DOSIMETERNAME ) {
		gType = dosimeter;
	} else {
		gType = readout;
	}

	// the gidentity string is of the form: 'sector: 2, layer: 4, wire; 33'
	// by construction in the sci-g API
	vector<string> identity = gutilities::getStringVectorFromStringWithDelimiter(gidentityString, ",");
	// each identity item is a string of the form 'sector: 2'
	for ( auto& gid: identity) {
		vector<string> identifier = gutilities::getStringVectorFromStringWithDelimiter(gid, ":");

		string idName  = identifier[0];
		int idValue = stoi(identifier[1]);

		gidentity.push_back(GIdentifier(idName, idValue));
	}

}


// todo: optimize the algorithm
bool GTouchable::operator == (const GTouchable& that) const
{

	// first, compare size of identity
	// this should never happen because the same sensitivity should be assigned the same identifier structure
	if (this->gidentity.size() != that.gidentity.size()) {
		if (verbosity) {
			cout << " Touchable sizes are different " << endl;
		}
		return false;
	}

	if (verbosity) {
		cout << " Touchable comparison:  " << endl;
		for (int i=0; i<that.gidentity.size(); i++) {
			cout << this->gidentity[i] << " " <<  that.gidentity[i] << endl;
		}
	}

	// now compare that the identity is actuallty the same
	// return false if something is different
	for (int i=0; i<that.gidentity.size(); i++) {
		if (this->gidentity[i] != that.gidentity[i]) {
			return false;
		}
	}

	switch (this->gType) {
		case readout:
			return this->gridTimeIndex == that.gridTimeIndex;
		case flux:
			return this->trackId == that.trackId;
		case dosimeter:
			return this->trackId == that.trackId;
		case particleCounter:
			return true;
	}

	return false;
}

// ostream GTouchable
ostream &operator<<(ostream &stream, GTouchable gtouchable) {
	for ( auto& gid: gtouchable.gidentity ) {
		stream << gid << std::endl;
	}
	return stream;
}

// ostream GIdentifier
ostream &operator<<(ostream &stream, GIdentifier gidentifier) {
	stream << " idName: " << gidentifier.idName << ", idValue " <<  gidentifier.idValue ;
	return stream;
}
