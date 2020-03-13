#ifndef  GTOUCHABLE_H
#define  GTOUCHABLE_H 1

// c++
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// GType: always use gIdentity as the discriminating factor.
// In addition:
//
// - readout: electronic Time Window is the discriminating factor
// flux: track id is the discriminating factor
// particleCounter: no other discriminating factors
enum GType { readout, flux, particleCounter };

struct GIdentifier {
private:
	string idName;
	int idValue;

	///< Logs GIdentifier on screen
	friend ostream &operator<<(ostream &stream, GIdentifier gidentifier) {
		stream << " idName: " << gidentifier.idName << ", idValue " <<  gidentifier.idValue ;
		return stream;
	}

public:
	// comparing just the values
	bool operator!= (const GIdentifier& gid) const {return this->idValue != gid.idValue;}  ///< Overloaded "!=" operator for the class 'GIdentifier'


};

class GTouchable
{
	
public:
	GTouchable(GType t, vector<GIdentifier> identity, bool v = 0) :
	gType{t},
	gIdentity{identity},
	trackId{0},
	eMultiplier{1},
	gridTimeIndex{0},
	verbosity{v} {}
	
public:
	double getEnergyMultiplier() {return eMultiplier;}
	
private:
	// set by constructor
	vector<GIdentifier> gIdentity;   ///< Uniquely identify a sensitive element
	
	// set by sensitive detector constructor
	GType  gType;
	
	// set in sensitiveDetector::ProcessHit
	int trackId;   ///< Used to determine if steps belong to the same hit for flux/particle counter detectors
	
	// set by processGTouchable in the digitization plugin. Defaulted to 1. Used to share energy / create new hits.
	double  eMultiplier;   ///< Energy Multiplier. By default it is 1, but energy could be shared (or created) among volumes
	
	// used to determine if a hit is within the same detector electronic time window
	// if the index is 0, this quantity is ignored
	// if it is > 0 then it is used to distinguish hits in separate time windows
	int gridTimeIndex;
	
	// users may want to define and save information from the processGTouchable function
	// to be used in the digitization later
	vector<double> userInformations;
	
	bool verbosity;

	friend ostream &operator<<(ostream &stream, GTouchable gtouchable);

public:
	bool operator== (const GTouchable& gtouchable) const;  ///< Overloaded "==" operator for the class 'GTouchable'
	void placeInTimeWindow(double time, double timeWindow) {gridTimeIndex = time/timeWindow;}
	
};


#endif
