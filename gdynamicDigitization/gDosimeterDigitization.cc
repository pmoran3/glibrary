#include "ginternalDigitization.h"



bool GDosimeterDigitization::defineReadoutSpecs() {
	float     timeWindow = 10;                  // electronic readout time-window of the detector
	float     gridStartTime = 0;                // defines the windows grid
	HitBitSet hitBitSet = HitBitSet("000000");  // defines what information to be stored in the hit
	bool      verbosity = true;

	readoutSpecs = new GReadoutSpecs(timeWindow, gridStartTime, hitBitSet, verbosity);

	return true;
}


// digitized the hit
GDigitizedData* GDosimeterDigitization::digitizeHit(GHit *ghit, int hitn) {

	// ghit->getGID() must have a single entry
	GIdentifier identity = ghit->getGID().front();

	GDigitizedData* gdata = new GDigitizedData(ghit);

	gdata->includeVariable(identity.getName(), identity.getValue()             );
	gdata->includeVariable("hitn",             hitn                            );
	gdata->includeVariable("eTot",             ghit->getTotalEnergyDeposited() );
	gdata->includeVariable("time",             ghit->getAverageTime()          );

	return gdata;
}

#include <fstream>
using std::ifstream;

// loads digitization constants
bool GDosimeterDigitization::loadConstants(int runno, string variation) {

	// Niel Data
	// key is PID
	map<int, string> nielDataFiles;
	nielDataFiles[11]    = "niel_electron.txt";
	nielDataFiles[211]   = "niel_pion.txt";
	nielDataFiles[2112]  = "niel_neutron.txt";
	nielDataFiles[22212] = "niel_proton.txt";

	for ( auto [pid, filename]: nielDataFiles) {

		ifstream inputfile;;
		inputfile.open(filename, ifstream::in);
		if( !inputfile ) {
			cerr << " Error loading dosimeter data for pid <" << pid << "> from file " << filename  << endl;
			return false;
		}

		cout << " Loading dosimeter data for pid <" << pid << "> from file " << filename <<  endl;
		double p0, p1;
		while( !inputfile.eof() ){

			inputfile >> p0 >> p1 ;

			nielfactorMap[pid].push_back(p0);
			E_nielfactorMap[pid].push_back(p1);
		}
		inputfile.close();


	}


	return true;
}

double GDosimeterDigitization::getNielFactorForParticleAtEnergy(int pid, double energy) {

}
