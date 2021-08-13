// ghit
#include "ghit.h"

// geant4
#include "G4VVisManager.hh"
#include "G4Circle.hh"

// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
G4ThreadLocal G4Allocator<GHit>* GHitAllocator = 0;

//GHit::GHit(GTouchable* gt) : G4VHit() {
GHit::GHit(GTouchable *gt, const G4Step* thisStep, const HitBitSet hbs, string cScheme) : G4VHit(),
colorSchema(cScheme),
gtouchable(gt) {
	addHitInfos(hbs, thisStep);
}

GHit::~GHit() {
	
}



void GHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

	// only care about schema if we are interactie
	if(pVVisManager) {
		setColorSchema();

		G4Circle circle(stepGlobalPos[0]);
		circle.SetFillStyle(G4Circle::filled);
		circle.SetScreenSize(10);
		pVVisManager->Draw(circle);

	}
}


// sets marker type, size, open or filled, its color based on its energy deposited

bool GHit::setColorSchema()
{

	return false;
}

//bool GHit::operator == (const GHit& that) const
//{
//	if ( this->gtouchable == that.gtouchable) {
//		return true;
//	}
//
//	return false;
//}
//
