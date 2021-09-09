// ghit
#include "ghit.h"

#include "G4TouchableHistory.hh"

void GHit::addHitInfosForBitset(const HitBitSet hbs, const G4Step* thisStep) {

	G4StepPoint   *poststep = thisStep->GetPostStepPoint();

	// PRAGMA TODO: there is a difference between using pre and post step
	G4ThreeVector  xyz  = poststep->GetPosition();
	G4ThreeVector  xyzL = poststep->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(xyz);
	globalPositions.push_back(xyz);
	localPositions.push_back(xyzL);

	// explicit variable for documentation
	float edep = thisStep->GetTotalEnergyDeposit()*gtouchable->getEnergyMultiplier();
	float time = poststep->GetGlobalTime();

	edeps.push_back(edep);
	times.push_back(time);

	// build hit information based on the bit index and the touchable
	// starting from 1 as no bit set is handled aboce
	for(size_t hbIndex = 1; hbIndex < hbs.size(); hbIndex++) {
		addHitInfosForBitIndex(hbIndex, hbs.test(hbIndex), thisStep);
	}

}


bool GHit::addHitInfosForBitIndex(size_t bitIndex, const bool test, const G4Step* thisStep)
{
	// nothing to do
	if(!test) return false;

	G4Track *trk = thisStep->GetTrack();
	G4StepPoint   *prestep  = thisStep->GetPreStepPoint();
//	G4StepPoint   *poststep = thisStep->GetPostStepPoint();

	// bit 1: pid, energies
	if(bitIndex == 1) {
		pids.push_back(trk->GetDefinition()->GetPDGEncoding());
		Es.push_back(prestep->GetTotalEnergy());

	} else if(bitIndex == 2) {

	} else if(bitIndex == 3) {

	} else if(bitIndex == 4) {

	} else if(bitIndex == 5) {

	}
	
	return true;
	
}
