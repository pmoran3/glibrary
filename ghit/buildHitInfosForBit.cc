// ghit
#include "ghit.h"

bool GHit::buildHitInfosForBit(GTouchable *gt, size_t bitIndex, const bool test, const G4Step* thisStep)
{
    // nothing to do
    if(!test) return false;
    
    // bit 1: energy and time
    if(bitIndex == 0) {
        // explicit variable for documentation
        double edep = thisStep->GetTotalEnergyDeposit()*gt->getEnergyMultiplier();
        double time = thisStep->GetPostStepPoint()->GetGlobalTime();
        
        stepEdep.push_back(edep);
        stepTime.push_back(time);
    }
    
    return true;
    
}
