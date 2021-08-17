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


	// initialized to -1. Set/retrieved with calculated quantities below
	float totalEnergyDeposited;
	float averageTime;

	// public interface: getting step by step quantities
public:
	vector<float> getEdeps() {return edeps;}
	vector<float> getTimes() {return times;}
	vector<G4ThreeVector> getGlobalPositions() {return globalPositions;}
	vector<G4ThreeVector> getLocalPositions()  {return localPositions;}

	// public interface: calculated quantities defined in calculationscc
	float getTotalEnergyDeposited();
	float getAverageTime();

	// gemc api
	// build hit information based on the G4Step
	void addHitInfos(const HitBitSet hbs, const G4Step* thisStep);

	// build hit information based on the bit index and the touchable
	bool addHitInfosForBit(size_t bitIndex, const bool test, const G4Step* thisStep);

	inline GTouchable*         getGTouchable() const { return gtouchable;}
	inline vector<GIdentifier> getGID() const { return gtouchable->getIdentity();}

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

