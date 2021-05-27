// ghit
#include "ghit.h"

void GHit::addHitInfos(const HitBitSet hbs, const G4Step* thisStep) {

	// build hit information based on the bit index and the touchable
	for(size_t hbIndex = 0; hbIndex < hbs.size(); hbIndex++) {
		addHitInfosForBit(hbIndex, hbs.test(hbIndex), thisStep);
	}

}


bool GHit::addHitInfosForBit(size_t bitIndex, const bool test, const G4Step* thisStep)
{
	// nothing to do
	if(!test) return false;
	
	// bit 1: energy and time
	if(bitIndex == 0) {
		// explicit variable for documentation
		float edep = thisStep->GetTotalEnergyDeposit()*gtouchable->getEnergyMultiplier();
		float time = thisStep->GetPostStepPoint()->GetGlobalTime();
		
		stepEdep.push_back(edep);
		stepTime.push_back(time);
	}
	
	return true;
	
}
