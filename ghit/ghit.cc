// ghit
#include "ghit.h"

// geant4
#include "G4VVisManager.hh"

// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
G4ThreadLocal G4Allocator<GHit>* GHitAllocator = 0;

//GHit::GHit(GTouchable* gt) : G4VHit() {
GHit::GHit(GTouchable *gt, const G4Step* thisStep, const HitBitSet hbs, string cScheme) : G4VHit(),
colorSchema(cScheme) {
	// build hit information based on the hitBitSet
	for(size_t hbIndex = 0; hbIndex < hbs.size(); hbIndex++) {
		buildHitInfosForBit(gt, hbIndex, hbs.test(hbIndex), thisStep);
	}
}

GHit::~GHit() {
	
}



void GHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

	// only care about schema if we are interactie
	if(pVVisManager) {
		setColorSchema();
	}
}


// sets marker type, size, open or filled, its color based on its energy deposited

bool GHit::setColorSchema()
{

	return false;
}



