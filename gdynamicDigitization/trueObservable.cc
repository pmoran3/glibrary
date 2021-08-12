// gdynamic
#include "gdynamicdigitization.h"


GTrueInfoData* GDynamicDigitization::collectTrueInformation(GHit *ghit)
{
	GTrueInfoData* trueInfoData = new GTrueInfoData();
	
	// edep and stepTime
	auto edepSteps = ghit->getStepEdep();
	if ( edepSteps.size() ) {
		float eTotal = 0;
		for ( auto& edep: edepSteps ) {
			eTotal = eTotal + edep;
		}
		trueInfoData->includeVariable("totEDep", eTotal);
	}
	
	return trueInfoData;
}
