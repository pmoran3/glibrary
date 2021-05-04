// ghit
#include "ghit.h"

float GHit::getTotalEnergyDeposited()
{
	float totalEdep = 0;
	
	for(const auto &ei: stepEdep) {
		totalEdep += ei;
	}
	
	return totalEdep;
}
