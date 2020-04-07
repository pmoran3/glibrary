#ifndef  GHIT_H
#define  GHIT_H 1

// This example is based on B4cCalorHit in  basic/B4/B4c

// doxygen
#include "ghitDoxy.h"

// conventions
#include "ghitConventions.h"


// geant4
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"

// glibrary
#include "gtouchable.h"


// GHIT Bitset.
// Setting a bit will call the corresponding code in buildHitInfos
//
// 1st bit: energy deposited, time
// 2nd bit: global position, step length
// 3rd bit: local position
// 4th bit: track informations: momentum, total energy, vertex, pid, track id
// 5th bit: mother particle track information. This is created after the event
// 6th bit: meta information: magnetic field. process id name that created the particle
// 7th bit: optical photon only: wavelength, momentum, vertex, track id

class GHit : public G4VHit
{
public:
	GHit(GTouchable *gt, const G4Step* thisStep, HitBitSet hbs, string colorSchema = "default");

	virtual ~GHit();

	inline void* operator new(size_t);
	inline void  operator delete(void*);

	// add G4Step information to the hit
	void addStepInfos(const G4Step* thisStep);

	// draws an object at hit location
	void Draw();

private:

	GTouchable *gTouchable;

	HitBitSet hitBitSet;

	// only used if pVVisManager exist (interactive mode)
	string colorSchema;

private:
	bool setColorSchema();
	bool buildHitInfosForBit(size_t bitIndex, bool test, const G4Step* thisStep); // build hit information based on the hit

	// hit data is collected for every step
	vector<double> stepEdep, stepTime;   // bit 1

	vector<G4ThreeVector> stepGlobalPos; // bit 2
	vector<double> stepSize;             // bit 2

	// geant4 touchable hierarchy
	vector<int> g4TouchableHierarchyID;

	// public interface: step by step quantities
public:
	vector<double> getStepEdep() {return stepEdep;}
	vector<double> getStepTime() {return stepTime;}

	// public interface: calculated quantities
public:
	double getTotalEnergyDeposited();

};


using GHitsCollection = G4THitsCollection<GHit> ;


// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
extern G4ThreadLocal G4Allocator<GHit>* GHitAllocator;

inline void* GHit::operator new(size_t)
{


	if(!GHitAllocator) {
		GHitAllocator = new G4Allocator<GHit>;
	}
	return (void *) GHitAllocator->MallocSingle();

	// as in B4cCalorHit
//	void *hit;
//	hit = (void *) GHitAllocator->MallocSingle();
//	return hit;

}

inline void GHit::operator delete(void *hit)
{

	if (!GHitAllocator) {
		GHitAllocator = new G4Allocator<GHit>;
	}
	GHitAllocator->FreeSingle((GHit*) hit);

}




#endif

