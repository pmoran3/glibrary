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

	// draws an object at hit location
	void Draw();

private:

	// only used if pVVisManager exist (interactive mode)
	string colorSchema;

private:
	bool setColorSchema();
	// build hit information based on the hit and the touchable
	bool buildHitInfosForBit(GTouchable *gt, size_t bitIndex, const bool test, const G4Step* thisStep);


	// hit data, selected by HitBitSet, to be collected for each step
private:
	vector<float> stepEdep, stepTime;   // bit 1

	vector<G4ThreeVector> stepGlobalPos; // bit 2
	vector<float> stepSize;             // bit 2

	// geant4 touchable hierarchy
	vector<int> g4TouchableHierarchyID;

	// public interface: getting step by step quantities
public:
	vector<float> getStepEdep() {return stepEdep;}
	vector<float> getStepTime() {return stepTime;}

	// public interface: calculated quantities defined in calculationscc
public:
	double getTotalEnergyDeposited();

};


//using GHitsCollection = G4THitsCollection<GHit> ;


// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
extern G4ThreadLocal G4Allocator<GHit>* GHitAllocator;

inline void* GHit::operator new(size_t)
{

	if(!GHitAllocator) {
		GHitAllocator = new G4Allocator<GHit>;
	}
//	return (void *) GHitAllocator->MallocSingle();

	void *hit;
	hit = (void *) GHitAllocator->MallocSingle();
	return hit;
}

inline void GHit::operator delete(void *hit)
{
	if (!GHitAllocator) {
		GHitAllocator = new G4Allocator<GHit>;
	}
	GHitAllocator->FreeSingle((GHit*) hit);
}




#endif

