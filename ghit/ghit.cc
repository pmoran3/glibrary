// ghit
#include "ghit.h"

// glibrary
#include "gutsConventions.h"

// geant4
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4VisAttributes.hh"

// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
G4ThreadLocal G4Allocator<GHit>* GHitAllocator = 0;

//GHit::GHit(GTouchable* gt) : G4VHit() {
GHit::GHit(GTouchable *gt, const G4Step* thisStep, const HitBitSet hbs, string cScheme) : G4VHit(),
colorSchema(cScheme),
gtouchable(gt) {
	addHitInfosForBitset(hbs, thisStep);

	// unitialized quantities
	// bit 0: always there
	totalEnergyDeposited = UNINITIALIZEDNUMBERQUANTITY;
	averageTime          = UNINITIALIZEDNUMBERQUANTITY;
	avgGlobalPosition = G4ThreeVector(UNINITIALIZEDNUMBERQUANTITY, UNINITIALIZEDNUMBERQUANTITY, UNINITIALIZEDNUMBERQUANTITY);
	avgLocalPosition  = G4ThreeVector(UNINITIALIZEDNUMBERQUANTITY, UNINITIALIZEDNUMBERQUANTITY, UNINITIALIZEDNUMBERQUANTITY);

}

GHit::~GHit() {
	
}


vector<int> GHit::getTTID() {
	vector<int> ttid;

	vector<GIdentifier> gids = getGID();

	for ( auto& gid : gids ) {
		ttid.push_back(gid.getValue());
	}

	return ttid;
}

void GHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

	// only care about schema if we are interactie
	if(pVVisManager) {
		setColorSchema();

		G4Circle circle(globalPositions[0]);
		circle.SetFillStyle(G4Circle::filled);
		circle.SetScreenSize(10);
		circle.SetVisAttributes(G4VisAttributes(colour_hit));
		pVVisManager->Draw(circle);

	}
}


// sets marker type, size, open or filled, its color based on its energy deposited
// notice: colorSchema should drive this
bool GHit::setColorSchema()
{
	colour_touch  = G4Colour(0.0, 0.0, 1.0);
	colour_hit    = G4Colour(1.0, 0.0, 0.0);
	colour_passby = G4Colour(0.0, 1.0, 0.0);

	return false;
}

