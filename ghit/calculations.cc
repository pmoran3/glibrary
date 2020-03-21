// ghit
#include "ghit.h"

double GHit::getTotalEnergyDeposited()
{
	double totalEdep = 0;
	
	for(auto ei: stepEdep) {
		totalEdep += ei;
	}
	
	return totalEdep;
}
