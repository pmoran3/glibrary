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
	friend ostream &operator<<(ostream &stream, GIdentifier gidentifier);

public:

	//  Overloaded "!=": comparing idValue
	bool operator!= (const GIdentifier& gid) const {return this->idValue != gid.idValue;}

// api
public:
	inline string getName() const {return idName;}
	inline int getValue() const {return idValue;}


};

// GTouchable: always use the detector identifier (gidentifier) as the discriminating factor.
// If the identifier is the same gType is used
class GTouchable
{
	
public:
	// constructor called in GDetectorConstruction::ConstructSDandField
	// to register a new gtouchable in the sensitive detector gtouchable map
	GTouchable(string digitization, string gidentityString, bool verb = false);


private:
	// set by sensitive detector constructor
	GTouchableType  gType;
	vector<GIdentifier> gidentity;  ///< Uniquely identify a sensitive element
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
	friend ostream &operator<<(ostream &stream, GTouchable gtouchable);

public:
	// Overloaded "==" operator for the class 'GTouchable'
	bool operator== (const GTouchable& gtouchable) const;
	
	// called in ProcessHits
	void placeInTimeWindow(int twindex) {gridTimeIndex = twindex;}

	const float getEnergyMultiplier() {return eMultiplier;}


// api
public:
	vector<GIdentifier> getIdentity() const {return gidentity;}



};


#endif
