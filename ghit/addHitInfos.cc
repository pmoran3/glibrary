// ghit
#include "ghit.h"

void GHit::addHitInfos(const HitBitSet hbs, const G4Step* thisStep) {


	G4ThreeVector xyz = thisStep->GetPostStepPoint()->GetPosition(); ///< Global Coordinates of interaction
	stepGlobalPos.push_back(xyz);


	// build hit information based on the bit index and the touchable
	for(size_t hbIndex = 0; hbIndex < hbs.size(); hbIndex++) {
		addHitInfosForBit(hbIndex, hbs.test(hbIndex), thisStep);
	}

}


bool GHit::addHitInfosForBit(size_t bitIndex, const bool test, const G4Step* thisStep)
{
	// nothing to do
	if(!test) return false;

	//G4StepPoint   *prestep  = thisStep->GetPreStepPoint();
	G4StepPoint   *poststep = thisStep->GetPostStepPoint();

	// bit 1: energy and time
	if(bitIndex == 0) {
		// explicit variable for documentation
		float edep = thisStep->GetTotalEnergyDeposit()*gtouchable->getEnergyMultiplier();
		float time = poststep->GetGlobalTime();
		
		stepEdep.push_back(edep);
		stepTime.push_back(time);
	}
	
	return true;
	
}
