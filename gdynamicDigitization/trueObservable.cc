// gdynamic
#include "gdynamicdigitization.h"

// notice: if the energy deposited is very low (~50eV)
// the rounding error on the averave calculations could be up to 10^-3
GTrueInfoData* GDynamicDigitization::collectTrueInformation(GHit *ghit)
{
	GTrueInfoData* trueInfoData = new GTrueInfoData();

	trueInfoData->setIdentity(ghit->getGID());

	// notices:
	// we do each var hitbit group loop separately in case some are not filled

	// local and global positions, edep and stepTime are always there
	float totalEDeposited = ghit->getTotalEnergyDeposited();
	auto edeps = ghit->getEdeps();
	auto times = ghit->getTimes();
	auto globalPositions = ghit->getGlobalPositions();
	auto localPositions  = ghit->getLocalPositions();

	float avgTime = 0;
	float  avgx = 0,  avgy = 0,  avgz = 0;
	float avglx = 0, avgly = 0, avglz = 0;

	auto nsteps = edeps.size();
	for ( auto s=0; s<nsteps; s++ ) {
		if ( totalEDeposited > 0 ) {
			avgTime = avgTime + times[s]*edeps[s]/totalEDeposited;
			avgx  = avgx  + globalPositions[s].getX()*edeps[s]/totalEDeposited;
			avgy  = avgy  + globalPositions[s].getY()*edeps[s]/totalEDeposited;
			avgz  = avgz  + globalPositions[s].getZ()*edeps[s]/totalEDeposited;
			avglx = avglx + localPositions[s].getX() *edeps[s]/totalEDeposited;
			avgly = avgly + localPositions[s].getY() *edeps[s]/totalEDeposited;
			avglz = avglz + localPositions[s].getZ() *edeps[s]/totalEDeposited;
		} else {
			avgTime = avgTime + times[s]/nsteps;
			avgx  = avgx  + globalPositions[s].getX()/nsteps;
			avgy  = avgy  + globalPositions[s].getY()/nsteps;
			avgz  = avgz  + globalPositions[s].getZ()/nsteps;
			avglx = avglx + localPositions[s].getX() /nsteps;
			avgly = avgly + localPositions[s].getY() /nsteps;
			avglz = avglz + localPositions[s].getZ() /nsteps;
		}
	}

	trueInfoData->includeVariable("totalEDeposited", totalEDeposited);
	trueInfoData->includeVariable("avgTime", avgTime);
	trueInfoData->includeVariable("avgx",  avgx);
	trueInfoData->includeVariable("avgy",  avgy);
	trueInfoData->includeVariable("avgz",  avgz);
	trueInfoData->includeVariable("avglx", avglx);
	trueInfoData->includeVariable("avgly", avgly);
	trueInfoData->includeVariable("avglz", avglz);



	// bit 1

	return trueInfoData;
}
