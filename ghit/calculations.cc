// ghit
#include "ghit.h"

// notice: if the energy deposited is very low (~50eV)
// the rounding error on the averave calculations could be up to 10^-3

void GHit::calculateInfosForBit(int bit)
{
	// bit 0: always present
	if ( bit == 0 ) {

		if(totalEnergyDeposited == UNINITIALIZEDQUANTITY) {
			getTotalEnergyDeposited();
		}

		float  avgx = 0,  avgy = 0,  avgz = 0;
		float avglx = 0, avgly = 0, avglz = 0;

		auto nsteps = edeps.size();
		for ( auto s=0; s<nsteps; s++) {
			if ( totalEnergyDeposited > 0 ) {
				averageTime += times[s]*edeps[s]/totalEnergyDeposited;
				avgx  = avgx  + globalPositions[s].getX()*edeps[s]/totalEnergyDeposited;
				avgy  = avgy  + globalPositions[s].getY()*edeps[s]/totalEnergyDeposited;
				avgz  = avgz  + globalPositions[s].getZ()*edeps[s]/totalEnergyDeposited;
				avglx = avglx + localPositions[s].getX() *edeps[s]/totalEnergyDeposited;
				avgly = avgly + localPositions[s].getY() *edeps[s]/totalEnergyDeposited;
				avglz = avglz + localPositions[s].getZ() *edeps[s]/totalEnergyDeposited;
			} else {
				averageTime += times[s]/nsteps;
				avgx  = avgx  + globalPositions[s].getX()/nsteps;
				avgy  = avgy  + globalPositions[s].getY()/nsteps;
				avgz  = avgz  + globalPositions[s].getZ()/nsteps;
				avglx = avglx + localPositions[s].getX() /nsteps;
				avgly = avgly + localPositions[s].getY() /nsteps;
				avglz = avglz + localPositions[s].getZ() /nsteps;
			}
		}
		avgGlobalPosition = G4ThreeVector(avgx,  avgy,  avgz);
		avgLocalPosition  = G4ThreeVector(avglx, avgly, avglz);

	} else if ( bit == 1 ) {

	} else if ( bit == 2 ) {

	} else if ( bit == 3 ) {

	} else if ( bit == 4 ) {

	}
}

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

	if(averageTime == UNINITIALIZEDQUANTITY) {

		if(totalEnergyDeposited == UNINITIALIZEDQUANTITY) {
			getTotalEnergyDeposited();
		}

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



G4ThreeVector GHit::getAvgGlobaPosition() {

	if ( avgGlobalPosition.getX() == UNINITIALIZEDQUANTITY && avgGlobalPosition.getY() == UNINITIALIZEDQUANTITY) {

		if(totalEnergyDeposited == UNINITIALIZEDQUANTITY) {
			getTotalEnergyDeposited();
		}

		float  avgx = 0, avgy = 0, avgz = 0;

		auto nsteps = edeps.size();
		for ( auto s=0; s<nsteps; s++) {
			if ( totalEnergyDeposited > 0 ) {
				avgx  = avgx  + globalPositions[s].getX()*edeps[s]/totalEnergyDeposited;
				avgy  = avgy  + globalPositions[s].getY()*edeps[s]/totalEnergyDeposited;
				avgz  = avgz  + globalPositions[s].getZ()*edeps[s]/totalEnergyDeposited;
			} else {
				averageTime += times[s]/nsteps;
				avgx  = avgx  + globalPositions[s].getX()/nsteps;
				avgy  = avgy  + globalPositions[s].getY()/nsteps;
				avgz  = avgz  + globalPositions[s].getZ()/nsteps;
			}
		}
		avgGlobalPosition = G4ThreeVector(avgx,  avgy,  avgz);
	}

	return avgGlobalPosition;
}

G4ThreeVector GHit::getAvgLocalPosition() {

	if ( avgLocalPosition.getX() == UNINITIALIZEDQUANTITY && avgLocalPosition.getY() == UNINITIALIZEDQUANTITY) {

		if(totalEnergyDeposited == UNINITIALIZEDQUANTITY) {
			getTotalEnergyDeposited();
		}


		float  avgx = 0,  avgy = 0,  avgz = 0;

		auto nsteps = edeps.size();
		for ( auto s=0; s<nsteps; s++) {
			if ( totalEnergyDeposited > 0 ) {
				avgx  = avgx  + localPositions[s].getX()*edeps[s]/totalEnergyDeposited;
				avgy  = avgy  + localPositions[s].getY()*edeps[s]/totalEnergyDeposited;
				avgz  = avgz  + localPositions[s].getZ()*edeps[s]/totalEnergyDeposited;
			} else {
				averageTime += times[s]/nsteps;
				avgx  = avgx  + localPositions[s].getX()/nsteps;
				avgy  = avgy  + localPositions[s].getY()/nsteps;
				avgz  = avgz  + localPositions[s].getZ()/nsteps;
			}
		}
		avgLocalPosition = G4ThreeVector(avgx,  avgy,  avgz);

	}
	return avgLocalPosition;
}
