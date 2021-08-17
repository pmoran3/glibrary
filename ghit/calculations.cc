// ghit
#include "ghit.h"

// notice: if the energy deposited is very low (~50eV)
// the rounding error on the averave calculations could be up to 10^-3

float GHit::getTotalEnergyDeposited()
{
	if(totalEnergyDeposited == UNINITIALIZEDQUANTITY) {
		totalEnergyDeposited = 0;

		for(const auto &ei: edeps) {
			totalEnergyDeposited += ei;
		}
	}
	return totalEnergyDeposited;
}

float GHit::getAverageTime()
{
	if(totalEnergyDeposited == UNINITIALIZEDQUANTITY) {
		getTotalEnergyDeposited();
	}

	if(averageTime == UNINITIALIZEDQUANTITY) {

		averageTime = 0;
		auto nsteps = edeps.size();
		for ( auto s=0; s<nsteps; s++) {
			if ( totalEnergyDeposited > 0 ) {
				averageTime += times[s]*edeps[s]/totalEnergyDeposited;
			} else {
				averageTime += times[s]/nsteps;
			}
		}

	}

	return averageTime;
}
