// ghit
#include "ghit.h"

#include "G4TouchableHistory.hh"

void GHit::addHitInfos(const HitBitSet hbs, const G4Step* thisStep) {

	G4StepPoint   *poststep = thisStep->GetPostStepPoint();

	// PRAGMA TODO: there is a difference between using pre and post step
	G4ThreeVector  xyz  = poststep->GetPosition();
	G4ThreeVector  xyzL = poststep->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(xyz);
	stepGlobalPos.push_back(xyz);
	stepLocalPos.push_back(xyzL);

	// explicit variable for documentation
	float edep = thisStep->GetTotalEnergyDeposit()*gtouchable->getEnergyMultiplier();
	float time = poststep->GetGlobalTime();

	stepEdep.push_back(edep);
	stepTime.push_back(time);

	// build hit information based on the bit index and the touchable
	for(size_t hbIndex = 0; hbIndex < hbs.size(); hbIndex++) {
		addHitInfosForBit(hbIndex, hbs.test(hbIndex), thisStep);
	}

}


bool GHit::addHitInfosForBit(size_t bitIndex, const bool test, const G4Step* thisStep)
{
	// nothing to do
	if(!test) return false;

//	G4StepPoint   *prestep  = thisStep->GetPreStepPoint();
//	G4StepPoint   *poststep = thisStep->GetPostStepPoint();

	// 
	if(bitIndex == 0) {

	} else if(bitIndex == 1) {


	} else if(bitIndex == 2) {

	} else if(bitIndex == 3) {

	} else if(bitIndex == 4) {

	} else if(bitIndex == 5) {

	}
	
	return true;
	
}
