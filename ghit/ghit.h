#ifndef  GHIT_H
#define  GHIT_H 1

// This example is based on B4cCalorHit in  examples/basic/B4/B4c
// find with locate examples/basic/B4/B4c

// HitBitSet definition
#include "ghitConventions.h"

// geant4
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4Colour.hh"

// glibrary
#include "gtouchable.h"

class GHit : public G4VHit
{
public:
	GHit(GTouchable *gt, const G4Step* thisStep, const HitBitSet hbs, const string cScheme = "default");

	virtual ~GHit();

	// examples/basic/B4/B4c/include/CalorHit
	inline void* operator new(size_t);
	inline void  operator delete(void*);
	// Overloaded "==" operator for the class 'GHit'
	// bool operator== (const GHit& that) const;

	// G4VHit: draws an object at hit location
	void Draw();

private:

	G4Colour colour_touch, colour_hit, colour_passby;
	bool setColorSchema();
	string colorSchema;

	// GTouchable saved here so it can be used in the overloaded == function
	GTouchable *gtouchable;

	// hit data, selected by HitBitSet, to be collected for each step
	// always present:
	vector<float> edeps, times;
	vector<G4ThreeVector> globalPositions;
	vector<G4ThreeVector> localPositions;

	// bit 1
	vector<float> stepSize;

	// initialized to UNINITIALIZEDNUMBERQUANTITY. Set/retrieved with methods below
	float totalEnergyDeposited;
	float averageTime;
	G4ThreeVector avgGlobalPosition;
	G4ThreeVector avgLocalPosition;

	// for streaming purposes
	// Initialized to UNINITIALIZEDNUMBERQUANTITY. Set with updateGTouchableWithPayload
	// retrieved with methods below
	float chargeAtElectronics;
	float timeAtElectronics;

	// build hit information based on the bit index and the touchable
	bool addHitInfosForBitIndex(size_t bitIndex, const bool test, const G4Step* thisStep);

public:
	// public interface: getting step by step quantities
	vector<float> getEdeps() {return edeps;}
	vector<float> getTimes() {return times;}
	vector<G4ThreeVector> getGlobalPositions() {return globalPositions;}
	vector<G4ThreeVector> getLocalPositions()  {return localPositions;}

	// public interface: calculated quantities defined in calculationscc
	void calculateInfosForBit(int bit);
	float getTotalEnergyDeposited();
	float getAverageTime();
	G4ThreeVector getAvgLocalPosition();
	G4ThreeVector getAvgGlobaPosition();

	// gemc api
	// build hit information based on the G4Step
	void addHitInfosForBitset(const HitBitSet hbs, const G4Step* thisStep);
	void setQandTimeAtElectronics(float t, int q);

	inline void setHAddress(int c, int s, int ch) {gtouchable->setHAddress(c, s, ch);}
	inline const GTouchable*         getGTouchable()         const { return gtouchable; }
	inline const vector<GIdentifier> getGID()                const { return gtouchable->getIdentity(); }
	inline const vector<double>      getDetectorDimensions() const { return gtouchable->getDetectorDimensions(); }

	// returns gtouchable identity values
	vector<int> getTTID();

};

// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
extern G4ThreadLocal G4Allocator<GHit>* GHitAllocator;

using GHitsCollection = G4THitsCollection<GHit> ;

inline void* GHit::operator new(size_t)
{
	if(!GHitAllocator) GHitAllocator = new G4Allocator<GHit>;
	return (void *) GHitAllocator->MallocSingle();

}

inline void GHit::operator delete(void *hit)
{
	if (!GHitAllocator) {
		GHitAllocator = new G4Allocator<GHit>;
	}

	GHitAllocator->FreeSingle((GHit*) hit);
}




#endif

