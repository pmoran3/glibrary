// gdynamic
#include "gdynamicdigitization.h"



GTrueInfoHit* GDynamic::collectTrueInformation(GHit *ghit)
{
	GTrueInfoHit* trueInfoHit = new GTrueInfoHit();
	
	// edep and stepTime
	if ( ghit->stepEdep.size() ) {
		float eTotal = 0;
		for ( auto& edep: ghit->stepEdep ) {
			eTotal = eTotal + edep;
		}
		trueInfoHit->includeVariable("totEDep", eTotal);
	}
	
	return gdata;
}
