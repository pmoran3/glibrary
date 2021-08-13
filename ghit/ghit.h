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

	// draws an object at hit location
	void Draw();

private:

	// only used if pVVisManager exist (interactive mode)
	string colorSchema;

	// GTouchable saved here so it can be used in the overloaded == function
	GTouchable *gtouchable;

private:
	G4Colour colour_touch, colour_hit, colour_passby;
	bool setColorSchema();


	// build hit information based on the bit index and the touchable
	bool addHitInfosForBit(size_t bitIndex, const bool test, const G4Step* thisStep);

	// hit data, selected by HitBitSet, to be collected for each step
private:
	// always present:
	vector<G4ThreeVector> stepGlobalPos;
	vector<G4ThreeVector> stepLocalPos;
	vector<float> stepEdep, stepTime;

	// bit 1
	vector<float> stepSize;             

	// geant4 touchable hierarchy
	vector<int> g4TouchableHierarchyID;

	// public interface: getting step by step quantities
public:
	vector<float> getStepEdep() {return stepEdep;}
	vector<float> getStepTime() {return stepTime;}

	// public interface: calculated quantities defined in calculationscc
public:
	float getTotalEnergyDeposited();
	GTouchable* getGTouchable() { return gtouchable;}

public:
	// Overloaded "==" operator for the class 'GHit'
	// bool operator== (const GHit& that) const;
	// build hit information based on the G4Step
	void addHitInfos(const HitBitSet hbs, const G4Step* thisStep);

};

// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
extern G4ThreadLocal G4Allocator<GHit>* GHitAllocator;

using GHitsCollection = G4THitsCollection<GHit> ;

inline void* GHit::operator new(size_t)
{

//	if(!GHitAllocator) {
//		GHitAllocator = new G4Allocator<GHit>;
//	}
////	return (void *) GHitAllocator->MallocSingle();
//
//	void *hit;
//	hit = (void *) GHitAllocator->MallocSingle();
//	return hit;



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

