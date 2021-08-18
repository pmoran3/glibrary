// gdynamic
#include "gdynamicdigitization.h"

// notice: if the energy deposited is very low (~50eV)
// the rounding error on the averave calculations could be up to 10^-3
GTrueInfoData* GDynamicDigitization::collectTrueInformation(GHit *ghit, int hitn)
{
	GTrueInfoData* trueInfoData = new GTrueInfoData(ghit);

	// notices:
	// we do each var hitbit group loop separately in case some are not filled

	// bit 0: always there
	ghit->calculateInfosForBit(0);
	G4ThreeVector avgGlobalPos = ghit->getAvgGlobaPosition();
	G4ThreeVector avgLocalPos  = ghit->getAvgLocalPosition();

	trueInfoData->includeVariable("totalEDeposited", ghit->getTotalEnergyDeposited());
	trueInfoData->includeVariable("avgTime", ghit->getAverageTime());
	trueInfoData->includeVariable("avgx",  avgGlobalPos.getX());
	trueInfoData->includeVariable("avgy",  avgGlobalPos.getY());
	trueInfoData->includeVariable("avgz",  avgGlobalPos.getZ());
	trueInfoData->includeVariable("avglx", avgLocalPos.getX());
	trueInfoData->includeVariable("avgly", avgLocalPos.getY());
	trueInfoData->includeVariable("avglz", avgLocalPos.getZ());
	trueInfoData->includeVariable("hitn ", hitn);



	// bit 1
	return trueInfoData;
}
