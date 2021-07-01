#ifndef  GTOUCHABLE_H
#define  GTOUCHABLE_H 1

// conventions
#include "gtouchableConventions.h"


// c++
#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::ostream;
using std::vector;

// - readout: electronic Time Window is the discriminating factor
// - flux: track id is the discriminating factor
// - particleCounter: no other discriminating factors
enum GTouchableType { readout, flux, particleCounter };

struct GIdentifier {


public:
	// constructor
	GIdentifier(string n, int v) : idName{n}, idValue{v} {}

private:
	string idName;
	int idValue;

	// Logs GIdentifier on screen
	friend ostream &operator<<(ostream &stream, GIdentifier gidentifier) {
		stream << " idName: " << gidentifier.idName << ", idValue " <<  gidentifier.idValue ;
		return stream;
	}

public:

	//  Overloaded "!=": comparing idValue
	bool operator!= (const GIdentifier& gid) const {return this->idValue != gid.idValue;}

};

// GTouchable: always use the detector identifier (gidentifier) as the discriminating factor.
// If the identifier is the same gType is used
class GTouchable
{
	
public:
	// constructor called at gvolume construction
	GTouchable(GTouchableType t, vector<GIdentifier> identifier, bool verb = false) :
	gType(t),
	gidentifier(identifier),
	verbosity(verb) {
		trackId = 0;
		eMultiplier = 1;
		gridTimeIndex = 0;
	}

private:
	// set by sensitive detector constructor
	GTouchableType  gType;
	vector<GIdentifier> gidentifier;   ///< Uniquely identify a sensitive element
	bool verbosity;

	// set in sensitiveDetector::ProcessHit
	// Used to determine if steps belong to the same hit for flux/particle counter detectors
	int trackId;
	
	// set by processGTouchable in the digitization plugin. Defaulted to 1. Used to share energy / create new hits.
	// Energy Multiplier. By default it is 1, but energy could be shared (or created) among volumes
	float  eMultiplier;
	
	// used to determine if a hit is within the same detector electronic time window for readout electronic
	// set using placeInTimeWindow in ProcessHits
	int gridTimeIndex;

	// to print it out
	friend ostream &operator<<(ostream &stream, GTouchable gtouchable) {
		for ( auto& identity: gtouchable.gidentifier ) {
			stream << identity << std::endl;
		}

		return stream;

	}

public:
	// Overloaded "==" operator for the class 'GTouchable'
	bool operator== (const GTouchable& gtouchable) const;
	
	// called in ProcessHits
	void placeInTimeWindow(int twindex) {gridTimeIndex = twindex;}

	const float getEnergyMultiplier() {return eMultiplier;}

};


#endif
